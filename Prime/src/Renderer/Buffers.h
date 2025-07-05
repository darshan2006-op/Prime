#pragma once
#include "Core/Core.h"
#include "Context.h"
#include <cstdint>

namespace prm {
	enum class BufferType: uint8_t {
		ArrayBuffer,
		ElementBuffer
	};

	class Buffer {
	public:
		static Ref<Buffer> create(const Ref<Context>& context, BufferType type);
		virtual void init() = 0;
		virtual void allocateSize(size_t size) = 0;
		virtual void addData(void* data, size_t size, size_t offset) = 0;
		virtual void bind() = 0;
		virtual void destroy() = 0;
		virtual ~Buffer() = default;
	protected:
		const Ref<Context>& m_context;
		BufferType m_type;
		Buffer(const Ref<Context>& context, BufferType type): m_context(context), m_type(type) {}
	};
}