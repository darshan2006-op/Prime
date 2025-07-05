#include "OpenGLBuffers.h"
#include <glad/glad.h>
#include <Core/Log.h>

namespace prm {

	static GLenum getOpenglEnum(BufferType type) {
		switch (type)
		{
		case prm::BufferType::ArrayBuffer:
			return GL_ARRAY_BUFFER;
			break;
		case prm::BufferType::ElementBuffer:
			return GL_ELEMENT_ARRAY_BUFFER;
			break;
		default:
			PRM_CORE_ERROR("Unsupported Buffer type {} found", int(type));
			return 0;
			break;
		}
	}

	OpenGLBuffers::OpenGLBuffers(const Ref<Context>& context, BufferType type): Buffer(context, type), m_nativeId(0)
	{
	}
	void OpenGLBuffers::init()
	{
		if (m_nativeId == 0) glGenBuffers(1, &m_nativeId);
	}
	void OpenGLBuffers::allocateSize(size_t size)
	{
		if (m_nativeId != 0 && size != 0) {
			bind();
			glBufferData(getOpenglEnum(m_type), size, nullptr, GL_DYNAMIC_DRAW);
		}
	}
	void OpenGLBuffers::addData(void* data, size_t size, size_t offset)
	{
		if (m_nativeId != 0 && size != 0 && offset >= 0) {
			bind();
			void* ptr = glMapBufferRange(getOpenglEnum(m_type), offset, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
			if (ptr) {
				memcpy(ptr, data, size);
				glUnmapBuffer(getOpenglEnum(m_type));
			}
			else {
				PRM_CORE_ERROR("Unable to update data in buffer");
			}
		}
	}

	void OpenGLBuffers::bind()
	{
		if (m_nativeId != 0) glBindBuffer(getOpenglEnum(m_type), m_nativeId);
	}
	void OpenGLBuffers::destroy()
	{
		if (m_nativeId != 0) glDeleteBuffers(1, &m_nativeId);
	}
	OpenGLBuffers::~OpenGLBuffers()
	{
		destroy();
	}
}
