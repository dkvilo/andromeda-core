#ifndef __ANDROMEDA_LIBS_OPENGL_INDEX_BUFFER__
#define __ANDROMEDA_LIBS_OPENGL_INDEX_BUFFER__

#include "../libs.hpp"

class L::Graphics::OpenGL::IndexBuffer
{
private:
  uint32_t m_RendererID;
  uint32_t m_Count;

public:
  IndexBuffer(uint32_t *indices, uint32_t count) : m_Count(count)
  {
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
  }

  void Bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  }

  void Unbind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  uint32_t GetCount() const
  {
    return m_Count;
  }

  ~IndexBuffer()
  {
    glDeleteBuffers(1, &m_RendererID);
  }
};

#endif // __ANDROMEDA_LIBS_OPENGL_INDEX_BUFFER__