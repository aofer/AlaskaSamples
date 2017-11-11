#pragma once
#include "IDemo.h"
#include "Common/ResourceManager.h"
#include "Common/Lighting.h"

class CubeMapCamera;

struct Material
{
	glm::vec4 diffuseColor;
	glm::vec4 specColor;
	glm::vec4 ambientColor;
	float shininess;
	float specularIntensity;
};


class SphericalHarmonicsDemo : public IDemo
{
private:
	
	MeshPtr m_room;
	ShaderProgramPtr m_shader;
	SpotLight m_spotLight;
	Material m_material;

	GLuint m_spotUBO;
	GLuint m_materialUBO;
	GLuint m_envMapTexture;
	GLuint m_fboId;
	CubeMapCamera* m_cubeCam;
	std::vector<glm::vec3> m_shCoeff[4];
	GLuint m_viewProjMatrixLocation;
	GLuint m_camPositionLocation;
	GLuint m_modelMatrixLocation;
	GLuint m_coeffLocation;
	unsigned int m_numOfBounces;
	glm::mat4x4 m_worldMatrix;


	void SphericalHarmonicsFromTexture(GLuint cubeTexture,
		std::vector<glm::vec3> & output, const unsigned int order);

	void SphericalHarmonicsAdd(float * result, int order,
		const float * inputA, const float * inputB);

	void SphericalHarmonicsScale(float * result, int order,
		const float * input, float scale);

	void SphericalHarmonicsEvaluateDirection(float * result, int order,
		const glm::vec3 & dir);

	void InitEnvironmentMapTexture();

	void InitEnvironmentRendering();

	void RenderEnvironmentMap(unsigned int coeffIndex);

	void RenderScene(const glm::vec3 &camPosition, const glm::mat4 &viewProjection, unsigned int coeffIndex);

	void BakeSphericalHarmonics();

public:
	virtual void InitializeScene(ResourceManager* manager);
	virtual void Update(float dt);
	virtual void Render(Camera* camera);

	SphericalHarmonicsDemo();

	virtual ~SphericalHarmonicsDemo();

	//Public setters for GUI
	void SetBounces(const int bounces);
};