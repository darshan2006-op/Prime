#pragma once
#include "Core/Core.h"
#include "Core/Window.h"

namespace prm {
	struct ContextOptions {
		RenderingApi api = RenderingApi::Opengl;
		bool vsync = true;
	};

	class Context
	{
	public:
		static Ref<Context> create(Ref<Window>& window, ContextOptions options);
		virtual void init() = 0;
		virtual void createSwapChain() = 0;
		virtual void presentSwapChain() = 0;
		virtual const Ref<Window>& getWindow() { return m_window; }
		virtual const ContextOptions& getOptions() { return m_options; }
		virtual ~Context() = default;
	protected:
		Ref<Window>& m_window;
		ContextOptions m_options;
		Context(Ref<Window>& window, ContextOptions options): m_window(window), m_options(options) {};

	};
}