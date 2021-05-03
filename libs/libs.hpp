#ifndef __ANDROMEDA_LIBS__
#define __ANDROMEDA_LIBS__

namespace L
{
  struct Vec2;
  struct Quat;
  struct Proxima;
  class GL;

  static inline float Lerp(float a, float b, float t);
  static inline float InvLerp(float a, float b, float v);
  static inline float Remap(float i_max, float i_min, float o_min, float o_max, float v);
}

#endif // __ANDROMEDA_LIBS__