#pragma once
#include "ResourceManager.h"


static std::string ReadFileIntoString(const std::string& filename)
{

	std::string content;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {
		std::cout << "Can't read file " << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	content.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&content[0], content.size());
	file.close();

	return content;
}


void ResourceManager::LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, std::string name)
{
	if (vShaderFile.empty() || fShaderFile.empty())
	{
		LOG_ERROR("Missing vertex\fragment shader");
		return;
	}
	ShaderProgramPtr program = std::make_shared<ShaderProgram>();;
	std::string vertexShaderStr = ReadFileIntoString(vShaderFile);
	std::string fragmentShaderStr = ReadFileIntoString(fShaderFile);
	std::string  geometryShaderStr = nullptr;
	if (!gShaderFile.empty())
	{
		geometryShaderStr = ReadFileIntoString(gShaderFile);
	}
	program->Compile(vertexShaderStr, fragmentShaderStr, geometryShaderStr);
	m_shaders[name] = program;
}


ShaderProgramPtr ResourceManager::GetShader(const std::string& name)
{
	return m_shaders[name];
}

void ResourceManager::LoadModel(const std::string& path, const std::string& name)
{
	MeshPtr tMesh = CreateMesh(path);

	m_meshes[name] = tMesh;
}

MeshPtr ResourceManager::GetMesh(const std::string& name)
{
	return m_meshes[name];
}

void ResourceManager::LoadTexture(const std::string& path, const std::string& name)
{
	TexturePtr texture = std::make_shared<Texture>(path);
	texture->Load();
	m_textures[name] = texture;
}

TexturePtr ResourceManager::GetTexture(const std::string& name)
{
	return m_textures[name];
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}


MeshPtr ResourceManager::CreateMesh(const std::string& path)
{
	// Release the previously loaded mesh (if it exists)
	//			Clear();
	MeshPtr resMesh = nullptr;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene) {
		resMesh = InitFromScene(pScene, path);
	}
	else {
		printf("Error parsing '%s': '%s'\n", path.c_str(), Importer.GetErrorString());
	}
	resMesh->InitOnGPU();

	return resMesh;
}

MeshPtr ResourceManager::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	MeshPtr mesh = std::make_shared<Mesh>();
	mesh->GetEntries().resize(pScene->mNumMeshes);


	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < mesh->GetEntries().size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh, mesh);
	}

	return mesh;
}

void ResourceManager::InitMesh(unsigned int Index, const aiMesh* paiMesh, MeshPtr mesh)
{
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
			glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec3(pNormal->x, pNormal->y, pNormal->z));

		Vertices.push_back(v);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}
	mesh->GetEntries()[Index].m_vertices = Vertices;
	mesh->GetEntries()[Index].m_indices = Indices;

}
