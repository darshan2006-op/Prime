#pragma once
#include "Core/Core.h"
#include "Core/Window.h"

namespace prm {
	class SwapChain {
	public:
		static Ref<SwapChain> Create(const Ref<Window>& window);
		virtual void init() = 0;
		virtual void swap() = 0;
		virtual ~SwapChain() = default;
	protected:
		SwapChain()=default;
	};
}