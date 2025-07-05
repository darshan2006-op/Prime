#pragma once
#include "Renderer/Context.h"

namespace prm {
	class OpenGLContext : public Context {
	public:
		OpenGLContext(Ref<Window>& window, ContextOptions options);
		virtual void init() override;
		virtual void createSwapChain() override;
		virtual void presentSwapChain() override;
		virtual void clearScreen(ClearParameter param) override;
		virtual void setClearColor(Color color) override;
	protected:
	};
}