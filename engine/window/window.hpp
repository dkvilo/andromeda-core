#ifndef __ENGINE_WINDOW__
#define __ENGINE_WINDOW__

#include "andromeda.hpp"

#include "glad/glad.h"
#include "../../libs/libs.hpp"

#include "GLFW/glfw3.h"
#include "log/log.hpp"

struct Andromeda::Types::WindowConfog
{
  char *title;
  int width, height;
};

class Andromeda::Window
{

private:
  GLFWwindow *m_WindowID;
  GLFWmonitor *m_MonitorID;
  const GLFWvidmode *m_VideoMode;

public:
  Window(Andromeda::Types::WindowConfog *conf)
  {

    Andromeda::Log::SetPrefix("Window");

    {
      int status = (int)glfwInit() == GLFW_TRUE;
      ASSERT(status, "Error while initializing GLFW", NULL);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);

    m_MonitorID = glfwGetPrimaryMonitor();
    m_VideoMode = glfwGetVideoMode(m_MonitorID);
    m_WindowID = glfwCreateWindow(conf->width, conf->height, static_cast<const char *>(conf->title), nullptr, nullptr);

    glfwMakeContextCurrent(m_WindowID);
    glfwSwapInterval(1);

    {
      int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
      ASSERT(status, "Failed to initialize OpenGL loader", NULL);
    }

    Andromeda::Log::Print("glfw window has been initialzed");
  }

  static GLFWkeyfun KeyHandler(GLFWwindow *window, GLFWkeyfun callback)
  {
    return glfwSetKeyCallback(window, callback);
  }

  static int ShouldClose(GLFWwindow *handle)
  {
    return glfwWindowShouldClose(handle);
  }

  static double TimeNow(void)
  {
    return glfwGetTime();
  }

  static void PullEvents()
  {
    glfwPollEvents();
  }

  static void SwapBuffers(GLFWwindow *window)
  {
    glfwSwapBuffers(window);
  }

  static void Destory(GLFWwindow *window)
  {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void HideCursor() const
  {
    glfwSetInputMode(m_WindowID, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  inline GLFWwindow *const GetId() const
  {
    return m_WindowID;
  }

  inline GLFWmonitor *const GetMonitorId() const
  {
    return m_MonitorID;
  }

  inline const GLFWvidmode *const GetVideoMode() const
  {
    return m_VideoMode;
  }
};

#endif // __ENGINE_WINDOW__
