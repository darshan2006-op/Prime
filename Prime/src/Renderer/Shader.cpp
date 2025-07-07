#include "Shader.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace prm {
	Ref<Shader> Shader::create(const Ref<Context>& context, ShaderType type)
	{
		switch (context->getOptions().api)
		{
		case RenderingApi::Opengl:
			return createRef<OpenGLShader>(context, type);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			break;
		}
	}
}