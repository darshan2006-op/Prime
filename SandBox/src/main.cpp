#include <iostream>
#include "prime.h"

using namespace std::placeholders;

class MyApp : public prm::Application {
public:
	MyApp() = default;
	virtual void onInit() {
		PRM_INFO("Application Init");
		prm::WindowOptions options;
		options.width = 800;
		options.height = 500;
		options.windowTitle = "Engine Window";
		options.handler = std::bind(&MyApp::onEvent, this, _1);
		m_window1 = prm::Window::build(options);
		m_window1->init();
	}
	virtual void onUpdate() {
		m_window1->update();
	}
	virtual void onDestroyed() {
		PRM_INFO("Application Destroyed");
		m_window1->destroy();
	}
	virtual bool onEvent(const prm::Ref<prm::Event>& e) {
		return true;
	}
	virtual bool isRunning() {

		return !m_window1->hasClosed();
	}
	prm::Ref<prm::Window> m_window1;

};

prm::Ref<prm::Application> prm::getClientApplication() {
	return prm::createRef<MyApp>();
}