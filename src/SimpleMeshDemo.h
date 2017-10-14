#pragma once
#include "IDemo.h"
#include "Common/ResourceManager.h"
class SimpleMeshDemo : public IDemo
{
private:
	MeshPtr m_floor;
	MeshPtr m_box;
	ShaderProgramPtr m_shader;
	GLuint m_viewMatrixULocation;
	GLuint m_projMatrixULocation;

public:
	virtual void InitializeScene(ResourceManager* manager);
	virtual void Update(float dt);
	virtual void Render(Camera* camera);
};