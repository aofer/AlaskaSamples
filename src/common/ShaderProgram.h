#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class ShaderProgram
{
private:
	GLuint m_program;

	GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);
public:
	ShaderProgram();
	void Compile(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc = NULL);
	void Bind();
	GLuint GetProgram() const;



};