#ifndef __ANDROMEDA_LIBS_OPENGL_TEXTURE__
#define __ANDROMEDA_LIBS_OPENGL_TEXTURE__

#include "../libs.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class L::Graphics::OpenGL::Texture
{

public:
	static void Create(const char *path, unsigned int &texture)
	{
		int width, height, channels;

		unsigned char *dataBuffer = stbi_load(path, &width, &height, &channels, 0);
		ASSERT(dataBuffer, "(STB_IMAGE): Unable to load texture", NULL);

		glGenTextures(1, &texture);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		GLenum texDataFormat;
		if (channels == 4)
		{
			texDataFormat = GL_RGBA;
		}

		if (channels == 3)
		{
			texDataFormat = GL_RGB;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, texDataFormat, width, height, 0, texDataFormat, GL_UNSIGNED_BYTE, dataBuffer);
		stbi_image_free(dataBuffer);
	}

	static void Generate(uint32_t width, uint32_t height, unsigned int &texture)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	}
};

#endif // __ANDROMEDA_LIBS_OPENGL_TEXTURE__
