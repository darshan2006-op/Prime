#pragma once
#include "Renderer/Context.h"

namespace prm {
	class OpenGLContext : public Context {
	public:
		OpenGLContext(Ref<Window>& window);
		virtual void init() override;
	protected:
		Ref<Window> m_window;
	};
}