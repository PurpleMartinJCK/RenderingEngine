#include "Square.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

void Square::draw()
{

	float shearMatrix[] = {
		1.0f, shearX, 0.0f, 0.0f,
		shearY, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	glPushMatrix();

	glRotatef(rotateXY, 0.0f, 0.0f, 1.0f);
	glTranslatef(position.x, position.y, position.z);
	//glMultMatrixf(shearMatrix);
	glScalef(scale, scale, 1);

		glBegin(GL_TRIANGLES);

		p1();
		p2();
		p3();

			// other triangle
		p3();
		p2();
		p4();

		// top face
		p5();
		p6();
		p8();

		p8();
		p6();
		p7();

		// side faces
		p8();
		p3();
		p1();

		p1();
		p5();
		p8();


		p7();
		p4();
		p3();

		p3();
		p8();
		p7();


		p6();
		p2();
		p4();

		p4();
		p7();
		p6();
		

		p5();
		p1();
		p2();

		p2();
		p6();
		p5();


		glEnd();

	glPopMatrix();
}

void Square::p1()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(xP1, yP1, zP1);
}
void Square::p2() 
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(xP2, yP2, zP2);
}
void Square::p3()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(xP3, yP3, zP3);
}
void Square::p4()
{
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(xP4, yP4, zP4);
}
void Square::p5()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(xP5, yP5, zP5);
}
void Square::p6()
{
	glColor3f(0.196f, 0.804f, 0.196f);
	glVertex3f(xP6, yP6, zP6);
}
void Square::p7()
{
	glColor3f(1.0f, 0.27f, 0.0f);
	glVertex3f(xP7, yP7, zP7);
}
void Square::p8()
{
	glColor3f(0.294f, 0.0f, 0.510f);
	glVertex3f(xP8, yP8, zP8);
}