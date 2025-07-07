#pragma once
#include <Core/Core.h>
#include "Material.h"

namespace prm {
	class Pipeline {
	public:
		static Ref<Pipeline> create(const Ref<Material>& material, const Ref<Context>& context);
		virtual void init() = 0;
		virtual void bind() = 0;
		virtual void destroy() = 0;

		friend class Context;

		virtual ~Pipeline() = default;
	protected:
		Ref<Material> m_material;
		Pipeline(const Ref<Material>& material) : m_material(material) {}

	};
}
