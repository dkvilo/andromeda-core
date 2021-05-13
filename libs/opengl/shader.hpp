#ifndef __ANDROMEDA_LIBS_OPENGL_SHADER__
#define __ANDROMEDA_LIBS_OPENGL_SHADER__

#include "../libs.hpp"

class L::Graphics::Shader
{
private:
  unsigned int m_program;
  unsigned int vertexShader;
  unsigned int fragmentShader;

public:
  Shader(const char *frag, const char *vert)
  {
    this->fragmentShader = this->Compile(L::Fs::ReadFileContent(frag), GL_FRAGMENT_SHADER);
    this->vertexShader = this->Compile(L::Fs::ReadFileContent(vert), GL_VERTEX_SHADER);
  }

  inline void Use()
  {
    glUseProgram(this->m_program);
  }

  unsigned int *Id()
  {
    return &this->m_program;
  };

private:
  inline unsigned int Compile(const char *content, unsigned int type)
  {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &content, NULL);
    glCompileShader(shader);
    return shader;
  }

  inline void CreateProgram(unsigned int f, unsigned int v)
  {
    this->m_program = glCreateProgram();
    glAttachShader(this->m_program, f);
    glAttachShader(this->m_program, v);
    glLinkProgram(this->m_program);
  }
};

#endif // __ANDROMEDA_LIBS_OPENGL_SHADER__