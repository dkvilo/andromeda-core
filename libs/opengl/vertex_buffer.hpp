#ifndef __ANDROMEDA_LIBS_OPENGL_VERTEX_BUFFER__
#define __ANDROMEDA_LIBS_OPENGL_VERTEX_BUFFER__

#include "../libs.hpp"

class L::Graphics::OpenGL::VertexBuffer
{
private:
  uint32_t m_RendererID;

public:
  VertexBuffer()
  {
    glGenBuffers(1, &m_RendererID);
  }

  VertexBuffer(size_t size)
  {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
  }

  void SetData(const void *data, uint32_t size) const
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
  }

  uint32_t GetRendererID() const
  {
    return m_RendererID;
  }

  void Bind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  }

  void Unbind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
};

#endif // __ANDROMEDA_LIBS_OPENGL_VERTEX_BUFFER__