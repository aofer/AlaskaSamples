
#include <iostream>
#include "CubeMapTexture.h"
#include "soil/soil.h"
#include <string.h>
#include "Common.h"
using namespace std;

static const GLenum types[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };


CubeMapTexture::CubeMapTexture(const std::string& Directory,
	const std::string& PosXFilename,
	const std::string& NegXFilename,
	const std::string& PosYFilename,
	const std::string& NegYFilename,
	const std::string& PosZFilename,
	const std::string& NegZFilename)
{
	string::const_iterator it = Directory.end();
	it--;
	string BaseDir = (*it == '/') || (*it == '\\') ? Directory : Directory + "/";

	m_fileNames[0] = BaseDir + PosXFilename;
	m_fileNames[1] = BaseDir + NegXFilename;
	m_fileNames[2] = BaseDir + PosYFilename;
	m_fileNames[3] = BaseDir + NegYFilename;
	m_fileNames[4] = BaseDir + PosZFilename;
	m_fileNames[5] = BaseDir + NegZFilename;

	m_textureObj = 0;

}


bool CubeMapTexture::Load()
{
	bool res = true;
	glGenTextures(1, &m_textureObj);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
	int width, height;

	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++)
	{
		unsigned char* image =
			SOIL_load_image(m_fileNames[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(types[i], 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		free(image);

		if (0 == m_textureObj)
		{
			printf("SOIL loading error: '%s'\n", SOIL_last_result());
			res = false;
			break;
		}

	}
	return res;
}

void CubeMapTexture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
}

