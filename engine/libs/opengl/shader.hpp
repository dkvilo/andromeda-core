#ifndef __ANDROMEDA_LIBS_OPENGL_SHADER__
#define __ANDROMEDA_LIBS_OPENGL_SHADER__

#include <vector>

#include "../libs.hpp"
#include "../fs/fs.hpp"

class L::Graphics::OpenGL::Shader
{
private:
	uint32_t m_RendererID;
	uint32_t m_VertexShader;
	uint32_t m_FragmentShader;

public:
	Shader() = default;
	Shader(const char *frag, const char *vert)
	{
		m_FragmentShader = Compile(L::Fs::ReadFileContent(frag), GL_FRAGMENT_SHADER);
		m_VertexShader = Compile(L::Fs::ReadFileContent(vert), GL_VERTEX_SHADER);
		CreateProgram(m_FragmentShader, m_VertexShader);
	}

	inline void Use() const
	{
		glUseProgram(m_RendererID);
	}

	inline void Unbind() const
	{
		glUseProgram(0);
		glDeleteProgram(m_RendererID);
	}

	unsigned int RendererId() const
	{
		return m_RendererID;
	}

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

			std::vector<char> log(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &log[0]);

			glDeleteShader(shader);
			ASSERT(NULL, log.data(), "SHADER_COMPILATION_ERROR");
		}

		return shader;
	}

	inline void CreateProgram(uint32_t fs, uint32_t vs)
	{
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, fs);
		glAttachShader(m_RendererID, vs);
		glLinkProgram(m_RendererID);
	}
};

#endif // __ANDROMEDA_LIBS_OPENGL_SHADER__