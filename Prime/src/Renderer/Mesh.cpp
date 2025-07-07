#include "Mesh.h"
#include "Context.h"
#include <Platform/OpenGL/OpenGLMesh.h>

namespace prm {
	Ref<Mesh> Mesh::create(const Ref<Context>& context, const Ref<Material>& material)
	{
		switch (context->getOptions().api)
		{
		case RenderingApi::Opengl:
			return createRef<OpenGLMesh>(context, material);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			break;
		}
	}
}
