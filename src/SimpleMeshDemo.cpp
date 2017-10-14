#pragma once
#include "SimpleMeshDemo.h"
#include "Common/Camera.h"


void SimpleMeshDemo::InitializeScene(ResourceManager* manager)
{
	manager->LoadModel("Models\\ground.obj", "ground");
	manager->LoadModel("Models\\box.obj", "box");
	manager->LoadShader("Shaders\\simpleMesh_vs.glsl", "Shaders\\simpleMesh_fs.glsl", "", "simpleMesh");

	m_floor = manager->GetMesh("ground");
	m_box = manager->GetMesh("box");
	m_shader = manager->GetShader("simpleMesh");
	m_shader->Bind();
	m_viewMatrixULocation = glGetUniformLocation(m_shader->GetProgram(), "viewMatrix");
	m_projMatrixULocation = glGetUniformLocation(m_shader->GetProgram(), "projectionMatrix");


}

void SimpleMeshDemo::Update(float dt)
{

}

void SimpleMeshDemo::Render(Camera* camera)
{
	m_shader->Bind();
	glUniformMatrix4fv(m_viewMatrixULocation, 1, GL_FALSE, &camera->GetView()[0][0]);
	glUniformMatrix4fv(m_projMatrixULocation, 1, GL_FALSE, &camera->GetProjection()[0][0]);
	//m_floor->Draw();
	m_box->Draw();


}
