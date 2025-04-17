#include "Context.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace prm {
	Ref<Context> Context::create(Ref<Window>& window)
	{
		switch (window->getOptions().graphicsOptions.api)
		{
		case RenderingApi::Opengl:
			return createRef<OpenGLContext>(window);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
	}
}
