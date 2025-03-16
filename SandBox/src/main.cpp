#include <iostream>
#include "prime.h"

class MyApp : public prm::Application {
public:
	MyApp() = default;
	virtual void onInit() {
		std::cout << "application init" << std::endl;
	}
	virtual void onUpdate() {
		std::cout << "application update" << std::endl;
	}
	virtual void onDestroyed() {
		std::cout << "application destroy" << std::endl;
	}
	virtual bool isRunning() {
		static int i = 0;
		return i++ < 10 ? true : false;
	}
};

prm::Ref<prm::Application> prm::getClientApplication() {
	return prm::createRef<MyApp>();
}