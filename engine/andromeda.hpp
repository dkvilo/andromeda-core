#ifndef __ANDROMEDA_CORE_API__
#define __ANDROMEDA_CORE_API__

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(check, msg)                   \
  {                                          \
    if (!(check))                            \
    {                                        \
      printf("Assertion failed: %s\n", msg); \
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
  struct Circle2d;
  struct Transform;
  struct Gizmo2d;
}

namespace Andromeda::Types
{
  struct WindowConfog;
}

#endif // __ANDROMEDA_CORE_API__