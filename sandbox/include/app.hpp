#ifndef __SANDBOX_APP__
#define __SANDBOX_APP__

#include "andromeda.hpp"
#include "window/window.hpp"
#include "entity/entity.hpp"

#define ANDROMEDA_EDITOR
#include "editor/editor.hpp"

#define GLM_HAS_UNRESTRICTED_UNIONS
#include "glm/vec3.hpp"

#include "../../libs/math/functions.hpp"
#include "../../libs/math/vec2.hpp"
#include "../../libs/proxima/proxima.hpp"
#include "../../libs/gl/gl.hpp"

//
// Do not forget to housekeep the size of the array
//
#define ENTITY_MANAGER_SIZE 12

struct Sandbox
{
private:
  Andromeda::Window *my_wind;
  L::Proxima *proxima_vm;

public:
  int Width, Height;
  double deltaTime;
  double elapsedTime = Andromeda::Window::TimeNow();
  Andromeda::Entity *EntityRegistry[ENTITY_MANAGER_SIZE];

  Sandbox()
  {
    // Load Proxima VM
    this->proxima_vm->run("./test.prx");

    // Configure Window
    Andromeda::Types::WindowConfog conf{
        "Andromeda Core V: 0.0.101-rc",
        1080,
        720,
    };

    // Create new Window
    this->my_wind = new Andromeda::Window(&conf);

    // Attach Window Key handler
    Andromeda::Window::KeyHandler(this->GetWidnowId(), Sandbox::KeyHandler);
  }

  inline GLFWwindow *const GetWidnowId() const
  {
    return this->my_wind->GetId();
  }

  inline Andromeda::Window *Window() const
  {
    return this->my_wind;
  }

  void UpdateTime(double ct)
  {
    this->deltaTime = ct - this->elapsedTime;
    this->elapsedTime = ct;
  }

  void Resize()
  {
    glfwGetWindowSize(this->GetWidnowId(), &this->Width, &this->Height);
  }

  static void Draw(int width, int height);

  static void BaseRenderer(int width, int height)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 100);
    glViewport(0, 0, width, height);
  }
  /*
	 *
	 * WINDOW Callbacks
	 *
	 */
  static void KeyHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  }
};

#endif // __SANDBOX_APP__
