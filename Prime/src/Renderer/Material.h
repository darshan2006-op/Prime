#pragma once
#include <vector>
#include <Core/Core.h>
#include <string>

namespace prm {
	class Shader;
	class Context;
	enum class ShaderType;

	enum class DataFormat {
		Unit ,
		Vector2,
		Vector3,

		Mat3x3,
		Mat4x4,
	};

	enum class DataType {
		Float32,
		Float16,

		Int32  ,
	};

	struct VertexInputDescriptor {
		DataFormat format;
		DataType type;
		int binding = 0;
		int location;
	};

	struct UniformData {
		std::string name;
		DataFormat format;
		DataType type;
		std::vector<uint8_t> data;
	};

	class Material {
	public:
		static Ref<Material> create();
		Material();

		template<typename T>
		void addUniformData(const std::string& name, DataFormat format, DataType type, const T& data) {
			UniformData udata;
			udata.name = name;
			udata.format = format;
			udata.type = type;
			udata.data = std::vector<uint8_t>(sizeof(data));
			memcpy(udata.data.data(), &data, sizeof(data));
			m_uniformData.push_back(udata);
		}
		void addInputDescription(DataFormat format, DataType type, int location, int binding = 0) {
			m_inputDescription.push_back({ format, type, binding, location });
		}
		void setShader(const Ref<Shader>& shader);
		const Ref<Shader>& getShader(ShaderType type);
		const std::vector<UniformData>& getUniformData() { return m_uniformData; }
		const std::vector<VertexInputDescriptor>& getVertexInputDescriptor() { return m_inputDescription; }

		~Material() = default;
	protected:
		
		static uint32_t materialCount ;

		uint32_t m_materialId;
		std::vector<VertexInputDescriptor> m_inputDescription;
		std::vector<UniformData> m_uniformData;
		Ref<Shader> m_vertexShader;
		Ref<Shader> m_fragmentShader;
		
		
	};
}