#pragma once
#include "IDemo.h"
#include "Common/ResourceManager.h"

class Terrain;

class TerrainTesselationDemo : public IDemo
{
private:

	Terrain* m_terrain;

public:
	virtual void InitializeScene(ResourceManager* manager);
	virtual void Update(float dt);
	virtual void Render(Camera* camera);

};