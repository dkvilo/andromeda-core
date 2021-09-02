#ifndef ANDROMEDA_ENGINE_COMPONENTS
#define ANDROMEDA_ENGINE_COMPONENTS

#include <math.h>

#include "andromeda.hpp"

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "window/window.hpp"
#include "entity/component.hpp"
#include "entity/entity.hpp"
#include "renderer/renderer.hpp"

#include "../libs/libs.hpp"
#include "../libs/opengl/shader.hpp"
#include "../libs/opengl/texture.hpp"

using namespace glm;
using namespace L::Graphics;
using namespace Andromeda::Components;

#define VBO_BUFFER_LENGTH 32
#define EBO_BUFFER_LENGTH 6

struct Andromeda::Components::Texture2d 
	: public Andromeda::Entity
{
	
	const char *m_Path;
	uint32_t m_Slot;
	
	OpenGL::Texture *m_Texture;

	Texture2d() {}

	Texture2d(const char *path, uint32_t slot) 
		: m_Path(path)
		, m_Slot(slot) 
	{
		m_Name 	  = "Texture2d";	
		m_Texture = new OpenGL::Texture(m_Path);
	}

	void BindTexture(const Andromeda::Renderer &renderer) const
	{
		renderer.SetTexture(m_Slot);
		m_Texture->Bind();
	}
	
	void AttachRenderer(const Andromeda::Renderer &renderer)
	{
		BindTexture(renderer);
	}
};

struct Andromeda::Components::Mesh2d
	: public Andromeda::Entity
	, public Andromeda::Component
{

	Andromeda::Renderer m_Renderer;
	
	Texture2d c_Texture;

	vec3 m_Scale;
	mat4 m_Model = mat4(1.0f);
	mat4 m_View = mat4(1.0f);

	/**
	 * TODO: Set Shaders from Material
	 * 
	 * 
	 */
	static constexpr char *s_FragShdr = "./engine/assets/shaders/basic/color.frag";
	static constexpr char *s_VertShdr = "./engine/assets/shaders/basic/color.vert";

	bool s_FirstFrame = false;
	
	Mesh2d(float scale) : m_Scale(scale)
	{
		m_Name = "Mesh2d";

		float vertexBufferData[VBO_BUFFER_LENGTH] = {
			// Positions         	// Colors           // UV
			-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 	0.0f, 0.0f, // Top-left
			 0.5f,  0.5f, 0.0f, 	0.0f, 1.0f, 0.0f, 	1.0f, 0.0f,	 // Top-right
			 0.5f, -0.5f, 0.0f, 	0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, // Bottom-right
			-0.5f, -0.5f, 0.0f, 	1.0f, 1.0f, 1.0f, 	0.0f, 1.0f // Bottom-left
		};

		uint32_t indicies[EBO_BUFFER_LENGTH] = {
			0, 1, 2,
			2, 3, 0
		};

		m_Renderer.Init(
			OpenGL::Shader(s_FragShdr, s_VertShdr),
			OpenGL::VertexArrayBuffer(),
			OpenGL::VertexBuffer(VBO_BUFFER_LENGTH * sizeof(float)),
			OpenGL::IndexBuffer(indicies, EBO_BUFFER_LENGTH)
		);
	
		m_Renderer.Submit(vertexBufferData, VBO_BUFFER_LENGTH * sizeof(float), 8, 8 * sizeof(float));
	}

	void update(double dt)
	{

		float aspect = (float)Andromeda::Window::GetWindowInfo().width / (float)Andromeda::Window::GetWindowInfo().height;
		UpdateProjection(-aspect, aspect, -1.0f, 1.0f, 1.0f, -1.0f);
	
		m_Renderer.SetViewProjection(m_Projection * m_View * m_Model);
		m_Renderer.SetResolution(vec2(Andromeda::Window::GetWindowInfo().width, Andromeda::Window::GetWindowInfo().height));
		m_Renderer.SetTime(dt);
		
		if (!s_FirstFrame)
		{
			c_Texture.AttachRenderer(m_Renderer);
			s_FirstFrame = true;
		}

		m_Renderer.Draw(EBO_BUFFER_LENGTH);
	}
};

class Andromeda::Components::Transform 
	: public Andromeda::Entity
	, public Andromeda::Component
{
public:
	vec3 m_Scale;
	float m_Angle;

public:
	Transform(const vec3&& position, const vec3 &&rotation, const vec3 &&scale) 
	{
		m_Name        = "Transform";
		m_Projection  = mat4(1.0f);

		m_Rotation 	  = rotation;
		m_Position    = position;
		m_Scale       = scale;
	}

	void Scale(const vec3 &scale)
	{
		m_Scale = scale;
		m_Projection = SampleScale(scale);
	}

	void Rotate(float angle)
	{
		m_Angle = angle;
		m_Projection = SampleRotation(m_Angle); 
	}

	void Translate(const vec3 &position)
	{
		m_Position = position;
		m_Projection = SampleTranslation(m_Position);
	}

private:
	mat4 SampleRotation(float angle) const
	{
		return rotate(mat4(1.0f), radians(angle), m_Rotation);
	}

	mat4 SampleTranslation(const vec3 &position) const 
	{
		return translate(mat4(1.0f), position);
	}
	
	mat4 SampleScale(const vec3 & _scale) const
	{
		return scale(mat4(1.f), _scale);
	}

public:
	void update(double dt)
	{
		float aspect = (float) Andromeda::Window::GetWindowInfo().width / (float) Andromeda::Window::GetWindowInfo().height;

		UpdateProjection(-aspect, aspect, -1.0f, 1.0f, 1.0f, -1.0f);
		m_Projection = SampleTranslation(ScreenToWorldSpace(m_Position)) * SampleRotation(m_Angle) * SampleScale(m_Scale);
	}

};

class Andromeda::Components::Camera 
	: public Andromeda::Entity
	, public Andromeda::Component
{

private:
	vec3 m_Eye, m_Center, m_Up;

public:
	Camera(const vec3 &eye, const vec3 &center, const vec3 &up)
	{
		m_Name = "Camera";
		CalculateViewMatrix(eye, center, up);
	}

	void CalculateViewMatrix(const vec3 &eye, const vec3 &center, const vec3 &up)
	{
		m_Eye, m_Center, m_Up = eye, center, up;
		m_Projection = inverse(lookAt(m_Eye, m_Center, m_Up));
	}

	inline vec3 &GetEye()
	{
		return m_Eye;
	}

	inline vec3 &GetCenter()
	{
		return m_Center;
	}

	inline vec3 &GetUp()
	{
		return m_Up;
	}

	void update(double dt)
	{
		float aspect = (float) Andromeda::Window::GetWindowInfo().width / (float) Andromeda::Window::GetWindowInfo().height;		
		UpdateProjection(-aspect, aspect, -1.0f, 1.0f, 1.0f, -1.0f);
	} 
};


#endif // ANDROMEDA_ENGINE_COMPONENTS
