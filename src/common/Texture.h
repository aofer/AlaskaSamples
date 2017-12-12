#pragma once
#include "Common.h"
#include <string>
#include <GL/glew.h>

struct ImageFormat {
	GLenum sizedFormat, baseFormat, type;
	uint32_t numberOfChannels, bytesPerChannel;

	const static ImageFormat IMAGE_FORMAT_SRGBA8;
	const static ImageFormat IMAGE_FORMAT_SRGB8;

	const static ImageFormat IMAGE_FORMAT_SBGR8;

	const static ImageFormat IMAGE_FORMAT_RGBA8_LINEAR;
	const static ImageFormat IMAGE_FORMAT_RGB8_LINEAR;

	const static ImageFormat IMAGE_FORMAT_R8;
	const static ImageFormat IMAGE_FORMAT_R16;

	const static ImageFormat IMAGE_FORMAT_DEPTH_32F;

	ImageFormat(GLenum sizedFormat, GLenum baseFormat, GLenum type, uint32_t numberOfChannels, uint32_t bytesPerChannel) :
		sizedFormat(sizedFormat), baseFormat(baseFormat), type(type), numberOfChannels(numberOfChannels), bytesPerChannel(bytesPerChannel) {
	}

	ImageFormat() {}
};

struct ImageData {
	ImageFormat format;
	uint32_t width, height;
	uint8_t* data;
	uint32_t sizeInBytes;
};



	class Texture
	{
	public:
		Texture(GLenum target);
		virtual ~Texture();

		void Bind(GLenum TextureUnit) const;

		void ChangeTextureParameter(GLenum parameter, GLfloat value);

		virtual const void* GetTexel(const ImageData &imageData, const int x, const int y, const int z);
		virtual void SetTexel(int imageIndex, const int x, const int y, const int z, const void* value);

		virtual void InitFromFile(const std::string &path, const ImageFormat &format = ImageFormat::IMAGE_FORMAT_RGBA8_LINEAR);
		virtual void InitFromFiles(const std::vector<std::string> &paths, const ImageFormat &format = ImageFormat::IMAGE_FORMAT_RGBA8_LINEAR);

		void InitFromData(uint32_t width, uint32_t height, const uint8_t* data, const ImageFormat &format = ImageFormat::IMAGE_FORMAT_RGBA8_LINEAR);


		inline void GetMipmapLevels(int levels) { m_mipmapLevels = levels; }

		inline const ImageData& GetImageData(int index) { return m_images[index]; }

	protected:

		GLenum m_textureTarget;
		GLuint m_textureObj;
		int m_mipmapLevels;

		std::vector<ImageData> m_images;

		virtual void Create();
		virtual void Destroy();
		virtual void InitOnGPU(bool deleteAfterPush = false) = 0;
		const ImageData LoadFile(const std::string &path, const ImageFormat &format);


	};
