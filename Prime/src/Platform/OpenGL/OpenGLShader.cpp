#include "OpenGLShader.h"
#include <glad/glad.h>
#include <vector>
#include <Core/Log.h>

namespace prm {
	GLenum getNativeType(ShaderType type) {
		switch (type)
		{
		case prm::ShaderType::VertexShader:
			return GL_VERTEX_SHADER;
			break;
		case prm::ShaderType::FragmentShader:
			return GL_FRAGMENT_SHADER;
			break;
		default:
			break;
		}
	}

	OpenGLShader::OpenGLShader(const Ref<Context>& context, ShaderType type): Shader(context, type), m_nativeId(0)
	{
	}

	void OpenGLShader::init()
	{
		if (m_nativeId == 0) {
			m_nativeId = glCreateShader(getNativeType(m_type));
		}
	}

	void OpenGLShader::compileWithSource(const std::string& src)
	{
		const char* data[] = {src.data()};
		const int length[] = { src.length() };
		
		glShaderSource(m_nativeId, 1, data, length);
		glCompileShader(m_nativeId);

		int success = GL_FALSE;
		glGetShaderiv(m_nativeId, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			char* shader_name = "";
			switch (m_type)
			{
			case prm::ShaderType::VertexShader:
				shader_name = "Vertex Shader";
				break;
			case prm::ShaderType::FragmentShader:
				shader_name = "Fragment Shader";
				break;
			default:
				break;
			}
			std::string msg = std::string();
			{
				std::vector<char> err_msg = std::vector<char>();
				GLsizei length = 0;
				glGetShaderInfoLog(m_nativeId, 0, &length, nullptr);
				err_msg.resize(length);
				glGetShaderInfoLog(m_nativeId, length, nullptr, err_msg.data());
				msg = std::string(err_msg.data());
			}
			PRM_ERROR("ERROR: While compile {} : \n {}", shader_name, msg);
		}
	}

	void OpenGLShader::destroy()
	{
		if (m_nativeId != 0) {
			glDeleteShader(m_nativeId);
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		destroy();
	}

}