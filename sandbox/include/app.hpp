#ifndef __SANDBOX_APP__
#define __SANDBOX_APP__

#include "andromeda.hpp"
#include "window/window.hpp"
#include "editor/editor.hpp"

#include "glm/vec3.hpp"
#include "game_object.hpp"

struct Sandbox
{
public:
  int m_Width, m_Height;
  double m_DeltaTime;
  double m_ElapsedTime = Andromeda::Window::TimeNow();

  Sandbox()
  {
    // Configure Window
    Andromeda::Types::WindowConfog conf{"Andromeda", 1080, 720};

    // Create new Window
    m_Window = new Andromeda::Window(&conf);

    // Attach Window Key handler
    Andromeda::Window::KeyHandler(GetWidnowId(), Sandbox::KeyHandler);
  }

  inline GLFWwindow *const GetWidnowId() const
  {
    return m_Window->GetId();
  }

  inline Andromeda::Window *Window() const
  {
    return m_Window;
  }

  void UpdateTime(double ct)
  {
    m_DeltaTime = ct - m_ElapsedTime;
    m_ElapsedTime = ct;
  }

  void Resize()
  {
    glfwGetWindowSize(GetWidnowId(), &m_Width, &m_Height);
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

private:
  Andromeda::Window *m_Window;
};

#endif // __SANDBOX_APP__
