#pragma once

class Camera;
class ResourceManager;

class IDemo
{
public:
	virtual void InitializeScene(ResourceManager* manager) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(Camera* camera) = 0;
};