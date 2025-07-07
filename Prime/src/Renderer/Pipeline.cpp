#include "Pipeline.h"
#include "Shader.h"
#include "Context.h"
#include <Core/Core.h>
#include <Platform/OpenGL/OpenGLPipeline.h>

namespace prm {
	Ref<Pipeline> Pipeline::create(const Ref<Material>& material, const Ref<Context>& context) {
		switch (context->getOptions().api)
		{
		case RenderingApi::Opengl:
			return createRef<OpenGLPipeline>(material);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			break;
		}
	}
}