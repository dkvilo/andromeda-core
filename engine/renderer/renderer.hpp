#ifndef __ENGINE_RENDERER__
#define __ENGINE_RENDERER__

#include "andromeda.hpp"

class Andromeda::Renderer
{
private:
  Andromeda::RenderingAPI SelectedAPI;

public:
  Renderer()
  {
    /**
     * 
     * Set default rendering API to OpenGL
     * 
     */
    this->SelectedAPI = Andromeda::RenderingAPI::OpenGL;
  }

  void UseRenderingAPI(Andromeda::RenderingAPI target)
  {
    this->SelectedAPI = target;
  }

  Andromeda::RenderingAPI GetAPI()
  {
    return this->SelectedAPI;
  }

  void Submit()
  {
  }
};

#endif // __ENGINE_RENDERER__