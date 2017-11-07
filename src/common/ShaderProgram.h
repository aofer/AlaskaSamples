#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

static GLuint m_currentlyBinded = -1; //replace later with shader manager
class ShaderProgram
{
private:
	GLuint m_program;


	GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);
public:
	ShaderProgram();
	void Compile(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc = NULL);
	void Bind();
	bool IsBinded();
	GLuint GetProgram() const;





};