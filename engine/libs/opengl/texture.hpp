#ifndef __ANDROMEDA_LIBS_OPENGL_TEXTURE__
#define __ANDROMEDA_LIBS_OPENGL_TEXTURE__

#include "../libs.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace L::Graphics;

class OpenGL::Texture
{

private:
	const char* m_Path;
	uint32_t m_RendererID;
	uint32_t m_Width, m_Height;

public:

	Texture() {}

	Texture(const char *path) : m_Path(path)
	{
		int width, height, channels;

		unsigned char *dataBuffer = stbi_load(m_Path, &width, &height, &channels, 0);
		ASSERT(dataBuffer, "(STB_IMAGE): Unable to load texture", NULL);

		m_Width, m_Height = width, height;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, texDataFormat, width, height, 0, texDataFormat, GL_UNSIGNED_BYTE, dataBuffer);
		stbi_image_free(dataBuffer);
	}

	void Generate(uint32_t width, uint32_t height) 
	{
		m_Width, m_Height = width, height;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	}

	void Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	inline const char* GetPath() { return m_Path; }
	inline uint32_t &Getheight() { return m_Height; }
	inline uint32_t &GetWidth() { return m_Width; }
	inline uint32_t &GetRendererID() { return m_RendererID; }
};

#endif // __ANDROMEDA_LIBS_OPENGL_TEXTURE__
