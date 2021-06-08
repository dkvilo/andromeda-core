#ifndef ANDROMEDA_ENGINE_COMPONENTS
#define ANDROMEDA_ENGINE_COMPONENTS

#include "andromeda.hpp"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "window/window.hpp"
#include "entity/component.hpp"
#include "entity/entity.hpp"
#include "renderer/renderer.hpp"

#include "../libs/libs.hpp"
#include "../libs/opengl/legacy.hpp"
#include "../libs/opengl/shader.hpp"
#include "../libs/opengl/texture.hpp"

using namespace glm;
using namespace L::Graphics;
using namespace Andromeda::Components;

struct Andromeda::Components::RGBColorMaterial : Andromeda::Entity
{
	vec3 m_Color;

	RGBColorMaterial(const vec3 &&color) : m_Color(color)
	{
		m_Name = "Color Material";
	}

	void update(double dt)
	{
		OpenGL::Legacy::fill_color(m_Color);
	}
};

struct Andromeda::Components::Stroke : public Andromeda::Entity, public Andromeda::Component
{
	RGBColorMaterial *m_ColorMaterial;

	float m_Offset = 0.0f;
	float m_Radius = 10.0f;
	float m_Angle = 0.0f;

	int m_Segments = 100;
	int m_LineWidth = 8;

	Stroke() : m_ColorMaterial(new RGBColorMaterial(vec3(0.121f, 0.917f, 0.566f)))
	{
		m_Name = "Stroke2d";
		m_Rotation = vec3(0, 0, 0);
	}

	void update(double dt)
	{

		UpdateProjection(0.0f, float(Andromeda::Window::GetWindowInfo().width), 0.0f, float(Andromeda::Window::GetWindowInfo().height), 0.00001f, -100000.0f);

		glLineWidth(m_LineWidth);
		glPushMatrix();
		if (m_Angle != 0.0f)
		{
			glRotatef(m_Angle, m_Rotation.x, m_Rotation.y, m_Rotation.z);
		}
		Andromeda_2d_begin(Andromeda_line_loop);
		m_ColorMaterial->update(dt);
		OpenGL::Legacy::draw_circle(ScreenToWorldSpace(m_Position), m_Radius + m_Offset, m_Segments);
		Andromeda_2d_end();
		glPopMatrix();
	}

	~Stroke()
	{
		delete m_ColorMaterial;
	}
};

struct Andromeda::Components::Shape2d : public Andromeda::Entity, public Andromeda::Component
{

	float m_Radius = 100.f;
	float m_Angle = 0.0f;
	int m_Segments = 100;
	int m_Triangles = 100;

	Shape2d()
	{
		m_Name = "Shape2d";
	}

	void update(double dt)
	{

		UpdateProjection(0.0f, float(Andromeda::Window::GetWindowInfo().width), 0.0f, float(Andromeda::Window::GetWindowInfo().height), 0.00001f, -100000.0f);

		glPushMatrix();
		if (m_Angle != 0.0f)
		{
			glRotatef(m_Angle, m_Rotation.x, m_Rotation.y, m_Rotation.z);
		}
		Andromeda_2d_begin(Andromeda_triangle_fan);
		OpenGL::Legacy::draw_filled_circle(ScreenToWorldSpace(m_Position), m_Radius, m_Segments, m_Triangles);
		Andromeda_2d_end();
		glPopMatrix();
	}
};

struct Andromeda::Components::Transform : public Andromeda::Entity
{
	float m_Scale = 0.5f;
	float m_Angle = 0.0f;

	Transform(const vec3 &&pos, const vec3 &&rot, float scale) : m_Scale(scale)
	{
		m_Name = "Transform";
		m_Position = pos;
		m_Rotation = rot;
	}

	void update(double dt) {}
};

struct Andromeda::Components::LegacyQuad : public Andromeda::Entity, public Andromeda::Component
{
	float m_Radius = 100.f;
	float m_Angle = 0.0f;

	uint32_t m_Texture;

	bool m_UseTransform = true;
	vec2 m_Dimensions;

	LegacyQuad() : m_Dimensions(0.5f, 0.5f)
	{
		m_Name = "LegacyQuad";
	}

	void update(double dt)
	{

		UpdateProjection(0.0f, float(Andromeda::Window::GetWindowInfo().width), 0.0f, float(Andromeda::Window::GetWindowInfo().height), 0.00001f, -100000.0f);

		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (m_Angle != 0.0f)
		{
			glRotatef(m_Angle, m_Rotation.x, m_Rotation.y, m_Rotation.z);
		}

		if (m_Texture)
		{
			glBindTexture(GL_TEXTURE_2D, m_Texture);
			glEnable(GL_TEXTURE_2D);
		}

		Andromeda_2d_begin(Andromeda_quads);
		OpenGL::Legacy::draw_quad(ScreenToWorldSpace(m_Position), m_Dimensions);
		Andromeda_2d_end();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
};

struct Andromeda::Components::Quad : public Andromeda::Entity
{

	Andromeda::Renderer m_Renderer;

	mat4 m_ProjectionMatrix = mat4(1.0f);

	Quad()
	{
		m_Name = "Quad";
		m_Renderer.Init(
				OpenGL::Shader(
						"./engine/assets/shaders/basic/color.frag",
						"./engine/assets/shaders/basic/color.vert"),
				OpenGL::VertexBuffer(36 * sizeof(float)));

		float vertexBufferData[36] = {
				// Positions         // colors
				-0.1f,
				-0.1f,
				0.0f,
				1.0f,
				1.0f,
				1.0f,
				0.1f,
				-0.1f,
				0.0f,
				1.0f,
				1.0f,
				1.0f,
				-0.1,
				0.1f,
				0.0f,
				1.0f,
				1.0f,
				1.0f,

				-0.1f,
				0.1f,
				0.0f,
				1.0f,
				1.0f,
				1.0f,
				0.1f,
				-0.1f,
				0.0f,
				1.0f,
				1.0f,
				1.0f,
				0.1f,
				0.1f,
				0.0f,
				1.0f,
				1.0f,
				1.0f,
		};

		m_Renderer.ResetSubmitton();
		m_Renderer.Submit(vertexBufferData, 36 * sizeof(float), 6, 6 * sizeof(float));
	}

	void update(double dt)
	{
		//
		// m_Renderer.SetViewProjection(m_ProjectionMatrix);
		//
		// We meed way to acces window information
		// m_Renderer.SetResolution(vec2(1080, 720));
		m_Renderer.SetTime(dt);
		m_Renderer.Draw();
	}
};

struct Andromeda::Components::Texture2d : public Andromeda::Entity
{
	const char *m_Path;
	uint32_t m_Texture;

	Texture2d(const char *path) : m_Path(path)
	{
		m_Name = "Texture2d";
		L::Graphics::OpenGL::Texture::Create(m_Path, m_Texture);
	}
};

struct Andromeda::Components::Sphere : public Andromeda::Entity, public Andromeda::Component
{
	float m_Angle = 0.0f;
	float m_Radius = 10.0f;

	uint32_t m_Segments = 80;
	uint32_t m_Texture;

	Sphere()
	{
		m_Name = "Sphere";
	};

	void update(double dt)
	{

		UpdateProjection(0.0f, float(Andromeda::Window::GetWindowInfo().width), 0.0f, float(Andromeda::Window::GetWindowInfo().height), 0.00001f, -100000.0f);

		glPushMatrix();
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);

		if (m_Angle != 0.0f)
		{
			glRotatef(m_Angle, m_Rotation.x, m_Rotation.y, m_Rotation.z);
		}

		if (m_Texture)
		{
			glBindTexture(GL_TEXTURE_2D, m_Texture);
			glEnable(GL_TEXTURE_2D);
		}

		// yellow diffuse : color where light hit directly the object's surface
		float diffuse[] = {1.0f, 1.0f, 0.0f, 1.0f};

		// Yellow ambient : color applied everywhere
		float ambient[] = {0.f, 0.f, 1.f, 1.000f};

		vec3 lightPosition = m_Position + vec3(2.0f, 2.0f, -7.0f);

		// Ambient light component
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

		// Diffuse light component
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

		//Light position
		glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(lightPosition));

		//Enable the first light and the lighting mode
		glEnable(GL_LIGHTING);

		Andromeda_2d_begin(Andromeda_triangles);
		OpenGL::Legacy::draw_sphere(ScreenToWorldSpace(m_Position), m_Segments, m_Radius);
		Andromeda_2d_end();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glPopMatrix();
	}
};

#endif
