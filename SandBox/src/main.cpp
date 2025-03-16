#include <iostream>
#include "prime.h"

class MyApp : public prm::Application {
public:
	MyApp() = default;
	virtual void onInit() {
		PRM_INFO("Application Init");
	}
	virtual void onUpdate() {
		PRM_INFO("Application Updated");
	}
	virtual void onDestroyed() {
		PRM_INFO("Application Destroyed");
	}
	virtual bool isRunning() {
		static int i = 0;
		return i++ < 10 ? true : false;
	}
};

prm::Ref<prm::Application> prm::getClientApplication() {
	return prm::createRef<MyApp>();
}