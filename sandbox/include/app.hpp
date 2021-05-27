#ifndef __SANDBOX_APP__
#define __SANDBOX_APP__

#include "andromeda.hpp"
#include "window/window.hpp"
#include "editor/editor.hpp"

#include "glm/vec3.hpp"
#include "game_object.hpp"

struct Sandbox
{
private:
  Andromeda::Window *my_wind;

public:
  int Width, Height;
  double deltaTime;
  double elapsedTime = Andromeda::Window::TimeNow();

  Sandbox()
  {
    // Configure Window
    Andromeda::Types::WindowConfog conf{"Andromeda", 1080, 720};

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

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)width / (float)height;
    glOrtho(-aspect, aspect, -1, 1, 0.00001, -100000);

    glEnable(GL_TEXTURE_2D);
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
