#ifndef __ANDROMEDA_LIBS_VEC2__
#define __ANDROMEDA_LIBS_VEC2__

#include "../libs.hpp"

struct L::Vec2
{
  float x, y;

  Vec2(float _x, float _y)
  {
    this->x = _x;
    this->y = _y;
  }

  Vec2() {}

  inline L::Vec2 operator+(L::Vec2 *a)
  {
    return L::Vec2{
        this->x + a->x,
        this->y + a->y};
  }

  inline L::Vec2 operator-(L::Vec2 *a)
  {
    return L::Vec2{
        this->x - a->x,
        this->y - a->y};
  }

  inline L::Vec2 operator*(L::Vec2 *a)
  {
    return L::Vec2{
        this->x * a->x,
        this->y * a->y};
  }

  inline L::Vec2 operator/(L::Vec2 *a)
  {
    return L::Vec2{
        this->x / a->x,
        this->y / a->y};
  }

  inline L::Vec2 product(L::Vec2 *a)
  {
  }

  inline L::Vec2 normalized()
  {
  }

  inline L::Vec2 normalize()
  {
  }

  inline L::Vec2 magnitude()
  {
  }
};

#endif // __ANDROMEDA_LIBS_VEC2__