#pragma once
#include <glm/glm.hpp>

class Camera {
	private:

	float fieldOfView;
	float aspectRatio;
	float zNear;
	float zFar;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 viewProjectionMatrix;

protected:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 lookAt;
	void UpdateMatrices();

public:

	//constructor
	Camera();
	Camera(float fieldOfView, float aspectRatio, float near, float far);
	//destructor
	~Camera();
	//setters
	void SetPosition(glm::vec3 position);
	void SetUp(glm::vec3 up);
	void SetLookAt(glm::vec3 lookAt);
	void SetFieldOfView(float fov);
	void SetAspectRatio(float aspectRatio);
	void SetNear(float near);
	void SetFar(float far);
	//getters
	glm::vec3 GetPosition() const;
	glm::vec3 GetUp() const;
	glm::vec3 GetForward();
	glm::vec3 GetRight();
	glm::vec3 GetLookAt() const;
	float GetFieldOfView() const;
	float GetAspectRatio() const;
	float GetNear() const;
	float GetFar() const;
	glm::mat4 GetProjection() const;
	glm::mat4 GetView() const;
	glm::mat4 GetViewProjection() const;



	virtual void Update(float dt);

};

