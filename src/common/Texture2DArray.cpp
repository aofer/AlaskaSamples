#include "Texture2DArray.h"

Texture2DArray::Texture2DArray() : Texture(GL_TEXTURE_2D_ARRAY) {}

Texture2DArray::~Texture2DArray(){}

void Texture2DArray::InitOnGPU(bool deleteAfterPush)
{
	glTextureStorage3D(m_textureObj, m_mipmapLevels, m_images[0].format.sizedFormat, m_images[0].width, m_images[0].height, m_images.size()); //allocate space for all

	for (unsigned int i = 0; i < m_images.size(); ++i) {
		ImageData &imageData = m_images[i];

		if (imageData.data != 0)
			glTextureSubImage3D(m_textureObj,
				0,
				0, 0, i,
				imageData.width, imageData.height, 1,
				imageData.format.baseFormat, imageData.format.type, imageData.data);

		if (deleteAfterPush) {
			delete[] imageData.data;
			imageData.data = 0;
		}
	}

	if (m_mipmapLevels > 1) {
		glGenerateTextureMipmap(m_textureObj); //generate the remaining mipmaps
		glTextureParameterf(m_textureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
		glTextureParameterf(m_textureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTextureParameterf(m_textureObj, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameterf(m_textureObj, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameterf(m_textureObj, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
