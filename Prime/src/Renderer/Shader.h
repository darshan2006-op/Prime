#pragma once
#include <Core/Core.h>
#include <string>
#include "Context.h"

namespace prm {
	enum class ShaderType {
		VertexShader,
		FragmentShader,
	};

	class Shader {
	public:
		static Ref<Shader> create(const Ref<Context>& context, ShaderType type);
		virtual void init() = 0;
		virtual void compileWithSource(const std::string& src) = 0;
		virtual const Ref<Context>& getContext() { return m_context; }
		virtual ShaderType getType() { return m_type; }
		virtual void destroy() = 0;
		virtual ~Shader() = default;
	protected:
		const Ref<Context> m_context;
		ShaderType m_type;
		Shader(const Ref<Context>& context, ShaderType type): m_context(context), m_type(type) {}
	};

}