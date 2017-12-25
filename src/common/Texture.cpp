
#include <iostream>
#include "Texture.h"
#include "soil/soil.h"

const ImageFormat ImageFormat::IMAGE_FORMAT_SRGBA8 = ImageFormat(GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE, 4, 1);
const ImageFormat ImageFormat::IMAGE_FORMAT_SRGB8 = ImageFormat(GL_SRGB8, GL_RGB, GL_UNSIGNED_BYTE, 3, 1);

const ImageFormat ImageFormat::IMAGE_FORMAT_SBGR8 = ImageFormat(GL_SRGB8, GL_BGR, GL_UNSIGNED_BYTE, 3, 1);

const ImageFormat ImageFormat::IMAGE_FORMAT_RGBA8_LINEAR = ImageFormat(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, 4, 1);
const ImageFormat ImageFormat::IMAGE_FORMAT_RGB8_LINEAR = ImageFormat(GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, 3, 1);

const ImageFormat ImageFormat::IMAGE_FORMAT_R8 = ImageFormat(GL_R8, GL_RED, GL_UNSIGNED_BYTE, 1, 1);
const ImageFormat ImageFormat::IMAGE_FORMAT_R16 = ImageFormat(GL_R16, GL_RED, GL_UNSIGNED_SHORT, 1, 2);

const ImageFormat ImageFormat::IMAGE_FORMAT_DEPTH_32F = ImageFormat(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT, 1, 4);


	Texture::Texture(GLenum target) : m_textureTarget(target), m_mipmapLevels(1)
	{
		Create();
	}

	Texture::~Texture()
	{
		Destroy();
		for (unsigned int i = 0; i < m_images.size(); ++i) {
			if (m_images[i].data != 0)
				delete[] m_images[i].data;
		}
	}

	void Texture::Create()
	{
		glGenTextures(1, &m_textureObj);
	}

	void Texture::Destroy()
	{
		glDeleteTextures(1, &m_textureObj);
	}

	void Texture::Bind(GLenum TextureUnit) const
	{
		glActiveTexture(TextureUnit);
		glBindTexture(m_textureTarget, m_textureObj);
	}

	void Texture::ChangeTextureParameter(GLenum parameter, GLfloat value) {
		glTextureParameterf(m_textureObj, parameter, value);
	}

	const void* Texture::GetTexel(const ImageData &imageData, const int x, const int y, const int z) {
		uint32_t texelSize = imageData.format.bytesPerChannel * imageData.format.numberOfChannels;
		uint8_t *ptr = imageData.data + (y * texelSize * imageData.width) + (x * texelSize);
		return ptr;
	}

	void Texture::SetTexel(int imageIndex, const int x, const int y, const int z, const void *value) {
		const ImageData &imageData = m_images[imageIndex];
		uint32_t texelSize = imageData.format.bytesPerChannel * imageData.format.numberOfChannels;
		uint8_t *ptr = imageData.data + (y * texelSize * imageData.width) + (x * texelSize);

		memcpy(ptr, value, texelSize);
	}


	void Texture::InitFromFile(const std::string &path, const ImageFormat &format) {
		m_images.push_back(LoadFile(path, format));
		InitOnGPU();
	}

	void Texture::InitFromFiles(const std::vector<std::string> &paths, const ImageFormat &format) {
		for (std::string path : paths) {
			m_images.push_back(LoadFile(path, format));
		}
		InitOnGPU();
	}


	void Texture::InitFromData(uint32_t width, uint32_t height, const uint8_t* data, const ImageFormat &format) {

		ImageData imageData;
		imageData.format = format;

		imageData.width = width;
		imageData.height = height;
		imageData.sizeInBytes = width * height * format.numberOfChannels * format.bytesPerChannel;

		if (data != 0) {
			imageData.data = new uint8_t[imageData.sizeInBytes];
			memcpy(imageData.data, data, imageData.sizeInBytes);
		}
		else
			imageData.data = 0;

		m_images.push_back(imageData);

		InitOnGPU();
	}



	////TODO remove redundant copy when returning, fix case where file not found
	//const ImageData Texture::LoadFile(const std::string &path, const ImageFormat &format)
	//{
	//	ImageData imageData;
	//	int width, height,channels;
	//	//unsigned char* image =
	//	//	SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	//	unsigned char* image = nullptr;
	//	if (format.numberOfChannels == 1)
	//	{
	//		image =
	//			SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_L);
	//	}
	//	else
	//	{
	//		image =
	//			SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
	//	}
	//	if (image)
	//	{
	//		imageData.format = format;
	//		imageData.width = width;
	//		imageData.height = height;
	//		imageData.sizeInBytes = imageData.width * imageData.height * imageData.format.numberOfChannels * imageData.format.bytesPerChannel;
	//		imageData.data = new uint8_t[imageData.sizeInBytes];
	//		memcpy(imageData.data, image, imageData.sizeInBytes);
	//		free(image);
	//	}
	//	else
	//	{
	//		LOG_ERROR("Texture file not found : {0}", path);
	//	}


	//	return imageData;
	//}

	const ImageData Texture::LoadFile(const std::string &path, const ImageFormat &format) {
		ilInit();

		ILuint image;
		ilGenImages(1, &image);
		ilBindImage(image);
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

		ImageData imageData;

		ILboolean result = ilLoadImage(path.c_str());
		if (result) {
			//ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

			imageData.format = format;

			imageData.width = ilGetInteger(IL_IMAGE_WIDTH);
			imageData.height = ilGetInteger(IL_IMAGE_HEIGHT);
			imageData.sizeInBytes = imageData.width * imageData.height * imageData.format.numberOfChannels * imageData.format.bytesPerChannel;

			imageData.data = new uint8_t[imageData.sizeInBytes];
			memcpy(imageData.data, ilGetData(), imageData.sizeInBytes);
		}
		else {
			std::cout << "Failed to load image from file: " << path << std::endl;
		}

		ilDeleteImages(1, &image);

		return imageData;
	}