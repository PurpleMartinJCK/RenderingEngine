#pragma once
#include "Shape.h"

class Square : public Shape
{
public:

	float xP1 = 0.0f;
	float yP1 = 0.1f;
	float zP1 = 0.0f;

	float xP2 = -0.1f;
	float yP2 = 0.0f;
	float zP2 = 0.0f;

	float xP3 = 0.1f;
	float yP3 = 0.0f;
	float zP3 = 0.0f;

	float xP4 = 0.0f;
	float yP4 = -0.1f;
	float zP4 = 0.0f;

	float xP5 = xP1;
	float yP5 = yP1;
	float zP5 = 0.1f;

	float xP6 = xP2;
	float yP6 = yP2;
	float zP6 = 0.1f;

	float xP7 = xP4;
	float yP7 = yP4;
	float zP7 = 0.1f;

	float xP8 = xP3;
	float yP8 = yP3;
	float zP8 = 0.1f;

	void draw();

	void p1();
	void p2();
	void p3();
	void p4();
	void p5();
	void p6();
	void p7();
	void p8();
	
};