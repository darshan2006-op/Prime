#include "OpenGLPipeline.h"
#include "OpenGLShader.h"
#include <glad/glad.h>

namespace prm {
	OpenGLPipeline::OpenGLPipeline(const Ref<Material>& material): Pipeline(material), m_nativeShader(0)
	{

	}
	void OpenGLPipeline::init()
	{
		if (m_nativeShader == 0) {
			m_nativeShader = glCreateProgram();
			{
				Weak<Shader> fshader = m_material->getShader(ShaderType::FragmentShader);
				if (auto shader = fshader.lock()) {
					OpenGLShader* rawShader = (OpenGLShader*)shader.get();
					glAttachShader(m_nativeShader, rawShader->getId());
				}
			}
			{
				Weak<Shader> fshader = m_material->getShader(ShaderType::VertexShader);
				if (auto shader = fshader.lock()) {
					OpenGLShader* rawShader = (OpenGLShader*)shader.get();
					glAttachShader(m_nativeShader, rawShader->getId());
				}
			}
			glLinkProgram(m_nativeShader);
		}
	}
	void OpenGLPipeline::bind()
	{
		glUseProgram(m_nativeShader);

		for (auto& ud : m_material->getUniformData()) {
			int location = -1;
			if (m_locationCache.find(ud.name) != m_locationCache.end()) {
				location = m_locationCache.at(ud.name);
			}
			else {
				location = glGetUniformLocation(m_nativeShader, ud.name.c_str());
				m_locationCache.insert({ud.name, location});
			}
			

			switch (ud.format)
			{
			case DataFormat::Unit:
				glUniform1iv(location, 1, (GLint*)ud.data.data());
				break;
			case DataFormat::Vector2:
				glUniform2fv(location, 1, (GLfloat*)ud.data.data());
				break;
			case DataFormat::Vector3:
				glUniform3fv(location, 1, (GLfloat*)ud.data.data());
				break;
			case DataFormat::Mat3x3:
				glUniformMatrix3fv(location, 1, GL_FALSE, (GLfloat*)ud.data.data());
				break;
			case DataFormat::Mat4x4:
				glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)ud.data.data());
				break;
			default:
				break;
			}
		}
	}
	void OpenGLPipeline::destroy()
	{
		glDeleteProgram(m_nativeShader);
	}
	OpenGLPipeline::~OpenGLPipeline()
	{
		destroy();
	}
}
