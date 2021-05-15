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
  GLFWwindow *m_window_id;
  GLFWmonitor *m_monitor_id;
  const GLFWvidmode *m_video_mode;

public:
  Window(Andromeda::Types::WindowConfog *conf)
  {

    {
      int status = (int)glfwInit() == GLFW_TRUE;
      ASSERT(status, "Error while initializing GLFW", NULL);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);

    this->m_monitor_id = glfwGetPrimaryMonitor();
    this->m_video_mode = glfwGetVideoMode(this->m_monitor_id);
    this->m_window_id = glfwCreateWindow(conf->width, conf->height, static_cast<const char *>(conf->title), nullptr, nullptr);

    glfwMakeContextCurrent(this->m_window_id);
    glfwSwapInterval(1);

    {
      int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
      ASSERT(status, "Failed to initialize OpenGL loader", NULL);
    }
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
    glfwSetInputMode(this->m_window_id, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  inline GLFWwindow *const GetId() const
  {
    return this->m_window_id;
  }

  inline GLFWmonitor *const GetMonitorId() const
  {
    return this->m_monitor_id;
  }

  inline const GLFWvidmode *const GetVideoMode() const
  {
    return this->m_video_mode;
  }
};

#endif // __ENGINE_WINDOW__
