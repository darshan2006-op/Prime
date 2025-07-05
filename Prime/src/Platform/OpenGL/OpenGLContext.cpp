#include "OpenGLContext.h"

#include "Core/PlatformDetection.h"
#include "Core/Core.h"
#include "Core/Log.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace prm {
	OpenGLContext::OpenGLContext(Ref<Window>& window, ContextOptions options): Context(window, options)
	{

	}
	void OpenGLContext::init()
	{
#ifdef PRM_PLATFORM_WINDOWS
		GLFWwindow* window = static_cast<GLFWwindow*>(m_window->getNativeWindowData().data);
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			PRM_CORE_ERROR("Unable to initialize glad for the given window");
		}
		if (m_options.vsync) {
			glfwSwapInterval(1);
		}
#endif
	}
	void OpenGLContext::createSwapChain()
	{
	}
	void OpenGLContext::presentSwapChain()
	{
		glfwSwapBuffers((GLFWwindow*)m_window->getNativeWindowData().data);
	}
	void OpenGLContext::clearScreen(ClearParameter param)
	{
		switch (param)
		{
		case prm::ClearParameter::ColorBuffer:
			glClear(GL_COLOR_BUFFER_BIT);
			break;
		case prm::ClearParameter::DepthBuffer:
			glClear(GL_DEPTH_BUFFER_BIT);
			break;
		case prm::ClearParameter::ColorAndDepthBuffer:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			break;
		default:
			break;
		}
	}
	void OpenGLContext::setClearColor(Color color)
	{
		float red = color.red / 255.0f;
		float green = color.green / 255.0f;
		float blue = color.blue / 255.0f;
		float alpha = color.alpha / 255.0f;
		glClearColor(red, green, blue, alpha);
	}
}