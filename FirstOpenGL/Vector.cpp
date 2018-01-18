#include "Vector.h"
#include <cmath>

Vector3::Vector3() {}
Vector3::Vector3(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}


Vector3 Vector3::operator+(Vector3 vec2) 
{
	return Vector3(x + vec2.x, y + vec2.y, z + vec2.z);
}
Vector3 Vector3::operator-(Vector3 vec2) 
{
	return Vector3(x - vec2.x, y - vec2.y, z - vec2.z);
}

Vector3 Vector3::operator*(float scalar)
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}
Vector3 Vector3::operator/(float scalar)
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

float Vector3::magnitude()
{
	return std::sqrt(x * x + y * y + z * z);
}