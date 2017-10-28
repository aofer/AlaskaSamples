#pragma once
#include "IDemo.h"
#include "Common/ResourceManager.h"
#include "Common/Lighting.h"

class CubeMapCamera;

class SphericalHarmonicsDemo : public IDemo
{
private:
	
	MeshPtr m_room;
	ShaderProgramPtr m_shader;
	SpotLight m_spotLight;

	GLuint m_spotUBO;
	GLuint m_envMapTexture;
	GLuint m_fboId;
	CubeMapCamera* m_cubeCam;
	std::vector<glm::vec3> m_shCoeff[4];
	GLuint m_viewMatrixULocation;
	GLuint m_projMatrixULocation;
	unsigned int m_numOfBounces;

	//TODO remove this struct and replace with UBO
	struct LightUniformLocations
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;
		GLuint direction;
		GLuint position;

	} m_lightLoc;

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
	void BakeSphericalHarmonics();

public:
	virtual void InitializeScene(ResourceManager* manager);
	virtual void Update(float dt);
	virtual void Render(Camera* camera);

	virtual ~SphericalHarmonicsDemo();
};