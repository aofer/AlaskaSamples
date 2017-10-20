#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
/*
This class represents a basic camera with all of its camera controls
*/

class CubeMapCamera : public Camera{
private:


public:
	
	CubeMapCamera(glm::vec3 camPosition);

	void SetCameraToFace(int faceIndex);

	//virtual void Update(float dt);

};


