#include "FPSCamera.h"
//#include <glm/gtx/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h> //TODO remove this dependency




	FPSCamera::FPSCamera(float fieldOfView, float aspectRatio, float near, float far) : Camera(fieldOfView, aspectRatio, near, far)
	{

	}

	FPSCamera::FPSCamera() : FPSCamera(45.0f, 4.0f / 3.0f, 0.1f, 100.0f)
	{

	}

	FPSCamera::~FPSCamera()
	{

	}

	void FPSCamera::Update(float dt)
	{

	}
	
	void FPSCamera::moveForward(float speed)
	{
		// Get the current view vector (the direction we are looking)
		glm::vec3 vVector = GetForward();

		position.x += vVector.x * speed;		// Add our acceleration to our position's X
		position.z += vVector.z * speed;		// Add our acceleration to our position's Z
		lookAt.x += vVector.x * speed;			// Add our acceleration to our view's X
		lookAt.z += vVector.z * speed;			// Add our acceleration to our view's Z
		UpdateMatrices();
	}


	void FPSCamera::pitch(float angle)
	{
		float PI = glm::pi<float>();
		float amount = std::sinf(angle * PI / 180);
		lookAt.y += amount;
		UpdateMatrices();
	}
	void FPSCamera::yaw(float angle)
	{
		float PI = glm::pi<float>();
		glm::vec3 rightVec = GetRight();
		float radians = angle* PI / 180;
		lookAt.x = position.x + (lookAt.x - position.x) * std::cosf(radians) + (lookAt.z - position.z) * std::sinf(radians);
		lookAt.z = position.z + (lookAt.z - position.z) * std::cosf(radians) + (position.x - lookAt.x) * std::sinf(radians);
		UpdateMatrices();
	}



	void FPSCamera::strafe(float speed)
	{
		// Get our normalized right vector (The direction perpendicular to our view)
		glm::vec3 rightVector = GetRight();

		// Move our FPSCamera position right or left along the right vector
		position.x += rightVector.x * speed;
		lookAt.x += rightVector.x * speed;
		position.z += rightVector.z * speed;
		lookAt.z += rightVector.z * speed;
		UpdateMatrices();
	}

	void FPSCamera::liftUp(float speed)
	{
		position.y += speed;
		lookAt.y += speed;
		UpdateMatrices();
	}



