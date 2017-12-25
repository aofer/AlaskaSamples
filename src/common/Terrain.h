#pragma once
#include "ResourceManager.h"

class Camera;

class Terrain
{

public:
	void Initialize(ResourceManager* manager);
	virtual void Update(float dt);
	virtual void Render(Camera* camera);

	void SetTerrainSize(const int& size);
	void SetDisplacementScale(const float& scale);
	void SetGridSize(const int& size);
private:

	ShaderProgramPtr m_shader;
	Texture2DPtr m_heightMap;
	Texture2DPtr m_colorMap;

	float m_displacementScale;
	float m_tessellatedTriWidth;
	glm::ivec2 m_gridsize;
	glm::vec2 m_size;
	int m_patchCount;

	bool m_drawWireframe;

	//Locations
	GLuint m_viewMatrixLocation;
	GLuint m_projMatrixLocation;
	GLuint m_gridSizeLocation;
	GLuint m_sizeLocation;
	GLuint m_displacementScaleLocation;
	GLuint m_tessellatedTriWidthLocation;
	GLuint m_patchCountLocation;
	GLuint m_cameraPositionLocation;
	GLuint m_heightMapLocation;
	GLuint m_colorMapLocation;

};