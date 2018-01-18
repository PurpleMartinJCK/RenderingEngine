#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.h"
#include <fstream>	
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\SOIL\include\SOIL.h"

#include <cmath>

bool Mesh::load(std::string meshFile, std::string textureFile)
{
	// load texture
	int width = 0;
	int height = 0;
	int channels = 0;

	unsigned char *image = SOIL_load_image(textureFile.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

	if (image == nullptr)
	{
		return false;
	}

	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	if (channels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(image);

	// load mesh
	radius = 0.0f;

	std::ifstream reader;	
	reader.open(meshFile);

	if (!reader)
	{
		// if this happened the file didn't open right
		return false;
	}

	// we load lines in one by one then process it
	char line[128] = { '\0' } ;

	std::vector<Vector3> vertexData;
	std::vector<Vector3> texCoordData;
	std::vector<Vector3> normalData;

	while (!reader.eof())
	{
		reader.getline(line, 128);

		if (std::strstr(line, "#") != nullptr)
		{
			continue;
		}
		else if (std::strstr(line, "vn") != nullptr)
		{
			Vector3 temp;
			std::sscanf(line, "vn %f %f %f", &temp.x, &temp.y, &temp.z);
			normalData.push_back(temp); 
		}
		else if (std::strstr(line, "vt") != nullptr)
		{
			Vector3 temp;
			std::sscanf(line, "vt %f %f", &temp.x, &temp.y);
			texCoordData.push_back(temp);
		}
		else if (std::strstr(line, "v") != nullptr)
		{
			Vector3 temp;
			std::sscanf(line, "v %f %f %f", &temp.x, &temp.y, &temp.z);
			vertexData.push_back(temp);

			radius = std::fmaxf(radius * 0.1f, temp.magnitude() * 0.1f);
		}
		else if (std::strstr(line, "f") != nullptr)
		{
			Face temp;

			std::sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u",
				&temp.vertices[0], &temp.texCoords[0], &temp.normals[0],
				&temp.vertices[1], &temp.texCoords[1], &temp.normals[1],
				&temp.vertices[2], &temp.texCoords[2], &temp.normals[2]);

			triangles.push_back(temp);
		}
	}

	reader.close();

	for (int i = 0; i < triangles.size(); i++)
	{
		//for each vertex in a triangle
		for (int j = 0; j < 3; j++)
		{
			triangles[i].vertex[j] = vertexData[triangles[i].vertices[j] - 1];

			triangles[i].texCoord[j] = texCoordData[triangles[i].texCoords[j] - 1];

			triangles[i].normal[j] = normalData[triangles[i].normals[j] - 1];
		}
	}

	return true;
}

void Mesh::draw()
{

	float shearMatrix[] = {
		1.0f, shearX, 0.0f, 0.0f,
		shearY, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);
	//glRotatef(rotateXY, rotateYZ, rotateZX, 1.0f);
	//glMultMatrixf(shearMatrix);
	glScalef(0.1f, 0.1f, 0.1f);

	if (!selected)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < triangles.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			glTexCoord2f(
				triangles[i].texCoord[j].x,
				triangles[i].texCoord[j].y);

			if (selected)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}

			glNormal3f(
				triangles[i].normal[j].x,
				triangles[i].normal[j].y,
				triangles[i].normal[j].z);

			glVertex3f(
				triangles[i].vertex[j].x,
				triangles[i].vertex[j].y,
				triangles[i].vertex[j].z);
		}
	}

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();


}