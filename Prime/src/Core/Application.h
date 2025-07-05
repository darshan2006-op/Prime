#pragma once
#include "Core/Core.h"

namespace prm {
	class Application;
	extern Ref<Application> getClientApplication();
	class Application {
	public:
		virtual void onInit() = 0;
		virtual void onUpdate(float dt) = 0;
		virtual void onDestroyed() = 0;
		virtual bool isRunning() = 0;
		virtual ~Application() = default;
	protected:
		Application() = default;
	};
}