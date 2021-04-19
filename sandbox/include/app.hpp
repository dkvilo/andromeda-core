#ifndef __SANDBOX_APP__
#define __SANDBOX_APP__

#include "andromeda.hpp"
#include "log/log.hpp"
#include "window/window.hpp"
#include "entity/entity.hpp"
#include "../../libs/math/vec2.hpp"
struct Sandbox
{
private:
  Andromeda::Log logger;
  Andromeda::Window *my_wind;

public:
  L::Vec2 mouse_pos;

  inline void Init()
  {
    Andromeda::Types::WindowConfog conf{
        .title = "Hello, World",
        .width = 1080,
        .height = 720,
    };
    this->my_wind = new Andromeda::Window(&conf);
    this->my_wind->hide_cursor();
  }

  inline GLFWwindow *get_widnow()
  {
    return this->my_wind->get_id();
  }

  inline void Log(const char *message)
  {
    logger.Print(message);
  }

  Sandbox()
  {
    logger.set_prefix("Sandbox");
  }

  ~Sandbox() {}
  /*
	 *
	 * WINDOW Callbacks
	 *
	 */
  inline static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  }
};

#endif // __SANDBOX_APP__
