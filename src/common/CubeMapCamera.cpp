#include "CubeMapCamera.h"


CubeMapCamera::CubeMapCamera(glm::vec3 camPosition): Camera()
{
	SetFieldOfView(90.0);
	SetAspectRatio(1.0);
	position = camPosition;
	lookAt = camPosition + glm::vec3(1.0, 0.0, 0.0);
	UpdateMatrices();
}


void CubeMapCamera::SetCameraToFace(int faceIndex)
{
	glm::vec3 camPosition = GetPosition();
	switch (faceIndex)
	{
	case 0:
		SetUp(glm::vec3(0.0, 1.0, 0.0));
		SetLookAt(camPosition + glm::vec3(1.0, 0.0, 0.0));
		break;
	case 1:
		SetUp(glm::vec3(0.0, 1.0, 0.0));
		SetLookAt(camPosition + glm::vec3(-1.0, 0.0, 0.0));
		break;
	case 2:
		SetUp(glm::vec3(0.0, 0.0, -1.0));
		SetLookAt(camPosition + glm::vec3(0.0, 1.0, 0.0));
		break;
	case 3:
		SetUp(glm::vec3(0.0, 0.0, 1.0));
		SetLookAt(camPosition + glm::vec3(0.0, -1.0, 0.0));
		break;
	case 4:
		SetUp(glm::vec3(0.0, 1.0, 0.0));
		SetLookAt(camPosition + glm::vec3(0.0, 0.0, 1.0));
		break;
	case 5:
		SetUp(glm::vec3(0.0, 1.0, 0.0));
		SetLookAt(camPosition + glm::vec3(0.0, 0.0, -1.0));
		break;
	}


}
