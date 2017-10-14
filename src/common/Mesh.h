#pragma once
#include <map>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>




struct Vertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;

	Vertex(glm::vec3 pos, glm::vec2 uv, glm::vec3 normal)
	{
		this->position = pos;
		this->uv = uv;
		this->normal = normal;
	}
};

class Mesh
{



public:
	Mesh();
	~Mesh();

	void InitOnGPU();

	void Draw();



private:


	struct SubMesh {
		SubMesh();

		~SubMesh();

		void InitOnGPU();

		GLuint VB;
		GLuint IB;
		GLuint VAO;

		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;

	};

	std::vector<SubMesh>		m_entries;
	bool						m_isLoadedOnGPU;

public:
	std::vector<SubMesh>& GetEntries();
	bool IsLoadedOnGPU() const;
	void SetIsLoadedOnGPU(const bool& isLoaded);

};

