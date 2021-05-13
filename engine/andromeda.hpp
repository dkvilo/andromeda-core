#ifndef __ANDROMEDA_CORE_API__
#define __ANDROMEDA_CORE_API__

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(check, msg, ...)              \
  {                                          \
    if (!(check))                            \
    {                                        \
      printf("Assertion failed: %s\n", msg); \
      if (__VA_ARGS__ != NULL)               \
      {                                      \
        printf("\tArg: %s\n", __VA_ARGS__);  \
      }                                      \
      exit(1);                               \
    }                                        \
  }

namespace Andromeda
{
  struct Entity;
  struct Component;
  struct UI;

  class Editor;
  class Window;
  class Log;
}

namespace Andromeda::Components
{
  struct RGBColorMaterial;
  struct Shape2d;
  struct Transform;
  struct Stroke;
  class Texture2d;
}

namespace Andromeda::Types
{
  struct WindowConfog;
}

#endif // __ANDROMEDA_CORE_API__