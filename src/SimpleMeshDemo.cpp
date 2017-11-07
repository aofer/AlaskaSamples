#pragma once
#include "SimpleMeshDemo.h"
#include "Common/Camera.h"


void SimpleMeshDemo::InitializeScene(ResourceManager* manager)
{
	m_floor = manager->LoadMesh("Models\\ground.obj", "ground");
	m_box = manager->LoadMesh("Models\\box.obj", "box");
	m_shader = manager->LoadShader("Shaders\\simpleMesh_vs.glsl", "Shaders\\simpleMesh_fs.glsl", "", "simpleMesh");
	m_texture = manager->LoadTexture("Textures\\checkers.png", "checkers");
	m_shader->Bind();
	m_viewMatrixULocation = glGetUniformLocation(m_shader->GetProgram(), "viewMatrix");
	m_projMatrixULocation = glGetUniformLocation(m_shader->GetProgram(), "projectionMatrix");
	GLuint tTextureLocation = glGetUniformLocation(m_shader->GetProgram(), "texSampler");
	glUniform1i(tTextureLocation, 0);

	//UBO stuff
	m_colors.colorA = glm::vec4(0.5, 0.2, 1.0,0.0);
	m_colors.colorB = glm::vec4(1.0, 0.0, 0.2,0.0);
	m_colors.colorC = glm::vec4(0.7, 0.3, 0.6,0.0);



	GLuint blockIndex = glGetUniformBlockIndex(m_shader->GetProgram(),"colorsUniform");
	glGenBuffers(1, &m_colorUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, m_colorUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(m_colors), &m_colors, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	GLuint binding_point_index = 2;
	glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, m_colorUBO);
	glUniformBlockBinding(m_shader->GetProgram(), blockIndex, binding_point_index);


}

void SimpleMeshDemo::SetColors(glm::vec4 colorA, glm::vec4 colorB, glm::vec4 colorC)
{
	m_colors.colorA = colorA;
	m_colors.colorB = colorB;
	m_colors.colorC = colorC;

}

void SimpleMeshDemo::Update(float dt)
{
	//m_colors.colorA += (dt * 0.1);
	
	//update colors from UBO
	glBindBuffer(GL_UNIFORM_BUFFER, m_colorUBO);
	GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	memcpy(p, &m_colors, sizeof(m_colors));
	glUnmapBuffer(GL_UNIFORM_BUFFER);
}

void SimpleMeshDemo::Render(Camera* camera)
{

	m_shader->Bind();
	m_texture->Bind(0);
	glUniformMatrix4fv(m_viewMatrixULocation, 1, GL_FALSE, &camera->GetView()[0][0]);
	glUniformMatrix4fv(m_projMatrixULocation, 1, GL_FALSE, &camera->GetProjection()[0][0]);



	//m_floor->Draw();
	m_box->Draw();


}
