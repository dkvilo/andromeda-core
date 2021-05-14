#ifndef __ANDROMEDA_LIBS_OPENGL_SHADER__
#define __ANDROMEDA_LIBS_OPENGL_SHADER__

#include <vector>
#include "../libs.hpp"

class L::Graphics::OpenGL::Shader
{
private:
  unsigned int m_RendererID;
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
    glUseProgram(this->m_RendererID);
  }

  unsigned int RendererId()
  {
    return this->m_RendererID;
  };

private:
  inline unsigned int Compile(const char *content, unsigned int type)
  {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &content, NULL);
    glCompileShader(shader);

    int isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
      int maxLength = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<char> infoLog(maxLength);
      glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

      glDeleteShader(shader);
      ASSERT(NULL, infoLog.data(), "SHADER_COMPILATION_ERROR");
    }

    return shader;
  }

  inline void CreateProgram(unsigned int f, unsigned int v)
  {
    this->m_RendererID = glCreateProgram();
    glAttachShader(this->m_RendererID, f);
    glAttachShader(this->m_RendererID, v);
    glLinkProgram(this->m_RendererID);
  }
};

#endif // __ANDROMEDA_LIBS_OPENGL_SHADER__