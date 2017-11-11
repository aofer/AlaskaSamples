#pragma once

#include <glm/glm.hpp>


struct DirectionalLight
{
	glm::vec4 Color;
	glm::vec4 Position;
	glm::vec4 Direction;
	float AmbientIntensity;
	float DiffuseIntensity;
};

struct PointLight
{
	glm::vec4 Color;
	glm::vec4 Position;
	float AmbientIntensity;
	float DiffuseIntensity;
	float ConstAtten;
	float LinearAtten;
	float ExpAtten;
};

struct SpotLight
{
	glm::vec4 Color;
	glm::vec4 Position;
	glm::vec4 Direction;
	float AmbientIntensity;
	float DiffuseIntensity;
	float ConstAtten;
	float LinearAtten;
	float ExpAtten;
	float Cutoff;
};
