#pragma once
#include "Common.h"
#include <vector>
#include <map>
#include <string>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture2D.h"
#include <assimp\Importer.hpp> 
#include <assimp\scene.h>       // Output data structure
#include <assimp\postprocess.h> // Post processing flags

static std::string ReadFileIntoString(const std::string& filename);

typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;

class ResourceManager
{
public:


	ShaderProgramPtr LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, std::string name);
	ShaderProgramPtr LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, const std::string& tesShader, const std::string& tcsShader, std::string name);
	ShaderProgramPtr GetShader(const std::string& name);
	MeshPtr LoadMesh(const std::string& path, const std::string& name);
	MeshPtr GetMesh(const std::string& name);
	Texture2DPtr LoadTexture2D(const std::string& path, const std::string& name, const ImageFormat &format = ImageFormat::IMAGE_FORMAT_RGBA8_LINEAR);
	Texture2DPtr GetTexture2D(const std::string& name);

	ResourceManager();
	~ResourceManager();
	void SetResourceFolderPath(const std::string& path);

private:
	// Resource Storage 
	std::map<std::string, ShaderProgramPtr> m_shaders;
	std::map<std::string, MeshPtr> m_meshes;
	std::map<std::string, Texture2DPtr> m_textures;
	std::string m_resourceFolderPath;

	MeshPtr ResourceManager::CreateMeshFromObj(const std::string& path);
	void ResourceManager::InitMesh(unsigned int Index, const aiMesh* paiMesh, MeshPtr mesh);
	MeshPtr ResourceManager::InitFromScene(const aiScene* pScene, const std::string& Filename);
};