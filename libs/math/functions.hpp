#ifndef __ANDROMEDA_LIBS_MATH_FUNCTIONS__
#define __ANDROMEDA_LIBS_MATH_FUNCTIONS__

#include "../libs.hpp"

static inline float L::Math::Lerp(float a, float b, float t)
{
  return (1.0f - t) * a + b * t;
}

static inline float L::Math::InvLerp(float a, float b, float v)
{
  return (v - a) / (b - a);
}

static inline float L::Math::Remap(float i_max, float i_min, float o_min, float o_max, float v)
{
  float t = L::Math::InvLerp(i_min, i_max, v);
  return L::Math::Lerp(o_min, o_max, t);
}

// XOR Random
static inline float L::Math::RnR(float min, float max)
{

  uint32_t range = 0xf2eec0de;

  range ^= (range << 13);
  range ^= (range >> 17);
  range ^= (range << 5);

  float random_zero_to_one = float(range) * (1.0f / 4294967296.0f);
  return min + (max - min) * random_zero_to_one;
}

#endif // __ANDROMEDA_LIBS_MATH_FUNCTIONS__