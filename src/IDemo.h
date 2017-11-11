#pragma once

class Camera;
class FPSCamera;
class ResourceManager;

class IDemo
{
public:
	IDemo() : m_camera(nullptr) {}
	virtual void InitializeScene(ResourceManager* manager) = 0;
	virtual void Update(float dt) = 0;
	//if we want to render from a different camera than the internal demo one
	virtual void Render(Camera* camera) = 0;

	FPSCamera* GetDemoCamera() const { return m_camera; }
protected:
	FPSCamera* m_camera;
};