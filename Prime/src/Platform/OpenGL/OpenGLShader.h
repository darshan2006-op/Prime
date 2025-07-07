#pragma once
#include <Renderer/Shader.h>

namespace prm {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const Ref<Context>& context, ShaderType type);
		virtual void init() override;
		virtual void compileWithSource(const std::string& src) override;
		virtual uint32_t getId() { return m_nativeId; }
		virtual void destroy() override;
		virtual ~OpenGLShader();
	protected:
		uint32_t m_nativeId;
	};
}
