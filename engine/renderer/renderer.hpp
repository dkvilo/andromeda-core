#ifndef __ENGINE_RENDERER__
#define __ENGINE_RENDERER__

#include "andromeda.hpp"

#include "../libs/libs.hpp"
#include "../libs/opengl/shader.hpp"
#include "../libs/opengl/vertex_buffer.hpp"

using namespace L::Graphics;

class Andromeda::Renderer
{
private:
  Andromeda::RenderingAPI m_SelectedAPI;
  mutable OpenGL::Shader m_Shader;
  mutable OpenGL::VertexBuffer m_Vbo;

public:
  Renderer()
  {
    /**
     * 
     * Set default rendering API to OpenGL
     * 
     */
    m_SelectedAPI = Andromeda::RenderingAPI::OpenGL;
  }

  void UseRenderingAPI(Andromeda::RenderingAPI target)
  {
    m_SelectedAPI = target;
  }

  Andromeda::RenderingAPI GetAPI()
  {
    return m_SelectedAPI;
  }

  void Init(const OpenGL::Shader &&shader, const OpenGL::VertexBuffer &&vbo) const
  {
    m_Shader = shader;
    m_Vbo = vbo;
  }

  void Submit(const void *data, size_t size, uint32_t count, size_t vertex_offset)
  {
    m_Vbo.SetData(data, size);
    glVertexAttribPointer(0, count, GL_FLOAT, GL_FALSE, vertex_offset, (void *)0); // next 12 bytes 3 * sizeof(float)
    glEnableVertexAttribArray(0);
  }

  void ResetSubmitton()
  {
    m_Vbo.Unbind();
  }

  void Draw()
  {
    m_Shader.Use();
    glDrawArrays(GL_TRIANGLES, 0, 8);
  }
};

#endif // __ENGINE_RENDERER__