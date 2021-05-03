#ifndef __ANDROMEDA_LIBS_GL__
#define __ANDROMEDA_LIBS_GL__

#include "../libs.hpp"

class L::GL
{

  static GL &Get()
  {
    static GL instance;
    return instance;
  }

public:
  static L::Vec2 put_pixel(unsigned int size, const L::Vec2 &pos)
  {
    return Get().put_pixel_impl(size, pos);
  }

private:
  L::Vec2 put_pixel_impl(unsigned int size, const L::Vec2 &pos)
  {

    L::Vec2 vert_pos(
        (float)pos.x + (size / 2),
        (float)pos.y + (size / 2));

    glPointSize(size);
    glTranslatef(pos.x, pos.y, 0);

    glBegin(GL_POINTS);
    glVertex3f(vert_pos.x, vert_pos.y, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glEnd();

    return vert_pos;
  }
};

#endif // __ANDROMEDA_LIBS_GL__