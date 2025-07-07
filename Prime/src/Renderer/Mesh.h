#pragma once
#include "Material.h"
#include "Buffers.h"
#include <Core/Core.h>

namespace prm {
	class Mesh {
	public:
		static Ref<Mesh> create(const Ref<Context>& context, const Ref<Material>& material);
		virtual void init() = 0;
		virtual void bind() = 0;
		virtual void destroy() = 0;
		virtual void addVertexBuffer(const Ref<Buffer>& vb) = 0;
		virtual void setIndexBuffer(const Ref<Buffer>& ib) = 0;
		virtual ~Mesh() = default;
	protected:
		Ref<Context> m_context;
		Ref<Material> m_material;
		Mesh(const Ref<Context>& context, const Ref<Material>& material) : m_context(context), m_material(material) {}
	};
}
