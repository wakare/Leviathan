#pragma once
#include "LevSceneRenderAttribute.h"
#include <map>
#include "LPtr.h"

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
			LevRenderObjectAttribute(RenderObjectAttributeType type, size_t byte_size_per_element, LPtr<RAIIBufferData> data);
			const RAIIBufferData& GetData() const;
			size_t GetByteSizePerElement() const;
			size_t GetElementCount() const;
			RenderObjectAttributeType GetType() const;

		private:
			RenderObjectAttributeType m_type;
			size_t m_byte_size_per_element;
			LPtr<RAIIBufferData> m_data;
		};

		class LEV_SCENE_API LevRAttrRenderObjectAttributeBinder : public LevSceneRenderAttribute
		{
		public: 
			LevRAttrRenderObjectAttributeBinder(size_t element_count);

			bool BindAttribute(ATTRIBUTE_HANDLE handle,  LPtr<LevRenderObjectAttribute> attribute);
			const std::map<ATTRIBUTE_HANDLE, LPtr<LevRenderObjectAttribute>>& GetAttributes() const;

			void SetIndexAttribute(LPtr<LevRenderObjectAttribute> index_attribute);

			bool HasIndexAttribute() const;
			const LevRenderObjectAttribute& GetIndexAttribute() const;

			size_t GetElementCount() const;
			size_t GetVertexCount() const;

		private:
			size_t m_element_count;
			std::map<ATTRIBUTE_HANDLE, LPtr<LevRenderObjectAttribute>> m_bind_attributes;
			LPtr<LevRenderObjectAttribute> m_index_attribute;
		};
	}
}