#include "OpenGLSwapchain.h"
#include "GLFW/glfw3.h"

namespace prm {
	OpenGLSwapchain::OpenGLSwapchain(const Ref<Window>& window): m_window(window)
	{
	}
	void OpenGLSwapchain::init()
	{

	}
	void OpenGLSwapchain::swap()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_window->getNativeWindowData().data);
		glfwSwapBuffers(window);
	}
}