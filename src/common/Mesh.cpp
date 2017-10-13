#include "Mesh.h"
#include "Common.h"
Mesh::SubMesh::SubMesh()
{
	VB = INVALID_GL_VALUE;
	IB = INVALID_GL_VALUE;
};

Mesh::SubMesh::~SubMesh()
{
	if (VB != INVALID_GL_VALUE)
	{
		glDeleteBuffers(1, &VB);
	}

	if (IB != INVALID_GL_VALUE)
	{
		glDeleteBuffers(1, &IB);
	}
}

void Mesh::SubMesh::InitOnGPU()
{
	size_t NumIndices = m_indices.size();
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::uv)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::normal)));

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &m_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::Mesh()
{
}


Mesh::~Mesh()
{

}

void Mesh::InitOnGPU()
{
	for (auto& submesh : m_entries)
	{
		submesh.InitOnGPU();
	}
	m_isLoadedOnGPU = true;
}

void Mesh::Draw()
{
	for (unsigned int i = 0; i < m_entries.size(); i++) {
		glBindVertexArray(m_entries.at(i).VAO);
		glDrawElements(GL_TRIANGLES, (GLsizei)m_entries[i].m_indices.size(), GL_UNSIGNED_INT, 0);
	}
}

std::vector<Mesh::SubMesh>& Mesh::GetEntries()
{
	return m_entries;
}

bool Mesh::IsLoadedOnGPU() const
{
	return m_isLoadedOnGPU;
}

void Mesh::SetIsLoadedOnGPU(const bool& isLoaded)
{
	m_isLoadedOnGPU = isLoaded;
}
