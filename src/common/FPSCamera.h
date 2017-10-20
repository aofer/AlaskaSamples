#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
/*
This class represents a basic camera with all of its camera controls
*/

class FPSCamera : public Camera {
private:

public:

	//constructor
	FPSCamera();
	FPSCamera(float fieldOfView, float aspectRatio, float near, float far);
	//destructor
	~FPSCamera();


	//this method is used to move the camera forward and backwards in our scene
	void moveForward(float speed);
	//this method changes the pitch of the camera
	void pitch(float angle);
	//this method changes the yaw of the camera
	void yaw(float angle);
	//this method moves the camera left and right, like in an FPS game
	void strafe(float speed);
	//this method moves the camera up and down
	void liftUp(float speed);
	//this is the most important method in the camera, its used on our display function to update the camera matrices in openGL

	virtual void Update(float dt);

};

