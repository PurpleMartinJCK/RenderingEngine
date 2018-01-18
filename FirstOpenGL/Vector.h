#pragma once






class Vector3
{
public:
	Vector3();
	Vector3(float X, float Y, float Z);

	//vec1 
	Vector3 operator+(Vector3 vec2);
	Vector3 operator-(Vector3 vec2);

	Vector3 operator*(float scalar);
	Vector3 operator/(float scalar);
	
	float magnitude();

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;


};