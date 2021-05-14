#ifndef __ANDROMEDA_LIBS_VEC2__
#define __ANDROMEDA_LIBS_VEC2__

#include "../libs.hpp"

struct L::Math::Vec2
{
  float x, y;

  Vec2(float _x, float _y)
  {
    this->x = _x;
    this->y = _y;
  }

  Vec2() {}

  inline L::Math::Vec2 operator+(L::Math::Vec2 *a)
  {
    return L::Math::Vec2{
        this->x + a->x,
        this->y + a->y};
  }

  inline L::Math::Vec2 operator-(L::Math::Vec2 *a)
  {
    return L::Math::Vec2{
        this->x - a->x,
        this->y - a->y};
  }

  inline L::Math::Vec2 operator*(L::Math::Vec2 *a)
  {
    return L::Math::Vec2{
        this->x * a->x,
        this->y * a->y};
  }

  inline L::Math::Vec2 operator/(L::Math::Vec2 *a)
  {
    return L::Math::Vec2{
        this->x / a->x,
        this->y / a->y};
  }

  inline L::Math::Vec2 product(L::Math::Vec2 *a)
  {
  }

  inline L::Math::Vec2 normalized()
  {
  }

  inline L::Math::Vec2 normalize()
  {
  }

  inline L::Math::Vec2 magnitude()
  {
  }
};

#endif // __ANDROMEDA_LIBS_VEC2__