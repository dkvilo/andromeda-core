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
  Andromeda::RenderingAPI SelectedAPI;
  mutable OpenGL::Shader shader;
  mutable OpenGL::VertexBuffer vbo;

public:
  Renderer()
  {
    /**
     * 
     * Set default rendering API to OpenGL
     * 
     */
    this->SelectedAPI = Andromeda::RenderingAPI::OpenGL;
  }

  void UseRenderingAPI(Andromeda::RenderingAPI target)
  {
    this->SelectedAPI = target;
  }

  Andromeda::RenderingAPI GetAPI()
  {
    return this->SelectedAPI;
  }

  void Init(const OpenGL::Shader &&shader, const OpenGL::VertexBuffer &&vbo) const
  {
    this->shader = shader;
    this->vbo = vbo;
  }

  void Submit(const void *data, size_t size, uint32_t count, size_t vertex_offset)
  {
    this->vbo.SetData(data, size);
    glVertexAttribPointer(0, count, GL_FLOAT, GL_FALSE, vertex_offset, (void *)0); // next 12 bytes 3 * sizeof(float)
    glEnableVertexAttribArray(0);
  }

  void ResetSubmitton()
  {
    this->vbo.Unbind();
  }

  void Draw()
  {
    this->shader.Use();
    glDrawArrays(GL_TRIANGLES, 0, 8);
  }
};

#endif // __ENGINE_RENDERER__