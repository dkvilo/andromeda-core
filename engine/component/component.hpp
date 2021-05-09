
#ifndef ANDROMEDA_LIBS_COMPONENTS
#define ANDROMEDA_LIBS_COMPONENTS

#include "glm/vec3.hpp"

#include "andromeda.hpp"
#include "entity/entity.hpp"

#include "../libs/libs.hpp"
#include "../libs/gl/ogl.hpp"

struct Andromeda::Components::RGBColorMaterial : Andromeda::Entity
{
  glm::vec3 color;

  RGBColorMaterial(const glm::vec3 &&color)
  {
    this->name = "Color Material";
    this->color = color;
  }

  void update(double dt)
  {
    L::Graphics::OGL::fill_color(this->color);
  }
};

struct Andromeda::Components::Gizmo2d : public Andromeda::Entity
{
  Andromeda::Components::RGBColorMaterial *color_material;

  float offset = 5;
  float radius = 100;
  int segments = 11;
  int line_width = 5;
  float angle = 0.0f;

  Gizmo2d()
  {
    this->name = "Gizmo2d";
    this->color_material = new Andromeda::Components::RGBColorMaterial(glm::vec3(0.121f, 0.917f, 0.566f));
  };

  void update(double dt)
  {
    glLineWidth(this->line_width);
    if (angle != 0.0f)
    {
      glRotatef(this->angle, this->rotation.x, this->rotation.y, this->rotation.z);
    }
    Andromeda_2d_begin(Andromeda_line_loop);
    this->color_material->update(dt);
    L::Graphics::OGL::draw_circle(this->position, this->radius + this->offset, this->segments);
    Andromeda_2d_end();
  };
};

struct Andromeda::Components::Circle2d : public Andromeda::Entity
{

  float radius;

  Circle2d()
  {
    this->name = "Circle2d";
  };

  void update(double dt)
  {
    Andromeda_2d_begin(Andromeda_triangle_fan);
    L::Graphics::OGL::draw_filled_circle(this->position, this->radius, 100, 100);
    Andromeda_2d_end();
  };
};

struct Andromeda::Components::Transform : public Andromeda::Entity
{
  float scale = 10.f;

  Transform(const glm::vec3 &&pos, const glm::vec3 &&rot, float scale)
  {
    this->name = "Transfrom";
    this->position = pos;
    this->rotation = rot;
    this->scale = scale;
  };
  void update(double dt){};
};

#endif
