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

		prm::ContextOptions contextOptions;
		contextOptions.api = prm::RenderingApi::Opengl;
		contextOptions.vsync = true;
		
		m_window1 = prm::Window::build(options);
		m_window1->init();

		m_window1Context = prm::Context::create(m_window1, contextOptions);
		m_window1Context->init();
	
		m_window1Context->createSwapChain();
		m_window1Context->setClearColor({100,100,150,255});

		m_buffer = prm::Buffer::create(m_window1Context, prm::BufferType::ArrayBuffer);

		float vertex[] = {
			-0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
		};
		m_buffer->init();
		m_buffer->allocateSize(sizeof(vertex));
		m_buffer->addData(vertex, sizeof(vertex), 0);
		m_buffer->bind();
	}

	virtual void onUpdate(float dt) {
		m_window1Context->clearScreen(prm::ClearParameter::ColorBuffer);
		
		m_buffer->bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
		glDrawArrays(GL_TRIANGLES, 0, 3);


		m_window1Context->presentSwapChain();
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

	prm::Ref<prm::Buffer> m_buffer;
	prm::Ref<prm::Window> m_window1;
	prm::Ref<prm::Context> m_window1Context;
};

prm::Ref<prm::Application> prm::getClientApplication() {
	return prm::createRef<MyApp>();
}