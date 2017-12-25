#include "Terrain.h"
#include "Camera.h"
void Terrain::Initialize(ResourceManager* manager)
{
	m_shader = manager->LoadShader("Shaders\\terrain_vs.glsl", "Shaders\\terrain_fs.glsl", "Shaders\\terrain_gs.glsl", "Shaders\\terrain_tes.glsl", "Shaders\\terrain_tcs.glsl", "terrain");
	m_heightMap = manager->LoadTexture2D("Textures\\height16bit1.png", "heightMap",ImageFormat::IMAGE_FORMAT_R16);
	m_colorMap = manager->LoadTexture2D("Textures\\checkers.png", "checkers");
	
	m_gridsize = glm::ivec2(64, 64);
	m_size = glm::vec2(10.0f, 10.0f);  //1km
	m_patchCount = m_gridsize.x * m_gridsize.y;
	m_displacementScale = 1.0f;

	m_shader->Bind();
	//set uniform locations
	m_viewMatrixLocation = glGetUniformLocation(m_shader->GetProgram(), "viewMatrix");
	m_projMatrixLocation = glGetUniformLocation(m_shader->GetProgram(), "projMatrix");
	m_gridSizeLocation = glGetUniformLocation(m_shader->GetProgram(), "gridSize");
	m_sizeLocation = glGetUniformLocation(m_shader->GetProgram(), "terrainSize");
	m_displacementScaleLocation = glGetUniformLocation(m_shader->GetProgram(), "displacementScale");
	//m_tessellatedTriWidthLocation = glGetUniformLocation(m_shader->GetProgram(), "tessellatedTriWidth");
	m_patchCountLocation = glGetUniformLocation(m_shader->GetProgram(), "patchCount");
	m_cameraPositionLocation = glGetUniformLocation(m_shader->GetProgram(), "cameraPosition");
	m_heightMapLocation = glGetUniformLocation(m_shader->GetProgram(), "displacementTexture");
	m_colorMapLocation = glGetUniformLocation(m_shader->GetProgram(), "colorTexture");

	glUniform1i(m_heightMapLocation, 0);
	glUniform1i(m_colorMapLocation, 1);

	glPatchParameteri(GL_PATCH_VERTICES, 4); //Sets the number of input for the tes to be 4

}

void Terrain::Update(float dt)
{

}

void Terrain::Render(Camera* camera)
{
	m_shader->Bind();
	m_heightMap->Bind(GL_TEXTURE0);
	m_colorMap->Bind(GL_TEXTURE1);

	//set uniforms
	glUniform2i(m_gridSizeLocation, m_gridsize.x, m_gridsize.y);
	glUniform1f(m_displacementScaleLocation, m_displacementScale);
	glUniform2f(m_sizeLocation, m_size.x, m_size.y);
	//glUniform1f(m_tessellatedTriWidthLocation, m_tessellatedTriWidth);
	//glUniform3fv(m_cameraPositionLocation, 1, &camera->GetPosition()[0]);
	glUniform3f(m_cameraPositionLocation, camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

	glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE,&camera->GetView()[0][0]);
	glUniformMatrix4fv(m_projMatrixLocation, 1, GL_FALSE,&camera->GetProjection()[0][0]);

	glDrawArraysInstanced(GL_PATCHES, 0, 4, m_patchCount);
}

void Terrain::SetTerrainSize(const int& size)
{
	m_size = glm::vec2(size,size);
}

void Terrain::SetDisplacementScale(const float& scale)
{
	m_displacementScale = scale;
}

void Terrain::SetGridSize(const int& size)
{
	m_gridsize = glm::ivec2(size,size);
	m_patchCount = m_gridsize.x * m_gridsize.y;
}
