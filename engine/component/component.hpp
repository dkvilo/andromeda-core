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
  vec3 color;

  RGBColorMaterial(const vec3 &&color)
  {
    this->name = "Color Material";
    this->color = color;
  }

  void update(double dt)
  {
    OpenGL::Legacy::fill_color(this->color);
  }
};

struct Andromeda::Components::Quad : public Andromeda::Entity
{

  float height = 0.0f;
  float width = 0.0f;

  Andromeda::Renderer renderer;

  Quad()
  {
    this->name = "Quad";
    float positions[18] = {
        -0.1f, -0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,
        -0.1f, 0.1f, 0.0f,

        -0.1f, 0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,
        0.1f, 0.1f, 0.0f};

    this->renderer.Init(
        OpenGL::Shader(
            "./shaders/basic/color.frag",
            "./shaders/basic/color.vert"),
        OpenGL::VertexBuffer(18 * sizeof(float)));

    this->renderer.Submit(positions, 18 * sizeof(float), 3, 3 * sizeof(float));
  };

  void update(double dt)
  {
    this->renderer.Draw();
  };
};

struct Andromeda::Components::Stroke : public Andromeda::Entity
{
  RGBColorMaterial *color_material;

  float offset = 0.0f;
  float radius = 10.0f;
  int segments = 100;
  int line_width = 8;
  float angle = 0.0f;

  Stroke()
  {
    this->name = "Stroke2d";
    this->rotation = vec3(0, 0, 0);
    this->color_material = new RGBColorMaterial(vec3(0.121f, 0.917f, 0.566f));
  };

  void update(double dt)
  {
    glLineWidth(this->line_width);
    glPushMatrix();
    if (angle != 0.0f)
    {
      glRotatef(this->angle, this->rotation.x, this->rotation.y, this->rotation.z);
    }
    Andromeda_2d_begin(Andromeda_line_loop);
    this->color_material->update(dt);
    OpenGL::Legacy::draw_circle(this->position, this->radius + this->offset, this->segments);
    Andromeda_2d_end();
    glPopMatrix();
  };
};

struct Andromeda::Components::Shape2d : public Andromeda::Entity
{

  float radius = 100.f;
  float angle = 0.0f;
  int segments = 100;
  int triangles = 100;

  Shape2d()
  {
    this->name = "Shape2d";
  };

  void update(double dt)
  {
    glPushMatrix();
    if (this->angle != 0.0f)
    {
      glRotatef(this->angle, this->rotation.x, this->rotation.y, this->rotation.z);
    }
    Andromeda_2d_begin(Andromeda_triangle_fan);
    OpenGL::Legacy::draw_filled_circle(this->position, this->radius, this->segments, this->triangles);
    Andromeda_2d_end();
    glPopMatrix();
  };
};

struct Andromeda::Components::Transform : public Andromeda::Entity
{
  float scale = 0.5f;
  float angle = 0.0f;

  Transform(const vec3 &&pos, const vec3 &&rot, float scale)
  {
    this->name = "Transfrom";
    this->position = pos;
    this->rotation = rot;
    this->scale = scale;
  };
  void update(double dt){};
};

#endif
