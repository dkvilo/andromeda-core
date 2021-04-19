#ifndef __ENGINE_WINDOW__
#define __ENGINE_WINDOW__

#include "GLFW/glfw3.h"

#include "andromeda.hpp"
#include "log/log.hpp"

struct Andromeda::Types::WindowConfog
{
  char 	*title;
  int 	width, height;
};

class Andromeda::Window
{

private:
  Andromeda::Log 		logger;
  GLFWwindow 				*m_window_id;
  GLFWmonitor 			*m_monitor_id;
  const GLFWvidmode *m_video_mode;

public:
  Window(Andromeda::Types::WindowConfog *conf)
  {
    // Initialize Logger
    logger.set_prefix("Window");
    if (glfwInit() != GLFW_TRUE)
    {
      logger.Print("Error While Initializeing GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    // Remove TitleBar
    glfwWindowHint(GLFW_DECORATED, false);

    this->m_monitor_id = glfwGetPrimaryMonitor();
    this->m_video_mode = glfwGetVideoMode(this->m_monitor_id);
    this->m_window_id = glfwCreateWindow(conf->width, conf->height, (const char *)conf->title, nullptr, nullptr);

    glfwMakeContextCurrent(this->m_window_id);
    glfwSwapInterval(1);
  }

  void hide_cursor()
  {
    glfwSetInputMode(this->m_window_id, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  inline GLFWwindow *get_id()
  {
    return this->m_window_id;
  }

  inline GLFWmonitor *get_monitor_id()
  {
    return this->m_monitor_id;
  }

  inline const GLFWvidmode *get_video_mode()
  {
    return this->m_video_mode;
  }
};

#endif // __ENGINE_WINDOW__
