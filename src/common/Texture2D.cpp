#include "Texture2D.h"

Texture2D::Texture2D() : Texture(GL_TEXTURE_2D) {}

Texture2D::~Texture2D(){}

void Texture2D::InitOnGPU(bool deleteAfterPush)
{
	ImageData &imageData = m_images[0];
	glBindTexture(m_textureTarget, m_textureObj);
	glTextureStorage2D(m_textureObj, m_mipmapLevels, imageData.format.sizedFormat, imageData.width, imageData.height); //allocate space for all

	if (imageData.data != 0)
		glTextureSubImage2D(m_textureObj, 0, 0, 0, imageData.width, imageData.height, imageData.format.baseFormat, imageData.format.type, imageData.data); //level 0 mipmap

	if (m_mipmapLevels > 1) {
		glGenerateTextureMipmap(m_textureObj); //generate the remaining mipmaps
		glTextureParameterf(m_textureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
		glTextureParameterf(m_textureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTextureParameterf(m_textureObj, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameterf(m_textureObj, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameterf(m_textureObj, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (/*deleteAfterPush*/true) {
		delete[] imageData.data;
		imageData.data = 0;
	}
	glBindTexture(m_textureTarget, 0);
}
