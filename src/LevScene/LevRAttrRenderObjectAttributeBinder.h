#pragma once
#include "LevSceneRenderAttribute.h"
#include <map>
#include "LSPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		typedef unsigned ATTRIBUTE_HANDLE;

		enum RenderObjectAttributeType
		{
			EROAT_FLOAT,
			EROAT_UINT
		};

		class LEV_SCENE_API LevRenderObjectAttribute
		{
		public:
			LevRenderObjectAttribute(RenderObjectAttributeType type, size_t byte_size_per_element, LSPtr<RAIIBufferData> data);
			const RAIIBufferData& GetData() const;
			size_t GetByteSizePerElement() const;
			size_t GetElementCount() const;
			RenderObjectAttributeType GetType() const;

		private:
			RenderObjectAttributeType m_type;
			size_t m_byte_size_per_element;
			LSPtr<RAIIBufferData> m_data;
		};

		enum RenderObjectPrimitiveType
		{
			EROPT_POINTS,
			EROPT_LINES,
			EROPT_TRIANGLES,
		};

		class LEV_SCENE_API LevRAttrRenderObjectAttributeBinder : public LevSceneRenderAttribute
		{
		public: 
			LevRAttrRenderObjectAttributeBinder(size_t element_count);

			bool BindAttribute(ATTRIBUTE_HANDLE handle,  LSPtr<LevRenderObjectAttribute> attribute);
			const std::map<ATTRIBUTE_HANDLE, LSPtr<LevRenderObjectAttribute>>& GetAttributes() const;

			void SetIndexAttribute(LSPtr<LevRenderObjectAttribute> index_attribute);

			bool HasIndexAttribute() const;
			const LevRenderObjectAttribute& GetIndexAttribute() const;

			size_t GetElementCount() const;
			size_t GetVertexCount() const;

			void SetPrimitiveType(RenderObjectPrimitiveType type);
			RenderObjectPrimitiveType GetPrimitiveType() const;

		private:
			size_t m_element_count;
			RenderObjectPrimitiveType m_primitive_type;
			std::map<ATTRIBUTE_HANDLE, LSPtr<LevRenderObjectAttribute>> m_bind_attributes;
			LSPtr<LevRenderObjectAttribute> m_index_attribute;
		};
	}
}