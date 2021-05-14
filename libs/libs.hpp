#ifndef __ANDROMEDA_LIBS__
#define __ANDROMEDA_LIBS__

namespace L
{

  namespace Graphics
  {
    namespace OpenGL
    {
      class Legacy;
      class Shader;
      class VertexBuffer;
      class IndexBuffer;
    };
  }

  namespace Fs
  {
    static inline const char *ReadFileContent(const char *path);
  }
  namespace Math
  {
    struct Vec2;
    struct Quat;
    struct Proxima;
    static inline float Lerp(float a, float b, float t);
    static inline float InvLerp(float a, float b, float v);
    static inline float Remap(float i_max, float i_min, float o_min, float o_max, float v);
    static inline float RnR(float min, float max);
  }
}

#endif // __ANDROMEDA_LIBS__