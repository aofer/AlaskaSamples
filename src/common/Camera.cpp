#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(float fieldOfView, float aspectRatio, float near, float far) : fieldOfView(fieldOfView), aspectRatio(aspectRatio), zNear(near), zFar(far)
{
	up = glm::vec3(0.0, 1.0, 0.0);
	position = glm::vec3(0.0, 0.0, 0.0);
	lookAt = glm::vec3(0.0, 0.0, -1.0);
}

Camera::Camera() : Camera(45.0f, 4.0f / 3.0f, 0.1f, 100.0f)
{

}

Camera::~Camera()
{

}

void Camera::Update(float dt)
{

}

//setters
void Camera::SetPosition(glm::vec3 position)
{
	this->position = position;
	UpdateMatrices();
}

void Camera::SetUp(glm::vec3 up){
	this->up = up;
	UpdateMatrices();

}

void Camera::SetLookAt(glm::vec3 lookAt)
{
	this->lookAt = lookAt;
	UpdateMatrices();
}

void Camera::SetFieldOfView(float fov)
{
	this->fieldOfView = fov;
	UpdateMatrices();
}

void Camera::SetAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
	UpdateMatrices();
}

void Camera::SetNear(float near)
{
	this->zNear = near;
	UpdateMatrices();
}

void Camera::SetFar(float far)
{
	this->zFar = far;
	UpdateMatrices();
}

//getters
glm::vec3 Camera::GetPosition() const
{
	return position;
}

glm::vec3 Camera::GetUp() const
{
	return up;
}

glm::vec3 Camera::GetLookAt() const
{
	return lookAt;
}

float Camera::GetFieldOfView() const
{
	return fieldOfView;
}

float Camera::GetAspectRatio() const
{
	return aspectRatio;
}

float Camera::GetNear() const
{
	return zNear;
}

float Camera::GetFar() const
{
	return zFar;
}
//returns the normalized forward vector
glm::vec3 Camera::GetForward()
{
	glm::vec3 fVector = glm::normalize(lookAt - position);
	return fVector;
}

glm::vec3 Camera::GetRight()
{
	return glm::cross(glm::normalize(up),GetForward());
}

glm::mat4 Camera::GetProjection() const
{
	return projectionMatrix;
}
glm::mat4 Camera::GetView() const
{
	return viewMatrix;
}
glm::mat4 Camera::GetViewProjection() const
{
	return viewProjectionMatrix;
}


void Camera::UpdateMatrices()
{

	projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, zNear, zFar);

	viewMatrix = glm::lookAt(position, lookAt, up);
	viewProjectionMatrix = projectionMatrix * viewMatrix;

}
