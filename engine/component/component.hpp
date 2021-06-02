#ifndef ANDROMEDA_ENGINE_COMPONENTS
#define ANDROMEDA_ENGINE_COMPONENTS

#include "andromeda.hpp"

#include "entity/entity.hpp"
#include "renderer/renderer.hpp"

#include "../libs/libs.hpp"
#include "../libs/opengl/legacy.hpp"
#include "../libs/opengl/shader.hpp"

#include "glm/vec3.hpp"

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

struct Andromeda::Components::Stroke : public Andromeda::Entity
{
  RGBColorMaterial *m_ColorMaterial;

  float m_Offset = 0.0f;
  float m_Radius = 10.0f;
  int m_Segments = 100;
  int m_LineWidth = 8;
  float m_Angle = 0.0f;

  Stroke() : m_ColorMaterial(new RGBColorMaterial(vec3(0.121f, 0.917f, 0.566f)))
  {
    m_Name = "Stroke2d";
    m_Rotation = vec3(0, 0, 0);
  };

  void update(double dt)
  {
    glLineWidth(m_LineWidth);
    glPushMatrix();
    if (m_Angle != 0.0f)
    {
      glRotatef(m_Angle, m_Rotation.x, m_Rotation.y, m_Rotation.z);
    }
    Andromeda_2d_begin(Andromeda_line_loop);
    m_ColorMaterial->update(dt);
    OpenGL::Legacy::draw_circle(m_Position, m_Radius + m_Offset, m_Segments);
    Andromeda_2d_end();
    glPopMatrix();
  };
};

struct Andromeda::Components::Shape2d : public Andromeda::Entity
{

  float m_Radius = 100.f;
  float m_Angle = 0.0f;
  int m_Segments = 100;
  int m_Triangles = 100;

  Shape2d()
  {
    m_Name = "Shape2d";
  };

  void update(double dt)
  {
    glPushMatrix();
    if (m_Angle != 0.0f)
    {
      glRotatef(m_Angle, m_Rotation.x, m_Rotation.y, m_Rotation.z);
    }
    Andromeda_2d_begin(Andromeda_triangle_fan);
    OpenGL::Legacy::draw_filled_circle(m_Position, m_Radius, m_Segments, m_Triangles);
    Andromeda_2d_end();
    glPopMatrix();
  };
};

struct Andromeda::Components::Transform : public Andromeda::Entity
{
  float m_Scale = 0.5f;
  float m_Angle = 0.0f;

  Transform(const vec3 &&pos, const vec3 &&rot, float scale) : m_Scale(scale)
  {
    m_Name = "Transfrom";
    m_Position = pos;
    m_Rotation = rot;
  };

  void update(double dt){};
};

struct Andromeda::Components::Quad : public Andromeda::Entity
{

  Andromeda::Renderer m_Renderer;

  Quad()
  {
    m_Name = "Quad";
    m_Renderer.Init(
        OpenGL::Shader("./shaders/basic/color.frag", "./shaders/basic/color.vert"),
        OpenGL::VertexBuffer(18 * sizeof(float)));
  };

  void update(double dt)
  {

    m_Renderer.ResetSubmitton();

    float positions[18] = {
        -0.1f + m_Position.x, -0.1f + m_Position.y, 0.0f,
        0.1f + m_Position.x, -0.1f + m_Position.y, 0.0f,
        -0.1 + m_Position.x, 0.1f + m_Position.y, 0.0f,

        -0.1f + m_Position.x, 0.1f + m_Position.y, 0.0f,
        0.1f + m_Position.x, -0.1f + m_Position.y, 0.0f,
        0.1f + m_Position.x, 0.1f + m_Position.y, 0.0f};

    m_Renderer.Submit(positions, 18 * sizeof(float), 3, 3 * sizeof(float));
    m_Renderer.Draw();
  };
};

struct Andromeda::Components::Sphere : public Andromeda::Entity
{

  float m_Angle = 0.0f;
  uint32_t m_Segments = 100;
  float m_Radius = 10.0f;

  Sphere()
  {
    m_Name = "Sphere";
  };

  void update(double dt)
  {
    glPushMatrix();
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (m_Angle != 0.0f)
    {
      glRotatef(m_Angle, m_Rotation.x, m_Rotation.y, m_Rotation.z);
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
    glLightfv(GL_LIGHT0, GL_POSITION, (float *)&(lightPosition));

    //Enable the first light and the lighting mode
    glEnable(GL_LIGHTING);

    Andromeda_2d_begin(Andromeda_triangles);
    // vec3 color(1, 0, 0);
    // OpenGL::Legacy::fill_color(color);
    OpenGL::Legacy::draw_sphere(m_Position, m_Segments, m_Radius);
    Andromeda_2d_end();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glPopMatrix();
  };
};

#endif
