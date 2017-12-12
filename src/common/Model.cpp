#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


Model::Model() : m_mesh(nullptr)
{
	m_scale = glm::vec3(1.0);
	m_rotation = glm::quat(0.0,0.0,0.0,0.0);
	m_position = glm::vec3(0.0);
}

Model::~Model()
{
	SAFE_DELETE(m_mesh);
}

glm::mat4 Model::GetModelMatrix() const
{
	glm::mat4 modelMatrix;
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0), m_scale);
	glm::mat4 rotationMatrix = glm::toMat4(m_rotation);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), m_position);
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	return modelMatrix;
}
