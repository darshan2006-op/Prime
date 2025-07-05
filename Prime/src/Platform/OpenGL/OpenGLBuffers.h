#pragma once
#include "Renderer/Buffers.h"
#include <Renderer/Context.h>
#include <Core/Core.h>

namespace prm {
	class OpenGLBuffers : public Buffer {
	public:
		OpenGLBuffers(const Ref<Context>& context, BufferType type);
		virtual void init() override;
		virtual void allocateSize(size_t size) override;
		virtual void addData(void* data, size_t size, size_t offset) override;
		virtual void bind() override;
		virtual void destroy() override;
		virtual ~OpenGLBuffers();
	private:
		uint32_t m_nativeId;
	};
}
