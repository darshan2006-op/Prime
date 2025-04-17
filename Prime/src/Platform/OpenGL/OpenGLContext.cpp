#include "OpenGLContext.h"

#include "Core/PlatformDetection.h"
#include "Core/Core.h"
#include "Core/Log.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace prm {
	OpenGLContext::OpenGLContext(Ref<Window>& window): m_window(window)
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
#endif
	}
}