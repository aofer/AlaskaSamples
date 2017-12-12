#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Common.h"
#include "Mesh.h"


class Model {

private:

	glm::vec3 m_scale;
	glm::vec3 m_position;
	glm::quat m_rotation;
	Mesh* m_mesh;

	//GLfloat* m_verts;
	//GLfloat* m_normals;
	//GLfloat* m_uvs;
	//GLshort* m_indices;


public:
	
	Model();
	virtual ~Model();

	glm::vec3 GetScale() const { return m_scale; }
	void SetScale(const glm::vec3& val) { m_scale = val; }
	glm::vec3 GetPosition() const { return m_position; }
	void SetPosition(const glm::vec3& val) { m_position = val; }
	glm::quat GetRotation() const { return m_rotation; }
	void SetRotation(const glm::quat& val) { m_rotation = val; }

	glm::mat4 GetModelMatrix() const;

	Mesh* GetMesh() const { return m_mesh; }
	void SetMesh(Mesh* val) { m_mesh = val; }



};

