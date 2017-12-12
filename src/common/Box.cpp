#include "Box.h"

Box::Box(uint length, uint width, uint height)
{

}

Box::Box()
{

}

Box::~Box()
{

}

Mesh* Box::CreateBoxMesh(uint length, uint width, uint height)
{
	std::vector<Vertex> verts;
	std::vector<unsigned int> indices;
	int halfLengh = length / 2;
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	verts.push_back(Vertex(glm::vec3(-halfLengh, -halfHeight, -halfWidth), glm::vec2(0.0,0.0), glm::vec3(0.0,1.0,0.0)));

	return nullptr;
}
