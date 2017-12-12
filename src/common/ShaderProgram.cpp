#include "ShaderProgram.h"
#include <vector>
#include "Common.h"
ShaderProgram::ShaderProgram()
{

}

void ShaderProgram::Compile(const std::string& vertexSrc, const std::string& FragSrc, 
	const std::string& GeometrySrc, const std::string& tesSource , const std::string& tcsSource )
{
	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertexSrc, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, FragSrc, "fragment shader");
	GLuint geometry_shader = -1;
	GLuint tes_shader = -1;
	GLuint tcs_shader = -1;

	int  link_result = 0;
	//create the program handle, attach the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	if (!GeometrySrc.empty())
	{
		geometry_shader = CreateShader(GL_GEOMETRY_SHADER, GeometrySrc, "geometry shader");
		glAttachShader(program, geometry_shader);
	}
	if (!tesSource.empty())
	{
		tes_shader = CreateShader(GL_GEOMETRY_SHADER, tesSource, "tes shader");
		glAttachShader(program, tes_shader);
	}
	if (!tcsSource.empty())
	{
		tcs_shader = CreateShader(GL_GEOMETRY_SHADER, tcsSource, "tcs shader");
		glAttachShader(program, tcs_shader);
	}

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		LOG_ERROR("Shader Loader : LINK ERROR : {0}", &program_log[0]);
		return;
	}
	m_program = program;
}

void ShaderProgram::Bind()
{
	if (m_program != m_currentlyBinded)
	{
		glUseProgram(m_program);
		m_currentlyBinded = m_program;
	}
}


bool ShaderProgram::IsBinded()
{
	return m_program == m_currentlyBinded;
}

GLuint ShaderProgram::GetProgram() const
{
	return m_program;
}

GLuint ShaderProgram::CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int   shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);


	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		//std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shader_log[0] << std::endl;
		//LOG_ERROR("ERROR compiling shader: %s, error:%s", shaderName, shader_log[0]);
	}

	return shader;

}