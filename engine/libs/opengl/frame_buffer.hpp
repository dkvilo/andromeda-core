#ifndef __ANDROMEDA_LIBS_OPENGL_FRAME_BUFFER__
#define __ANDROMEDA_LIBS_OPENGL_FRAME_BUFFER__

#include "../../../engine/andromeda.hpp"

#include "../libs.hpp"

#include "texture.hpp"
#include "render_buffer.hpp"

using namespace L::Graphics;

class OpenGL::FrameBuffer
{

private:
	mutable uint32_t m_RendererID;
	uint32_t m_Texture;
	OpenGL::RenderBuffer *m_RenderBuffer;

public:
	FrameBuffer(uint32_t width, uint32_t height)
	{
		/**
		 * Generate framebuffer
		 */
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		/**
		 * Generate Empty texture for framebufffer
		 */
		OpenGL::Texture::Generate(width, height, m_Texture);

		/**
		 * Attach framebuffer to the generated texture
		 */
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

		/**
		 * Create and bind RenderBuffer to FrameBuffer
		 */
		m_RenderBuffer = new OpenGL::RenderBuffer(width, height);

		/**
		 * Check for FrameBuffer status
		 */
		ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not completed", "FRAME_BUFFER");

		/**
		 * Unbind FrameBuffer
		 */
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	inline void Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	inline void Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	inline uint32_t GetID() const
	{
		return m_RendererID;
	}

	inline uint32_t GetTextureID() const
	{
		return m_Texture;
	}
};

#endif // __ANDROMEDA_LIBS_OPENGL_FRAME_BUFFER__
