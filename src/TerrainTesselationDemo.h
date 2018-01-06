#pragma once
#include "IDemo.h"
#include "Common/ResourceManager.h"

class Terrain;

class TerrainTesselationDemo : public IDemo
{
private:

	Terrain* m_terrain;
	//glm::ivec2 m_windowSize;


public:
	virtual void InitializeScene(ResourceManager* manager);
	virtual void Update(float dt);
	virtual void Render(Camera* camera);

	void SetTerrainSize(const int& size);
	void SetDisplacementScale(const float& scale);
	void SetGridSize(const int& size);
	//set the window size for wireframe drawing
	void SetWindowSize(const glm::ivec2& size);
	void SetWireframe(const bool &enableWireframe);
};