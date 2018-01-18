#include "Shape.h"
#include <cmath>

void Shape::update(float deltaTime)
{
	// will swap the shape direction if the origin vertex goes to an edge
	if (position.x <= -1)
	{
		velocity.x = std::fabs(velocity.x);
		force(velocity * (velocity.magnitude() / 0.2f) * 0.5f);

	}
	else if (position.x >= 1)
	{
		velocity.x = std::fabs(velocity.x) * -1.0f;
		force(velocity * (velocity.magnitude() / 0.2f) * 0.5f);
	}

	if (position.y <= -1)
	{
		velocity.y = std::fabs(velocity.y);
		force(velocity * (velocity.magnitude() / 0.2f) * 0.5f);
	}
	else if (position.y >= 1)
	{
		velocity.y = std::fabs(velocity.y) * -1.0f;
		force(velocity * (velocity.magnitude() / 0.2f) * 0.5f);
	}

	if (position.z <= -1)
	{
		velocity.z = std::fabs(velocity.z);
		force(velocity * (velocity.magnitude() / 0.2f) * 0.5f);
	}
	else if (position.z >= 1)
	{
		velocity.z = std::fabs(velocity.z) * -1.0f;
		force(velocity * (velocity.magnitude() / 0.2f) * 0.5f);
	}

	if (velocity.magnitude() >= 0.02f)
	{
		force(velocity * (velocity.magnitude() / 0.2f) * -1.0f);
	}
	else
	{
		velocity = velocity * 0.0f;
		acceleration = acceleration * 0.0f;
	}
	//velocity = velocity + (acceleration) / 2 * deltaTime;

	//position = position + velocity * deltaTime;

	position = position + velocity * deltaTime + (acceleration * deltaTime * deltaTime) * 0.5f;

	//velocity = velocity * 0.99f;

	// randomises rotation
	if (isRotateXY)
	{
		if (rotateRandXY > 0.01f)
		{
			rotateXY += increment;
			rotateRandXY -= increment;
		}
		else if (rotateRandXY < -0.01f)
		{
			rotateXY -= increment;
			rotateRandXY += increment;
		}
		else
		{
			isRotateXY = false;
			rotateRandXY = 0.0f;
		}

		if (rotateXY > 360.0f)
		{
			rotateXY -= 360.0f;
		}

	}
	else if (RandomRangei(0, 10000) == 1)
	{
		isRotateXY = true;
		rotateRandXY = RandomRangef(-200, 200);
	}

	if (isRotateYZ)
	{


		if (rotateRandYZ > 0.01f)
		{
			rotateYZ += increment;
			rotateRandYZ -= increment;
		}
		else if (rotateRandYZ < -0.01f)
		{
			rotateYZ -= increment;
			rotateRandYZ += increment;
		}
		else
		{
			isRotateYZ = false;
			rotateRandYZ = 0.0f;
		}

		if (rotateYZ > 360.0f)
		{
			rotateYZ -= 360.0f;
		}

	}
	else if (RandomRangei(0, 100) == 1)
	{
		isRotateYZ = true;
		rotateRandYZ = (float)(RandomRangei(-20, 20) * 10);
	}

	if (isRotateZX)
	{


		if (rotateRandZX > 0.01f)
		{
			rotateZX += increment;
			rotateRandZX -= increment;
		}
		else if (rotateRandZX < -0.01f)
		{
			rotateZX -= increment;
			rotateRandZX += increment;
		}
		else
		{
			isRotateZX = false;
			rotateRandZX = 0.0f;
		}

		if (rotateZX > 360.0f)
		{
			rotateZX -= 360.0f;
		}

	}
	else if (RandomRangei(0, 10000) == 1)
	{
		isRotateZX = true;
		rotateRandZX = RandomRangef(-200, 200);
	}
	// randomises scale
	if (isScale)
	{
		if (scale <= 0.1f)
		{
			scaleRand = 0.05f;
		}


		if (scaleRand > 0.01f)
		{
			scale += increment;
			scaleRand -= increment;
		}
		else if (scaleRand < -0.01f)
		{
			scale -= increment / 1000;
			scaleRand += increment / 1000;
		}
		else
		{
			isScale = false;
			scaleRand = 0.0f;
		}

	}
	else if (RandomRangei(0, 10000) == 1)
	{
		isScale = true;
		scaleRand = RandomRangef(-1.0f, 1.0f);

		if (scale < 0.5f)
		{
			scaleRand = std::fabs(scaleRand);
		}
		else if (scale > 1.5f)
		{
			scaleRand = -std::fabs(scaleRand);
		}

	}
	// randomises shear for X
	if (isShearX)
	{

		if (shearRandX > 0.01f)
		{
			shearX += increment / 1000;
			shearRandX -= increment / 1000;
		}
		else if (shearRandX < -0.01f)
		{
			shearX -= increment;
			shearRandX += increment;
		}
		else
		{
			isShearX = false;
			shearRandX = 0.0f / 1000;
		}

	}
	else if (RandomRangei(0, 10000) == 1)
	{
		isShearX = true;
		shearRandX = RandomRangef(-2.0f, 2.0f);

		if (shearX < -2.0f)
		{
			shearRandX = std::fabs(scaleRand);
		}
		else if (shearX > 2.0f)
		{
			shearRandX = -std::fabs(scaleRand);
		}

	}
	// randomises shear for Y
	if (isShearY)
	{

		if (shearRandY > 0.01f)
		{
			shearY += increment / 1000;
			shearRandY -= increment / 1000;
		}
		else if (shearRandY < -0.01f)
		{
			shearY -= increment / 1000;
			shearRandY += increment / 1000;
		}
		else
		{
			isShearY = false;
			shearRandY = 0.0f;
		}

	}
	else if (RandomRangei(0, 10000) == 1)
	{
		isShearY = true;
		shearRandY = RandomRangef(-1.5f, 1.5f);

		if (shearY < -2.0f)
		{
			shearRandY = std::fabs(scaleRand);
		}
		else if (shearY > 2.0f)
		{
			shearRandY = -std::fabs(scaleRand);
		}
							
	}

}

void Shape::force(Vector3 f)
{
	acceleration = acceleration + f / mass;
}

void Shape::updateVel(float deltaTime)
{
	velocity = velocity + acceleration * deltaTime * 0.5f;
}
