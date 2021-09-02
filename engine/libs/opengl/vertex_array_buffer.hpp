#ifndef __ANDROMEDA_LIBS_OPENGL_VERTEX_ARRAY_BUFFER__
#define __ANDROMEDA_LIBS_OPENGL_VERTEX_ARRAY_BUFFER__

#include "../libs.hpp"

using namespace L::Graphics;

class OpenGL::VertexArrayBuffer
{
private:
	uint32_t m_RendererID;


public:
	VertexArrayBuffer()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	void Unbind() const
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
};

#endif // __ANDROMEDA_LIBS_OPENGL_VERTEX_ARRAY_BUFFER__