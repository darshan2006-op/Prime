#include "Core/Window.h"
struct GLFWwindow;

namespace prm {
	struct WindowData {
		WindowOptions options;
		EventDispatcher dispatcher;
	};

	class WindowsWindow: public Window {
	public:
		WindowsWindow(WindowOptions& options);
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;
		virtual NativeWindowData getNativeWindowData();
		virtual bool hasClosed() override;
		virtual const WindowOptions& getOptions() override { return data.options; }
		virtual ~WindowsWindow();
	private:
		GLFWwindow* m_navtiveWindow;
		static bool s_glfwInitFlag ;
		bool m_hasDestroyed;
		WindowData data;
	};
}