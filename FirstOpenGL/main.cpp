
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include "Triangle.h"
#include "Square.h"
#include "Random.h"
#include "Mesh.h"

#include <cmath>

const int size = 20;
const float fovY = 0.9f;
const float nearPlane = 1.0f;
const float farPlane = 100.0f;
Vector3 cameraPosition;

Shape *selectedShape = nullptr;
Shape *shapeArray[size] = {nullptr};

int randShape = -1;
float maxMin = 500.0f;

int advance = 0;

int oldTimeSinceStart = 0;

bool raysphere(Vector3 spherePos, Vector3 rayDir, Vector3 rayPos, float radius)
{
	Vector3 temp = spherePos - rayPos;
	
	float dist = temp.magnitude();
	float dot = temp.x * rayDir.x + temp.y * rayDir.y + temp.z * rayDir.z;
	float result = radius * radius - (dist * dist - dot * dot);

	return result >= 0.0f;
}

void keyPressed(unsigned char key, int x, int y) {
	if (key == 'f')
	{
		if (selectedShape)
		{
			Vector3 randForce = { RandomRangef(-maxMin,maxMin), RandomRangef(-maxMin, maxMin), RandomRangef(-maxMin, maxMin) };
			selectedShape->force(randForce);
		}
	}
}

void mousePressed(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (selectedShape != nullptr)
		{
			selectedShape->selected = false;
		}

		selectedShape = nullptr;

		//TRIGGER WARNING: MATHS AHEAD

		float xPercent;
		float yPercent;
		float aspect = 1.0f;
		float fovX = 2.0f * std::atan(aspect * std::tan(fovY / 2.0f));

		//get X,Y mouse click as [0,1]'s
		xPercent = (float)x / 600.0f;
		yPercent = (float)y / 600.0f;

		/* cast a ray and detect the object we just clicked on! */
		//resolve z
		Vector3 result;
		result.z = -nearPlane;

		//resolve x
		float xWidth = 2.0f * nearPlane * std::tan(fovX / 2.0f);
		result.x = xPercent * xWidth - (xWidth / 2.0f);

		//resolve y
		float yWidth = 2.0f * nearPlane * std::tan(fovY / 2.0f);
		result.y = yPercent * yWidth - (yWidth / 2.0f);
		
		result = result / result.magnitude();

		for (int i = 0; i < size; i++)
		{
			if (raysphere(
				shapeArray[i]->position - cameraPosition,
				result,
				Vector3(),
				shapeArray[i]->radius))
			{
				shapeArray[i]->selected = true;
				selectedShape = shapeArray[i];

				break;
			}
		}
	}
}

void renderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//clear black

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.5f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

	//Ask OpenGL for the matrix, and extract the positional values
	float matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	cameraPosition.x = matrix[12];
	cameraPosition.y = matrix[13];
	cameraPosition.z = matrix[14];

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (float)(timeSinceStart - oldTimeSinceStart) / 1000.0f;
	oldTimeSinceStart = timeSinceStart;

	for (int i = 0; i < size; i++)
	{
		shapeArray[i]->update(deltaTime);

		// Since the internal physics update in updateVel() is multiplied by 0.5f,
		// it only updates for half the frame's time. This will be done
		// using the accelleration from the previous frame. 
		// Then, we will update the accelleration as part of our 
		// collision resolve step. After that, we update the last 
		// half of the frame with the new acceleration (which will also be used
		// for the first half of the next frame).

		shapeArray[i]->updateVel(deltaTime);
	}
	
	for (int i = 0; i < size; i++)
	{
		Vector3 pos1 = shapeArray[i]->position;
		
		for (int j = i + 1; j < size; j++)
		{
			Vector3 pos2 = shapeArray[j]->position;

			// from pos2 towards pos1
			Vector3 difference = pos1 - pos2;
			float distance = difference.magnitude();

			if (distance != 0.0f)
			{
				// as a unit vector
				difference = difference / distance;

				if (distance < (shapeArray[i]->radius + shapeArray[j]->radius))
				{
					shapeArray[i]->force(difference * 3.0f);
					shapeArray[j]->force(difference * -3.0f);
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		shapeArray[i]->updateVel(deltaTime);
		shapeArray[i]->draw();

		shapeArray[i]->acceleration = Vector3(0.0f, 0.0f, 0.0f);
	}

	glutSwapBuffers();
	glutPostRedisplay();

	//if (advance == 0)
	//{
	//	system("pause");
	//	advance += 10;
	//}
	//advance--;
	
}

int main(int argc, char **argv)
{
	SeedRandomNumberGenerator();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300, 300);//optional
	glutInitWindowSize(600, 600); //optional
	glutCreateWindow("OpenGL First Window");

	glutKeyboardFunc(keyPressed);
	glutMouseFunc(mousePressed);

	glewInit();

	for (int i = 0; i < size; i++)
	{
		Mesh *mesh = new Mesh();

		switch (i % 3)
		{
		case 0:
			if (!mesh->load("./SmallCubeFix.obj", "Test.png")) return 1;
			break;
		case 1:
			if (!mesh->load("./SmallSphereFixed.obj", "Test.png")) return 1;
			break;

			case 2:
				if (!mesh->load("./SmallPyramidFixed.obj", "Test.png")) return 1;
				break;
			
			/*case 3:
				if (!mesh->load("./SmallCubeCoolAgainFixed.obj")) return 1;
				break;*/
		}

		shapeArray[i] = mesh;
	}

	std::cout << glGetString(GL_VENDOR);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	// lights
	glEnable(GL_LIGHTING);

	float lightPosition0[] = { 0.0f, 0.0f, -1.7f, 1.0f };
	float diffuse0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float emissive0[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float specular0[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float attenuation0 = 3.05f;

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuation0);

	float lightPosition1[] = { 0.0f, 0.0f, -0.7f, 1.0f };
	float diffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float emissive1[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float specular1[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float attenuation1 = 3.05f;

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, attenuation1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular0);

	// camera
	glMatrixMode(GL_PROJECTION);

	float temp = 1.0f / tan(fovY / 2.0f);

	float zFar = farPlane;
	float zNear = nearPlane;

	float projMatrix[16];
	
	projMatrix[0] = temp / (8.0f / 6.0f);
	projMatrix[1] = 0.0f;
	projMatrix[2] = 0.0f;
	projMatrix[3] = 0.0f;

	projMatrix[4] = 0.0f;
	projMatrix[5] = temp;
	projMatrix[6] = 0.0f;
	projMatrix[7] = 0.0f;
	
	projMatrix[8] = 0.0f;
	projMatrix[9] = 0.0f;
	projMatrix[10] = (zFar + zNear) / (zNear - zFar);
	projMatrix[11] = -1.0f;
	
	projMatrix[12] = 0.0f;
	projMatrix[13] = 0.0f;
	projMatrix[14] = (2.0f * zFar * zNear) / (zNear - zFar);
	projMatrix[15] = 0.0f;

	glLoadMatrixf(projMatrix);

	glMatrixMode(GL_MODELVIEW);
	// action!
	glutDisplayFunc(renderScene);
	
	glutMainLoop();

	for (int i = 0; i < size; i++)
	{
		delete shapeArray[i];
	}

	return 0;
}

