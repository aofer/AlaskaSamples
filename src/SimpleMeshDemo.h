#pragma once
#include "IDemo.h"
#include "Common/ResourceManager.h"
class SimpleMeshDemo : public IDemo
{
private:
	MeshPtr m_floor;
	MeshPtr m_box;
	ShaderProgramPtr m_shader;
	TexturePtr m_texture;
	GLuint m_viewMatrixULocation;
	GLuint m_projMatrixULocation;

	//UBO test
	GLuint m_colorUBO;

	struct colors
	{
		glm::vec3 colorA;
		glm::vec3 colorB;
		glm::vec3 colorC;

	};

	colors m_colors;

public:
	virtual void InitializeScene(ResourceManager* manager);
	virtual void Update(float dt);
	virtual void Render(Camera* camera);

	void SetColors(glm::vec4 colorA, glm::vec4 colorB, glm::vec4 colorC);
};