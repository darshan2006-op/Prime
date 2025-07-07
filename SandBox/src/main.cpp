#include <iostream>
#include <math.h>
#include <prime.h>

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


		float vertex[] = {
			-0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f,
			 0.0f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
		};
		m_buffer = prm::Buffer::create(m_window1Context, prm::BufferType::ArrayBuffer);
		m_buffer->init();
		m_buffer->allocateSize(sizeof(vertex));
		m_buffer->addData(vertex, sizeof(vertex), 0);
		m_buffer->bind();

		uint32_t indices[] = { 0, 1, 2 };
		m_index = prm::Buffer::create(m_window1Context, prm::BufferType::ElementBuffer);
		m_index->init();
		m_index->allocateSize(sizeof(uint32_t) * 3);
		m_index->addData(indices, sizeof(indices), 0);
		m_index->bind();

		std::string vertexSrc = R"(
			#version 430 core
			layout(location=0) in vec3 aPos;
			layout(location=1) in vec3 aColor;

			void main() {
				gl_Position = vec4(aPos, 1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 430 core
			layout(location=0) out vec4 oColor;
			
			uniform vec3 u_color;

			void main() {
				oColor = vec4(u_color, 1.0f);
			}
		)";

		m_vertexShader = prm::Shader::create(m_window1Context, prm::ShaderType::VertexShader);
		m_vertexShader->init();
		m_vertexShader->compileWithSource(vertexSrc);

		m_fragmentShader = prm::Shader::create(m_window1Context, prm::ShaderType::FragmentShader);
		m_fragmentShader->init();
		m_fragmentShader->compileWithSource(fragmentSrc);

		float rawdata[] = {1.0f, 0.0f, 0.5f};

		m_material1 = prm::Material::create();
		m_material1->addInputDescription(prm::DataFormat::Vector3, prm::DataType::Float32, 0);
		m_material1->addInputDescription(prm::DataFormat::Vector3, prm::DataType::Float32, 1);
		m_material1->addUniformData("u_color", prm::DataFormat::Vector3, prm::DataType::Float32, rawdata);
		m_material1->setShader(m_fragmentShader);
		m_material1->setShader(m_vertexShader);
		
		m_pipeLine = prm::Pipeline::create(m_material1, m_window1Context);
		m_pipeLine->init();

		m_mesh1 = prm::Mesh::create(m_window1Context, m_material1);
		m_mesh1->init();
		m_mesh1->addVertexBuffer(m_buffer);
		m_mesh1->setIndexBuffer(m_index);
	}

	virtual void onUpdate(float dt) {
		m_window1Context->clearScreen(prm::ClearParameter::ColorBuffer);
		
		m_pipeLine->bind();
		m_mesh1->bind();

		m_window1Context->drawElements(3);

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
	prm::Ref<prm::Buffer> m_index;

	prm::Ref<prm::Window> m_window1;
	prm::Ref<prm::Context> m_window1Context;

	prm::Ref<prm::Shader> m_vertexShader;
	prm::Ref<prm::Shader> m_fragmentShader;

	prm::Ref<prm::Pipeline> m_pipeLine;
	prm::Ref<prm::Material> m_material1;
	prm::Ref<prm::Mesh> m_mesh1;
};

prm::Ref<prm::Application> prm::getClientApplication() {
	return prm::createRef<MyApp>();
}