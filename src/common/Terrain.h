#pragma once
#include "ResourceManager.h"

class Camera;

class Terrain
{

public:
	void Initialize(ResourceManager* manager);
	virtual void Update(float dt);
	virtual void Render(Camera* camera);

private:

	ShaderProgramPtr m_shader;
	Texture2DPtr m_heightMap;

	float m_displacementScale;
	float m_tessellatedTriWidth;
	glm::ivec2 m_gridsize;
	glm::vec2 m_size;
	int m_patchCount;

	bool m_drawWireframe;

	//Locations
	GLuint m_viewMatrixLocation;
	GLuint m_projMatrixLocation;

};