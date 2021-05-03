#ifndef __ANDROMEDA_LIBS_MATH_FUNCTIONS__
#define __ANDROMEDA_LIBS_MATH_FUNCTIONS__

#include "../libs.hpp"

static inline float L::Lerp(float a, float b, float t)
{
  return (1.0f - t) * a + b * t;
}

static inline float L::InvLerp(float a, float b, float v)
{
  return (v - a) / (b - a);
}

static inline float L::Remap(float i_max, float i_min, float o_min, float o_max, float v)
{
  float t = L::InvLerp(i_min, i_max, v);
  return L::Lerp(o_min, o_max, t);
}

#endif // __ANDROMEDA_LIBS_MATH_FUNCTIONS__