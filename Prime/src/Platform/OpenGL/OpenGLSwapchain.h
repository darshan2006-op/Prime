#pragma once
#include "Renderer/Swapchain.h"

namespace prm {
	class OpenGLSwapchain : public SwapChain {
	public:
		OpenGLSwapchain(const Ref<Window>& window);
		virtual void init() override;
		virtual void swap() override;
	protected:
		Ref<Window> m_window;
	};
}