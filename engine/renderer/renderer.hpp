#ifndef __ENGINE_RENDERER__
#define __ENGINE_RENDERER__

#include "andromeda.hpp"

#include "../libs/libs.hpp"
#include "../libs/opengl/shader.hpp"
#include "../libs/opengl/vertex_buffer.hpp"

#include "glm/matrix.hpp"
#include "glm/vec2.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;
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
		m_SelectedAPI = Andromeda::RenderingAPI::OpenGL;
	}

	void UseRenderingAPI(Andromeda::RenderingAPI target)
	{
		m_SelectedAPI = target;
	}

	Andromeda::RenderingAPI GetAPI() const
	{
		return m_SelectedAPI;
	}

	void Init(const OpenGL::Shader &&shader, const OpenGL::VertexBuffer &&vbo) const
	{
		m_Shader = shader;
		m_Vbo = vbo;
	}

	void Submit(const void *data, size_t size, uint32_t count, size_t vertex_offset) const
	{
		m_Vbo.SetData(data, size);

		// Pass position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_offset, (void *)0); // next 12 bytes 3 * sizeof(float)
		glEnableVertexAttribArray(0);

		// Pass color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_offset, (void *)(3 * sizeof(float))); // next 20 bytes 5 * sizeof(float)
		glEnableVertexAttribArray(1);

		// Pass UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_offset, (void *)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void SetViewProjection(const mat4 &u_ViewProjection) const
	{
		GLuint location = glGetUniformLocation(m_Shader.RendererId(), "u_ViewProjection");
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(u_ViewProjection));
	}

	void SetResolution(const vec2 &resolution)
	{
		GLuint location = glGetUniformLocation(m_Shader.RendererId(), "u_Resolution");
		glUniform2fv(location, 1, value_ptr(resolution));
	}

	void SetTime(const float &u_Time)
	{
		GLuint location = glGetUniformLocation(m_Shader.RendererId(), "u_Time");
		glUniform1f(location, u_Time);
	}

	void ResetSubmitton() const
	{
		m_Vbo.Unbind();
	}

	void Draw() const
	{
		m_Shader.Use();
		glDrawArrays(GL_TRIANGLES, 0, 8);
	}
};

#endif // __ENGINE_RENDERER__