#include <iostream>
#include "prime.h"
#include "glad/glad.h"


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
		options.graphicsOptions.api = prm::RenderingApi::Opengl;
		m_window1 = prm::Window::build(options);
		m_window1->init();
		m_window1Context = prm::Context::create(m_window1);
		m_window1Context->init();
	}
	virtual void onUpdate() {
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5, 0.0f);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f( 0.5f, -0.5, 0.0f);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f( 0.0f, 0.5, 0.0f);
		}
		glEnd();
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
	prm::Ref<prm::Context> m_window1Context;

};

prm::Ref<prm::Application> prm::getClientApplication() {
	return prm::createRef<MyApp>();
}