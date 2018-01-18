#pragma once
#include "Random.h"
#include "Vector.h"

class Shape
{
public:

		Vector3 position{
	RandomRangef(-1.0f, 1.0f),
	RandomRangef(-1.0f, 1.0f),
	RandomRangef(-1.0f, 1.0f)
	};

	float radius = 0.05f;
	float mass = 1.0f;
	float friction = 0.99f;
	bool selected = false;

	float increment = 0.02f;

	Vector3 velocity{
	RandomRangef(-0.3f, 0.3f),
	RandomRangef(-0.3f, 0.3f),
	RandomRangef(-0.3f, 0.3f)
	};
	Vector3 acceleration;

	float incrementX = RandomRangef(0.0f, 0.03f);
	float incrementY = RandomRangef(0.0f, 0.03f);
	float incrementZ = RandomRangef(0.0f, 0.03f);

	float rotateXY = 0.0f;
	float rotateYZ = 0.0f;
	float rotateZX = 0.0f;
	float shearX = 0.0f;
	float shearY = 0.0f;
	float trans = 0.0f;
	float scale = 1.0f;

		
	void update(float deltaTime);
	void force(Vector3 f);
	// updates velocity for half of the frame
	void updateVel(float deltaTime);

	virtual void draw() = 0;

private:

	float rotateRandXY = 0.0f;
	float rotateRandYZ = 0.0f;
	float rotateRandZX = 0.0f;
	float shearRandX = 0.0f;
	float shearRandY = 0.0f;
	float trandRand = 0.0f;
	float scaleRand = 0.0f;

	bool isRotateXY = false;
	bool isRotateYZ = false;
	bool isRotateZX = false;
	bool isShearX = false;
	bool isShearY = false;
	bool isTrans = false;
	bool isScale = false;

};
