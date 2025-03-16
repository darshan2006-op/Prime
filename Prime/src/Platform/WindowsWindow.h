#include "Core/Window.h"
struct GLFWwindow;

namespace prm {
	class WindowsWindow: public Window {
	public:
		WindowsWindow(WindowOptions& options);
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;
		virtual bool hasClosed() override;
		virtual ~WindowsWindow();
	private:
		GLFWwindow* m_navtiveWindow;
		WindowOptions m_options;
		static bool s_glfwInitFlag ;
		bool m_hasDestroyed;
	};
}