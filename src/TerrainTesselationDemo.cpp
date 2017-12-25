#include "TerrainTesselationDemo.h"
#include "Common/Camera.h"
#include "common/Terrain.h"

void TerrainTesselationDemo::InitializeScene(ResourceManager* manager)
{
	m_terrain = new Terrain();
	m_terrain->Initialize(manager);

}

void TerrainTesselationDemo::Update(float dt)
{
	m_terrain->Update(dt);
}

void TerrainTesselationDemo::Render(Camera* camera)
{
	m_terrain->Render(camera);
}

void TerrainTesselationDemo::SetTerrainSize(const int& size)
{
	m_terrain->SetTerrainSize(size);
}

void TerrainTesselationDemo::SetDisplacementScale(const float& scale)
{
	m_terrain->SetDisplacementScale(scale);
}

void TerrainTesselationDemo::SetGridSize(const int& size)
{
	m_terrain->SetGridSize(size);
}
