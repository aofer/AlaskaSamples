#pragma once
#include "Common.h"
#include <vector>
#include <map>
#include <string>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include <assimp\Importer.hpp> 
#include <assimp\scene.h>       // Output data structure
#include <assimp\postprocess.h> // Post processing flags

static std::string ReadFileIntoString(const std::string& filename);

typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
typedef std::shared_ptr<Texture> TexturePtr;

class ResourceManager
{
public:


	void LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, std::string name);
	ShaderProgramPtr GetShader(const std::string& name);
	void LoadModel(const std::string& path, const std::string& name);
	MeshPtr GetMesh(const std::string& name);
	void LoadTexture(const std::string& path, const std::string& name);
	TexturePtr GetTexture(const std::string& name);

	ResourceManager();
	~ResourceManager();

private:
	// Resource Storage 
	std::map<std::string, ShaderProgramPtr> m_shaders;
	std::map<std::string, MeshPtr> m_meshes;
	std::map<std::string, TexturePtr> m_textures;

	MeshPtr ResourceManager::CreateMesh(const std::string& path);
	void ResourceManager::InitMesh(unsigned int Index, const aiMesh* paiMesh, MeshPtr mesh);
	MeshPtr ResourceManager::InitFromScene(const aiScene* pScene, const std::string& Filename);
};