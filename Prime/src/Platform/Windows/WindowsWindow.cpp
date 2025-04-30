#include "Platform/Windows/WindowsWindow.h"
#include "GLFW/glfw3.h"
#include "Core/Log.h"
#include "Events/ApplicationEvents.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvents.h"

namespace prm {
	bool WindowsWindow::s_glfwInitFlag = false;
	WindowsWindow::WindowsWindow(WindowOptions& options) : m_navtiveWindow(nullptr), m_hasDestroyed(false)
	{
		data.options = options;
	}
	void WindowsWindow::init()
	{
		if (!s_glfwInitFlag)
			if (!glfwInit())
				PRM_CORE_CRITICAL("Unable to Initialize GLFW");


		this->m_navtiveWindow = glfwCreateWindow(data.options.width, data.options.height, data.options.windowTitle.c_str(), nullptr, nullptr);
		if (this->m_navtiveWindow == nullptr)
			PRM_CORE_ERROR("Unable to create Window");

		glfwSetWindowUserPointer(m_navtiveWindow, &data);
		data.dispatcher.init(this->data.options.handler);


		glfwSetWindowCloseCallback(m_navtiveWindow, [](GLFWwindow* window) {
			WindowData* options = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			options->dispatcher.pushEvent(createRef<WindowCloseEvent>());
			});

		glfwSetWindowSizeCallback(m_navtiveWindow, [](GLFWwindow* window, int width, int height) {
			WindowData* options = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			options->dispatcher.pushEvent(createRef<WindowResizeEvent>(width, height));
			});

		glfwSetCursorPosCallback(m_navtiveWindow, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData* options = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			options->dispatcher.pushEvent(createRef<MouseMovedEvent>(xpos, ypos));
			});

		glfwSetKeyCallback(m_navtiveWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData* options = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS:
			{
				options->dispatcher.pushEvent(createRef<KeyPressedEvent>(key, 0));

				break;
			}
			case GLFW_RELEASE:
			{
				options->dispatcher.pushEvent(createRef<KeyReleasedEvent>(key));
				break;
			}
			case GLFW_REPEAT:
			{
				options->dispatcher.pushEvent(createRef<KeyPressedEvent>(key, 1));
				break;
			}
			}
			});

		glfwSetCharCallback(m_navtiveWindow, [](GLFWwindow* window, unsigned int codepoint) {
			WindowData* options = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			options->dispatcher.pushEvent(createRef<KeyTypedEvent>(codepoint));
			});

		glfwSetMouseButtonCallback(m_navtiveWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData* options = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					options->dispatcher.pushEvent(createRef<MouseButtonPressedEvent>(button));
					break;
				}
				case GLFW_RELEASE:
				{
					options->dispatcher.pushEvent(createRef<MouseButtonReleasedEvent>(button));
					break;
				}
				}
			});

		glfwSetScrollCallback(m_navtiveWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData* options = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				options->dispatcher.pushEvent(createRef<MouseScrolledEvent>(xOffset, yOffset));
			});

		
	}
	void WindowsWindow::update()
	{
		glfwPollEvents();
	}
	void WindowsWindow::destroy()
	{
		data.dispatcher.destroy();
		glfwDestroyWindow(this->m_navtiveWindow);
		glfwTerminate();
		this->m_hasDestroyed = true;
	}
	NativeWindowData WindowsWindow::getNativeWindowData()
	{
		NativeWindowData data;
		data.options = this->getOptions();
		data.data = m_navtiveWindow;
		return data;
	}
	bool WindowsWindow::hasClosed()
	{
		return glfwWindowShouldClose(this->m_navtiveWindow);
	}
	WindowsWindow::~WindowsWindow()
	{
		if (!this->m_hasDestroyed)
			destroy();
	}
}