#include "Buffers.h"
#include <Core/Core.h>
#include "Context.h"
#include <Platform/OpenGL/OpenGLBuffers.h>

namespace prm {
	Ref<Buffer> Buffer::create(const Ref<Context>& context, BufferType type)
	{
		switch (context->getOptions().api)
		{
		case RenderingApi::Opengl:
			return createRef<OpenGLBuffers>(context, type);
			break;
		case RenderingApi::Vulkan:
			return nullptr;
			break;
		default:
			return nullptr;
			break;
		}
	}
}
