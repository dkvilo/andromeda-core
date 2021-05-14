#ifndef ANDROMEDA_LIBS_COMPONENTS
#define ANDROMEDA_LIBS_COMPONENTS

#include "glm/vec3.hpp"

#include "andromeda.hpp"
#include "entity/entity.hpp"

#include "../libs/libs.hpp"
#include "../libs/opengl/legacy.hpp"

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
    L::Graphics::OpenGL::Legacy::fill_color(this->color);
  }
};

class Andromeda::Components::Texture2d : public Andromeda::Entity
{
private:
  size_t texture_id;

public:
  Texture2d(const char *src)
  {
    // this->texture_id = L::Graphics::OpenGL::new_texture(src);
  }

  void update(double dt)
  {
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0, 0);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(300, 0);

    glTexCoord2f(1, 0);
    glVertex2f(300, 90);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0, 90);
    glEnd();
  }

  ~Texture2d()
  {
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
};

struct Andromeda::Components::Stroke : public Andromeda::Entity
{
  Andromeda::Components::RGBColorMaterial *color_material;

  float offset = 25;
  float radius = 100;
  int segments = 100;
  int line_width = 8;
  float angle = 0.0f;

  Stroke()
  {
    this->name = "Stroke2d";
    this->rotation = glm::vec3(0, 0, 0);
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
    L::Graphics::OpenGL::Legacy::draw_circle(this->position, this->radius + this->offset, this->segments);
    Andromeda_2d_end();
  };
};

struct Andromeda::Components::Shape2d : public Andromeda::Entity
{

  float radius = 100.f;
  int segments = 100;
  int triangles = 100;

  Shape2d()
  {
    this->name = "Shape2d";
  };

  void update(double dt)
  {
    Andromeda_2d_begin(Andromeda_triangle_fan);
    L::Graphics::OpenGL::Legacy::draw_filled_circle(this->position, this->radius, this->segments, this->triangles);
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
