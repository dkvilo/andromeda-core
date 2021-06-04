#ifndef __ANDROMEDA_CORE_API__
#define __ANDROMEDA_CORE_API__

#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"

namespace Andromeda
{

  enum RenderingAPI
  {
    OpenGL,
    Metal,
    WebGL,
    None
  };

  class Renderer;
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
  struct Quad;
  struct Sphere;
  struct Texture2d;

}

namespace Andromeda::Types
{
  struct WindowConfog;
}

#endif // __ANDROMEDA_CORE_API__