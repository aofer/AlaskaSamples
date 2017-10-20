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

}

void SimpleMeshDemo::Update(float dt)
{

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
