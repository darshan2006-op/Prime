#include "Window.h"
#include "Log.h"
#include "PlatformDetection.h"
#include "Platform/Windows/WindowsWindow.h"

namespace prm {
    Ref<Window> prm::Window::build(WindowOptions& options)
    {
#ifdef PRM_PLATFORM_WINDOWS
        return createRef<WindowsWindow>(options);
#else
        PRM_CORE_CRITICAL("This platform is not supported");
        return nullptr;
#endif // PRM_PLATFORM_WINDOWS
    }
}