#ifndef __ANDROMEDA_LIBS_OPENGL_RENDER_BUFFER__
#define __ANDROMEDA_LIBS_OPENGL_RENDER_BUFFER__

#include "../libs.hpp"

using namespace L::Graphics;
class OpenGL::RenderBuffer
{

private:
	mutable uint32_t m_RendererID;

public:
	RenderBuffer(uint32_t width, uint32_t height)
	{
		glGenRenderbuffers(1, &m_RendererID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
		/**
		 * Attach render buffer to framebuffer
		 */
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RendererID);
	}

	uint32_t GetID() const
	{
		return m_RendererID;
	}
};

#endif // __ANDROMEDA_LIBS_OPENGL_FRAME_BUFFER__
