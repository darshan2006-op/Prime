#include "OpenGLMesh.h"
#include <glad/glad.h>

namespace prm {
	OpenGLMesh::OpenGLMesh(const Ref<Context>& context, const Ref<Material>& material) : Mesh(context, material), m_nativeVao(0), m_bufferCount(0)
	{
	}

	void OpenGLMesh::init()
	{
		if (m_nativeVao == 0) {
			glGenVertexArrays(1, &m_nativeVao);
		}
	}

	void OpenGLMesh::bind()
	{
		if (m_nativeVao != 0) {
			glBindVertexArray(m_nativeVao);
		}
	}

	void OpenGLMesh::destroy()
	{
		if (m_nativeVao != 0) {
			glDeleteVertexArrays(1, &m_nativeVao);
		}
	}

	size_t getFormatSize(DataFormat type) {
		switch (type)
		{
		case prm::DataFormat::Unit:
			return sizeof(float);
			break;
		case prm::DataFormat::Vector2:
			return sizeof(float) * 2;
			break;
		case prm::DataFormat::Vector3:
			return sizeof(float) * 3;
			break;
		case prm::DataFormat::Mat3x3:
			return sizeof(float) * 9;
			break;
		case prm::DataFormat::Mat4x4:
			return sizeof(float) * 16;
			break;
		default:
			break;
		}
	}

	uint32_t getFormatCount(DataFormat format) {
		switch (format)
		{
		case prm::DataFormat::Unit:
			return 1;
			break;
		case prm::DataFormat::Vector2:
			return 2;
			break;
		case prm::DataFormat::Vector3:
			return 3;
			break;
		case prm::DataFormat::Mat3x3:
			return 9;
			break;
		case prm::DataFormat::Mat4x4:
			return 16;
			break;
		default:
			break;
		}
	}

	void OpenGLMesh::addVertexBuffer(const Ref<Buffer>& vb)
	{
		bind();
		vb->bind();
		size_t stride = 0;
		for (auto& elem : m_material->getVertexInputDescriptor()) {
			if (elem.binding == m_bufferCount) {
				stride += getFormatSize(elem.format);
			}
		}
		size_t offset = 0;
		for (auto& elem : m_material->getVertexInputDescriptor()) {
			if (elem.binding == m_bufferCount) {
				glEnableVertexAttribArray(elem.location);
				glVertexAttribPointer(elem.location, getFormatCount(elem.format), GL_FLOAT, GL_FALSE, stride, (const void*)offset);
				offset += getFormatSize(elem.format);
			}
		}
		m_bufferCount++;
	}

	void OpenGLMesh::setIndexBuffer(const Ref<Buffer>& ib)
	{
		bind();
		ib->bind();
	}

	OpenGLMesh::~OpenGLMesh()
	{
		destroy();
	}

}