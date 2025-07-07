#pragma once
#include <Renderer/Mesh.h>

namespace prm {
	class OpenGLMesh : public Mesh{
	public:
		OpenGLMesh(const Ref<Context>& context, const Ref<Material>& material);
		virtual void init() override;
		virtual void bind() override;
		virtual void destroy() override;
		virtual void addVertexBuffer(const Ref<Buffer>& vb) override;
		virtual void setIndexBuffer(const Ref<Buffer>& ib) override;
		virtual ~OpenGLMesh();
	protected:
		uint32_t m_nativeVao;
		uint32_t m_bufferCount;
	};
}