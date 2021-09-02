#ifndef __ENGINE_WINDOW__
#define __ENGINE_WINDOW__

#include "andromeda.hpp"

#include "glad/glad.h"
#include "../../engine/libs/libs.hpp"

#include "GLFW/glfw3.h"
#include "log/log.hpp"

struct Andromeda::Types::WindowConfog
{
	char *title;
	uint32_t width, height;
};

class Andromeda::Window
{

private:
	GLFWwindow *m_WindowID;
	GLFWmonitor *m_MonitorID;
	const GLFWvidmode *m_VideoMode;
	Andromeda::Types::WindowConfog m_WindowInfo;

public:
	Window(const Andromeda::Types::WindowConfog &conf)
	{

		Andromeda::Log::SetPrefix("Window");

		{
			int status = (int)glfwInit() == GLFW_TRUE;
			ASSERT(status, "Error while initializing GLFW", NULL);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);

		m_MonitorID = glfwGetPrimaryMonitor();
		m_VideoMode = glfwGetVideoMode(m_MonitorID);
		m_WindowID = glfwCreateWindow(conf.width, conf.height, static_cast<const char *>(conf.title), nullptr, nullptr);

		glfwMakeContextCurrent(m_WindowID);
		glfwSwapInterval(1);

		{
			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			ASSERT(status, "Failed to initialize OpenGL loader", NULL);
		}

		m_WindowInfo = conf;
		Andromeda::Log::Print("glfw window has been initialzed");
	}

	static Andromeda::Types::WindowConfog GetWindowInfo()
	{
		return get_window_info_impl();
	}

	static GLFWwindow *const GetWindowContext()
	{
		return Get().GetId();
	}

	static void SetWindowInfo(uint32_t width, uint32_t height)
	{
		Get().set_window_info_impl(width, height);
	}

	static GLFWkeyfun KeyHandler(GLFWwindow *window, GLFWkeyfun callback)
	{
		return glfwSetKeyCallback(window, callback);
	}

	static GLFWframebuffersizefun FrameBufferSetSizeHandler(GLFWwindow *window, GLFWframebuffersizefun callback)
	{
		return glfwSetFramebufferSizeCallback(window, callback);
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

	Window() = default;

private:
	static Andromeda::Types::WindowConfog get_window_info_impl()
	{
		return Get().m_WindowInfo;
	}

	void set_window_info_impl(uint32_t width, uint32_t height)
	{
		m_WindowInfo.width = width;
		m_WindowInfo.height = height;
	}

	static Andromeda::Window &Get()
	{
		static Andromeda::Window s_Instance;
		return s_Instance;
	}
};

#endif // __ENGINE_WINDOW__
