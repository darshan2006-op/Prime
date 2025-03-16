#pragma once
#include <string>
#include "Core/Core.h"
#include "Events/Events.h"

namespace prm {

	struct WindowOptions{
		uint16_t width, height;
		std::string windowTitle;
		std::function<void(Event&)> handler;
	};

	class Window {
	public:
		static Ref<Window> build(WindowOptions& options);

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void destroy() = 0;
		virtual bool hasClosed() = 0;

		virtual ~Window() = default;
	protected:
		Window() = default;
	};
}