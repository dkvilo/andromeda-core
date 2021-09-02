#ifndef __ENGINE_RENDERER__
#define __ENGINE_RENDERER__

#include "andromeda.hpp"

#include "../libs/libs.hpp"
#include "../libs/opengl/shader.hpp"

#include "../libs/opengl/index_buffer.hpp"
#include "../libs/opengl/vertex_buffer.hpp"
#include "../libs/opengl/vertex_array_buffer.hpp"

#include "glm/matrix.hpp"
#include "glm/vec2.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;
using namespace L::Graphics;

class Andromeda::Renderer
{
private:
	Andromeda::RenderingAPI m_SelectedAPI;
	OpenGL::Shader m_Shader;
	OpenGL::VertexBuffer m_Vbo;
	OpenGL::VertexArrayBuffer m_Vao;
	OpenGL::IndexBuffer m_Ebo;

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

	void Init(const OpenGL::Shader &&shader, const OpenGL::VertexArrayBuffer &&vao, const OpenGL::VertexBuffer &&vbo, const OpenGL::IndexBuffer &&ebo)	{
		/**
		 * 
		 * Reference Shader
		 * 
		 */ 
		m_Shader = shader;
		
		/**
		 * 
		 * Reference VBO
		 * 
		 */ 
		m_Vbo = vbo;

		/**
		 * 
		 * Reference VAO
		 * 
		 */
		m_Vao = vao;

		/**
		 * 
		 * Reference EBO
		 * 
		 */
		m_Ebo = ebo;
	}

	void Submit(const void *data, size_t size, uint32_t count, size_t vertex_offset) const
	{
		
		/**
		 * 
		 * Upload data to vertex buffer (POSTION, COLOR, UV)
		 * 
		 */
		m_Vbo.SetData(data, size);

		/**
		 * 
		 * Bind IndexBuffer
		 * 
		 */	
		m_Ebo.Bind();

		/**
		 * 
		 * Configure Vertex Array Layout
		 * 
		 */

		/**
		 * 
		 * Pass position
		 * 
		 */
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_offset, (void *)0); // next 12 bytes 3 * sizeof(float)
		glEnableVertexAttribArray(0);

		/**
		 * 
		 *  Pass color
		 * 
		 */
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_offset, (void *)(3 * sizeof(float))); // next 20 bytes 5 * sizeof(float)
		glEnableVertexAttribArray(1);

		/**
		 * 
		 *  Pass UV
		 * 
		 */
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_offset, (void *)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

	}

	/**
	 * 
	 * TODO: Move Vertex Array Layout configuration in separate class 
	 * 
	 */

	void SetViewProjection(const mat4 &u_ViewProjection) const
	{
		uint32_t location = glGetUniformLocation(m_Shader.RendererId(), "u_ViewProjection");
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(u_ViewProjection));
	}

	void SetResolution(const vec2 &resolution) const
	{
		uint32_t location = glGetUniformLocation(m_Shader.RendererId(), "u_Resolution");
		glUniform2fv(location, 1, value_ptr(resolution));
	}

	void SetTime(const float &u_Time) const
	{
		uint32_t location = glGetUniformLocation(m_Shader.RendererId(), "u_Time");
		glUniform1f(location, u_Time);
	}

	void SetTexture(uint32_t slot) const
	{
		uint32_t location = glGetUniformLocation(m_Shader.RendererId(), "u_Tex0");
		glUniform1f(location, slot);
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	void ResetSubmitton() const
	{
		/**
		 * 
		 * Unbind buffers
		 * 
		 */ 
		m_Vbo.Unbind();
		m_Ebo.Unbind();
		m_Vao.Unbind();
	}

	void Draw(uint32_t size) const
	{
		/**
		 * 
		 * Bind Shader
		 * 
		 */ 
		m_Shader.Use();

		/**
		 * 
		 * Issue draw call
		 * 
		 */
	    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void *)0);
	}
};

#endif // __ENGINE_RENDERER__