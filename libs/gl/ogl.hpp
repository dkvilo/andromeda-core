#ifndef __ANDROMEDA_LIBS_OGL__
#define __ANDROMEDA_LIBS_OGL__

#define Andromeda_2d_begin glBegin
#define Andromeda_2d_end glEnd

#define Andromeda_points GL_POINTS
#define Andromeda_lines GL_LINES
#define Andromeda_line_loop GL_LINE_LOOP
#define Andromeda_line_strip GL_LINE_STRIP
#define Andromeda_triangles GL_TRIANGLES
#define Andromeda_triangle_strip GL_TRIANGLE_STRIP
#define Andromeda_triangle_fan GL_TRIANGLE_FAN
#define Andromeda_quads GL_QUADS

#include "../libs.hpp"

#include <math.h>

class L::Graphics::OGL
{
private:
  static OGL &Get()
  {
    static OGL instance;
    return instance;
  }

public:
  static void put_pixel(size_t size, const glm::vec3 pos)
  {
    Get().put_pixel_impl(size, pos);
  }

  static void fill_color(glm::vec3 &color)
  {
    glColor3f(color.r, color.g, color.b);
  }

  static void draw_circle(glm::vec3 position, float r, int segments)
  {
    Get().draw_circle_impl(position.x, position.y, r, segments);
  }

  static void draw_filled_circle(glm::vec3 position, float r, int segments, int max_triangle)
  {
    Get().draw_filled_circle_impl(position.x, position.y, r, segments, max_triangle);
  }

  static void blend_alpha()
  {
    Get().blend_alpha_impl();
  }

private:
  void blend_alpha_impl()
  {
    // TODO: make configurable
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void draw_filled_circle_impl(float cx, float cy, float r, int segments, int max_triangle)
  {
    double twicePi = 2.0 * 3.142;

    glVertex2f(cx, cy);
    for (size_t i = 0; i <= segments; i++)
    {
      glVertex2f(
          (cx + (r * cos(i * twicePi / max_triangle))), (cy + (r * sin(i * twicePi / max_triangle))));
    }
  }

  void draw_circle_impl(float cx, float cy, float r, int segments)
  {

    for (int i = 0; i < segments; i++)
    {
      float theta = 2.0f * 3.1415926f * float(i) / float(segments);
      float x = r * cosf(theta);
      float y = r * sinf(theta);
      glVertex2f(x + cx, y + cy);
    }
  }

  void put_pixel_impl(size_t size, const glm::vec3 pos)
  {
    glPointSize(size);
    Andromeda_2d_begin(Andromeda_points);
    glVertex3f(pos.x, pos.y, pos.z);
    Andromeda_2d_end();
  }
};

#endif // __ANDROMEDA_LIBS_OGL__