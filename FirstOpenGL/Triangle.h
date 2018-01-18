#pragma once
#include <cmath>
#include "Shape.h"

class Triangle : public Shape
{
public:

	float xP1 = 0.0f;
	float yP1 = std::sqrt(3.0f) / 10;

	float xP2 = -0.1f;
	float yP2 = 0.0f;

	float xP3 = 0.1f;
	float yP3 = 0.0f;

	float xP4 = 0.0f;
	float yP4 = yP1 * (1.0f / 3.0f);
	float zP4 = 0.13f;

	void draw();

};