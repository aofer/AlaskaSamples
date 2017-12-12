#include "Terrain.h"

void Terrain::Initialize(ResourceManager* manager)
{
	m_shader = manager->LoadShader("Shaders\\terrain_vs.glsl", "Shaders\\terrain_fs.glsl", "Shaders\\terrain_gs.glsl", "Shaders\\terrain_tes.glsl", "Shaders\\terrain_tcs.glsl", "terrain");
	m_heightMap = manager->LoadTexture2D("Textures\\heightMap.jpg", "heightMap");
	m_gridsize = glm::ivec2(64, 64);
	m_size = glm::vec2(1000.0f, 1000.0f);  //1km
	m_patchCount = m_gridsize.x * m_gridsize.y;

	//set uniform locations
	m_viewMatrixLocation = glGetUniformLocation(m_shader->GetProgram(), "viewMatrix");
	m_projMatrixLocation = glGetUniformLocation(m_shader->GetProgram(), "projMatrix");

	glPatchParameteri(GL_PATCH_VERTICES, 4); //Sets the number of input for the tes to be 4
}

void Terrain::Update(float dt)
{

}

void Terrain::Render(Camera* camera)
{
	m_shader->Bind();
	m_heightMap->Bind(GL_TEXTURE0);

	//set uniforms

	glDrawArraysInstanced(GL_PATCHES, 0, 4, m_patchCount);
}
