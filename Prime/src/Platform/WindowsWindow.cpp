#include "Platform/WindowsWindow.h"
#include "GLFW/glfw3.h"
#include "Core/Log.h"
#include "Events/ApplicationEvents.h"

namespace prm {
    bool WindowsWindow::s_glfwInitFlag = false;
    WindowsWindow::WindowsWindow(WindowOptions& options): m_navtiveWindow(nullptr), m_options(options), m_hasDestroyed(false)
    {
    }
    void WindowsWindow::init()
    {
        if (!s_glfwInitFlag)
            if (!glfwInit())
                PRM_CORE_CRITICAL("Unable to Initialize GLFW");


        this->m_navtiveWindow = glfwCreateWindow(m_options.width, m_options.height, m_options.windowTitle.c_str(), nullptr, nullptr);
        if (this->m_navtiveWindow == nullptr)
            PRM_CORE_ERROR("Unable to create Window");

        glfwSetWindowUserPointer(m_navtiveWindow, &m_options);

        glfwSetWindowCloseCallback(m_navtiveWindow, [](GLFWwindow* window) {
            WindowOptions* options = static_cast<WindowOptions*>(glfwGetWindowUserPointer(window));
            Event& e = WindowCloseEvent();
            options->handler(e);
        });
    }
    void WindowsWindow::update()
    {
        glfwSwapBuffers(this->m_navtiveWindow);
        glfwPollEvents();
    }
    void WindowsWindow::destroy()
    {
        glfwDestroyWindow(this->m_navtiveWindow);
        glfwTerminate();
        this->m_hasDestroyed = true;
    }
    bool WindowsWindow::hasClosed()
    {
        return glfwWindowShouldClose(this->m_navtiveWindow);
    }
    WindowsWindow::~WindowsWindow()
    {
        if(!this->m_hasDestroyed)
            destroy();
    }
}