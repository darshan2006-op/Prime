#pragma once
#include "Core/Core.h"
#include "Core/Window.h"

namespace prm {
	class Context
	{
	public:
		static Ref<Context> create(Ref<Window>& window);
		virtual void init() = 0;
		virtual ~Context() = default;
	protected:
		Context() = default;
	};
}