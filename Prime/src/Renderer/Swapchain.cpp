#include "Renderer/Renderer.h"
#include "Core/Window.h"
#include "Swapchain.h"
#include "Platform/OpenGL/OpenGLSwapchain.h"

namespace prm {
	Ref<SwapChain> prm::SwapChain::Create(const Ref<Window>& window)
	{
		switch (window->getOptions().graphicsOptions.api)
		{
		case RenderingApi::Opengl:
			return createRef<OpenGLSwapchain>(window);
			break;
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
	}
}