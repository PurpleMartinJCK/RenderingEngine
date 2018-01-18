#pragma once
#include "Shape.h"
#include "Vector.h"
#include <string>
#include <vector>

class Face
{
public:
	
	int vertices[3] = { 0 };
	int texCoords[3] = { 0 };
	int normals[3] = { 0 };

	Vector3 vertex[3];
	Vector3 texCoord[3]; // ignore z
	Vector3 normal[3];

};

class Mesh : public Shape
{
public:

	bool load(std::string meshFile, std::string textureFile);

	void draw();

private:
	std::vector<Face> triangles;

	unsigned int textureHandle = 0;
};