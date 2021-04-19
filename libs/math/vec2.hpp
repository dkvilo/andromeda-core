#ifndef __ANDROMEDA_LIBS_VEC2__
#define __ANDROMEDA_LIBS_VEC2__

#include "../libs.hpp"

struct L::Vec2
{
  double x, y;

  Vec2(double _x, double _y)
  {
    this->x = _x;
    this->y = _y;
  }

  Vec2() {}

  inline L::Vec2 operator+(L::Vec2 *a)
  {
    return L::Vec2{
      x : this->x + a->x,
      y : this->y + a->y
    };
  }

  inline L::Vec2 operator-(L::Vec2 *a)
  {
    return L::Vec2{
      x : this->x - a->x,
      y : this->y - a->y
    };
  }

  inline L::Vec2 operator*(L::Vec2 *a)
  {
    return L::Vec2{
      x : this->x * a->x,
      y : this->y * a->y
    };
  }

  inline L::Vec2 operator/(L::Vec2 *a)
  {
    return L::Vec2{
      x : this->x / a->x,
      y : this->y / a->y
    };
  }
};

#endif // __ANDROMEDA_LIBS_VEC2__