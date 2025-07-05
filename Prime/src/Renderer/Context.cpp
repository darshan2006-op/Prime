#include "Context.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace prm {
	Ref<Context> Context::create(Ref<Window>& window, ContextOptions options)
	{
		switch (options.api)
		{
		case RenderingApi::Opengl:
			return createRef<OpenGLContext>(window, options);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
	}
}
