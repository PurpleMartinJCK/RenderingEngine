#include "Triangle.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

void Triangle::draw()
{
	float shearMatrix[] = {
		1.0f, shearX, 0.0f, 0.0f,
		shearY, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	glPushMatrix();

	glRotatef(rotateXY, rotateYZ, rotateZX, 1.0f);
	glTranslatef(position.x, position.y, position.z);
	//glMultMatrixf(shearMatrix);
	//glScalef(scale, scale, 1.0f);

		glBegin(GL_TRIANGLES);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(xP1, yP1, 0.0f);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(xP2, yP2, 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(xP3, yP3, 0.0f);
			
			//first face
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(xP4, yP4, zP4);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(xP1, yP1, 0.0f);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(xP2, yP2, 0.0f);
			
			// second face
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(xP4, yP4, zP4);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(xP2, yP2, 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(xP3, yP3, 0.0f);

			// third face
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(xP4, yP4, zP4);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(xP3, yP3, 0.0f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(xP1, yP1, 0.0f);
			
		glEnd();

	glPopMatrix();
}