#pragma once

#include <Renderer/Pipeline.h>
#include <unordered_map>

namespace prm {
	class OpenGLPipeline: public Pipeline {
	public:
		OpenGLPipeline(const Ref<Material>& material);
		virtual void init() override;
		virtual void bind() override;
		virtual void destroy() override;
		virtual ~OpenGLPipeline();
	protected:
		std::unordered_map<std::string, int> m_locationCache;
		uint32_t m_nativeShader;
	};
}