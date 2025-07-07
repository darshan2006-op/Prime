#include "Material.h"
#include "Shader.h"

namespace prm {
	uint32_t Material::materialCount = 0;

	Ref<Material> Material::create()
	{
		return createRef<Material>();
	}
	void Material::setShader(const Ref<Shader>& shader)
	{
		switch (shader->getType())
		{
		case ShaderType::VertexShader:
			m_vertexShader = shader;
			break;
		case ShaderType::FragmentShader:
			m_fragmentShader = shader;
			break;
		default:
			break;
		}
	}
	const Ref<Shader>& Material::getShader(ShaderType type)
	{
		switch (type)
		{
		case ShaderType::VertexShader:
			return m_vertexShader;
			break;
		case ShaderType::FragmentShader:
			return m_fragmentShader;
			break;
		default:
			break;
		}
	}
	Material::Material() : m_materialId(Material::materialCount), m_inputDescription({}), m_uniformData({})
	{
		Material::materialCount++;
	}
}
