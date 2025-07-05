#pragma once
#include "Core/Core.h"
#include "Core/Window.h"

namespace prm {
	struct ContextOptions {
		RenderingApi api = RenderingApi::Opengl;
		bool vsync = true;
	};

	enum class ClearParameter: uint8_t {
		ColorBuffer,
		DepthBuffer,
		ColorAndDepthBuffer,
	};

	struct Color {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
	};

	class Context
	{
	public:
		static Ref<Context> create(Ref<Window>& window, ContextOptions options);
		virtual void init() = 0;
		virtual void createSwapChain() = 0;
		virtual void presentSwapChain() = 0;
		virtual void clearScreen(ClearParameter param) = 0;
		virtual void setClearColor(Color color) = 0;
		virtual const Ref<Window>& getWindow() { return m_window; }
		virtual const ContextOptions& getOptions() { return m_options; }
		virtual ~Context() = default;
	protected:
		Ref<Window>& m_window;
		ContextOptions m_options;
		Context(Ref<Window>& window, ContextOptions options): m_window(window), m_options(options) {};

	};
}
