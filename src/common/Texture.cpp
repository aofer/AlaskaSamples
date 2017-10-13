
#include <iostream>
#include "Texture.h"
#include "soil/soil.h"

	Texture::Texture(const std::string& FileName, GLenum TextureTarget)
	{
		m_textureTarget = TextureTarget;
		m_fileName = FileName;
	}


	bool Texture::Load()
	{
		bool res = true;
		do
		{
			glGenTextures(1, &m_textureObj);
			glBindTexture(m_textureTarget, m_textureObj);
			int width, height;
			unsigned char* image =
				SOIL_load_image(m_fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, image);
			free(image);
			if (0 == m_textureObj)
			{
				printf("SOIL loading error: '%s'\n", SOIL_last_result());
				res = false;
				break;
			}


			//glTexImage2D(m_textureTarget, 0, GL_RGBA, m_image.columns(), m_image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
			glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(m_textureTarget, 0);

		} while (0);


		return res;
	}

	void Texture::Bind(GLenum TextureUnit)
	{
		glActiveTexture(TextureUnit);
		glBindTexture(m_textureTarget, m_textureObj);
	}
