#include "LevRAttrRenderObjectAttributeBinder.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRenderObjectAttribute::LevRenderObjectAttribute(RenderObjectAttributeType type, size_t byte_size_per_element, LSPtr<RAIIBufferData> data)
			: m_type(type)
			, m_byte_size_per_element(byte_size_per_element)
			, m_data(data)
		{
		}

		const RAIIBufferData & LevRenderObjectAttribute::GetData() const
		{
			return *m_data;
		}

		size_t LevRenderObjectAttribute::GetByteSizePerElement() const
		{
			return m_byte_size_per_element;
		}

		size_t LevRenderObjectAttribute::GetElementCount() const
		{
			return m_data->GetArrayDataByteSize() / GetByteSizePerElement();
		}

		RenderObjectAttributeType LevRenderObjectAttribute::GetType() const
		{
			return m_type;
		}

		LevRAttrRenderObjectAttributeBinder::LevRAttrRenderObjectAttributeBinder(size_t element_count)
			: LevSceneObjectAttribute(ELSOAT_RENDER)
			, m_index_attribute(nullptr)
			, m_element_count(element_count)
		{
			/*
				Default primitive type is triangle.
			*/
			SetPrimitiveType(EROPT_TRIANGLES);
		}

		bool LevRAttrRenderObjectAttributeBinder::BindAttribute(ATTRIBUTE_HANDLE handle, LSPtr<LevRenderObjectAttribute> attribute)
		{
			//EXIT_IF_FALSE(attribute->GetElementCount() >= m_element_count);
			m_bind_attributes[handle] = attribute;

			return true;
		}

		const std::map<ATTRIBUTE_HANDLE, LSPtr<LevRenderObjectAttribute>>& LevRAttrRenderObjectAttributeBinder::GetAttributes() const
		{
			return m_bind_attributes;
		}

		void LevRAttrRenderObjectAttributeBinder::SetIndexAttribute(LSPtr<LevRenderObjectAttribute> index_attribute)
		{
			m_index_attribute = index_attribute;
		}

		bool LevRAttrRenderObjectAttributeBinder::HasIndexAttribute() const
		{
			return m_index_attribute.Get();
		}

		const Leviathan::Scene::LevRenderObjectAttribute& LevRAttrRenderObjectAttributeBinder::GetIndexAttribute() const
		{
			LEV_ASSERT(HasIndexAttribute());
			return *m_index_attribute;
		}

		size_t LevRAttrRenderObjectAttributeBinder::GetElementCount() const
		{
			return m_element_count;
		}

		size_t LevRAttrRenderObjectAttributeBinder::GetVertexCount() const
		{
			if (m_index_attribute.Get())
			{
				return m_index_attribute->GetElementCount();
			}

			return m_element_count;
		}

		void LevRAttrRenderObjectAttributeBinder::SetPrimitiveType(RenderObjectPrimitiveType type)
		{
			m_primitive_type = type;
		}

		Leviathan::Scene::RenderObjectPrimitiveType LevRAttrRenderObjectAttributeBinder::GetPrimitiveType() const
		{
			return m_primitive_type;
		}

	}
}