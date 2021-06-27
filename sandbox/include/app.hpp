#ifndef __SANDBOX_APP__
#define __SANDBOX_APP__

#include "andromeda.hpp"
#include "window/window.hpp"
#include "editor/editor.hpp"

#include "libs/opengl/frame_buffer.hpp"

#include "glm/vec3.hpp"
#include "game_object.hpp"

using namespace L::Graphics;
using namespace Andromeda::Types;

struct Sandbox
{
public:
	int m_Width, m_Height;
	double m_DeltaTime;
	double m_ElapsedTime = Andromeda::Window::TimeNow();
	OpenGL::FrameBuffer *m_FrameBuffer;

	Sandbox()
	{
		// Configure Window
		WindowConfog conf{"Andromeda", 1920, 1080};

		// Create new Window
		m_Window = new Andromeda::Window(conf);

		// Attach Window Key handler
		Andromeda::Window::KeyHandler(GetWidnowId(), Sandbox::KeyHandler);

#if defined(ANDROMEDA_EDITOR)
		// Attach FrameBuffer handler
		Andromeda::Window::FrameBufferSetSizeHandler(GetWidnowId(), Sandbox::FrameBufferSizeHandler);
		m_FrameBuffer = new OpenGL::FrameBuffer(m_Window->GetVideoMode()->width, m_Window->GetVideoMode()->height);
#endif
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

	double GetScaledElapsedTime(float scaler) const
	{
		return m_ElapsedTime * scaler;
	}

	void Resize()
	{
		glfwGetWindowSize(GetWidnowId(), &m_Width, &m_Height);
		m_Window->SetWindowInfo(m_Width, m_Height);
	}

	static void Draw(int width, int height);

	static void BaseRenderer(int width, int height)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float aspect = (float)width / (float)height;
		glOrtho(-aspect, aspect, -1, 1, 0.1, -1000.f);
	}

	/**
	 * WINDOW Key Input Handler
	 */
	static void KeyHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}

	/**
	 * Update viewport on Framebuffer size change
	 */
	static void FrameBufferSizeHandler(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

private:
	Andromeda::Window *m_Window;
};

#endif // __SANDBOX_APP__
