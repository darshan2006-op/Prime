#include <iostream>
#include <math.h>
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
		m_window1Swapchain = prm::SwapChain::Create(m_window1);
		m_window1Swapchain->init();
		m_t = 0;
		m_angle = 330.0 * (3.14/180);
		m_radius = 1;
	}
	virtual void onUpdate() {

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cos(m_radius * m_angle), m_radius * sin(m_angle), 0.0f);
		glVertex3f(cos(m_radius * m_angle - (2 * 3.14 / 3)), m_radius * sin(m_angle - (2 * 3.14 / 3)), 0.0f);
		glVertex3f(cos(m_radius * m_angle - (4 * 3.14 / 3)), m_radius * sin(m_angle - (4 * 3.14 / 3)), 0.0f);
		glEnd();

		if (m_t % 120 == 0) {
			m_t = 0;
			m_angle += 3.14 / 18;
		}

		m_t++;
		m_window1Swapchain->swap();
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
	prm::Ref<prm::SwapChain> m_window1Swapchain;
	float m_angle;
	float m_radius;
	int m_t;
};

prm::Ref<prm::Application> prm::getClientApplication() {
	return prm::createRef<MyApp>();
}