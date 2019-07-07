#include "OpenGLObject2.h"
#include "OpenGLUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLObject2::OpenGLObject2(unsigned id, GLenum primitive_type, const Scene::LevRAttrRenderObjectAttributeBinder& attribute_binder)
			: m_attribute_binder(attribute_binder)
			, m_inited(false)
			, m_primitive_type(primitive_type)
			, m_id(id)
		{

		}

		/*
			A Empty object
		*/
		OpenGLObject2::OpenGLObject2(unsigned id)
			: m_attribute_binder(Scene::LevRAttrRenderObjectAttributeBinder(0))
			, m_inited(false)
			, m_primitive_type(GL_INVALID_ENUM)
			, m_id(id)
		{

		}

		void OpenGLObject2::AddUniform(LPtr<OpenGLUniform> uniform)
		{
			m_uniforms.push_back(uniform);
		}

		bool OpenGLObject2::Render(GLuint shaderProgram)
		{
			if (!m_inited)
			{
				m_inited = _init();
				LEV_ASSERT(m_inited);
			}

			for (auto& fn : m_preprocess_fns)
			{
				fn();
			}

			EXIT_IF_FALSE(ApplyUniform(shaderProgram));

			EXIT_IF_FALSE(m_VAO);
			glBindVertexArray(m_VAO);

			m_attribute_binder.HasIndexAttribute() ? (glDrawElements(m_primitive_type, m_attribute_binder.GetVertexCount(), GL_UNSIGNED_INT, 0)) : (glDrawArrays(m_primitive_type, 0, m_attribute_binder.GetVertexCount()));
			glBindVertexArray(0);

			for (auto& fn : m_postprocess_fns)
			{
				fn();
			}

			return true;
		}

		bool OpenGLObject2::ApplyUniform(GLuint shaderProgram)
		{
			for (auto& pUniform : m_uniforms)
			{
				EXIT_IF_FALSE(pUniform->Apply(shaderProgram));
			}

			return true;
		}

		unsigned OpenGLObject2::GetID() const
		{
			return m_id;
		}

		void OpenGLObject2::AddPreProcess(std::function<void()> fn)
		{
			m_preprocess_fns.push_back(fn);
		}

		void OpenGLObject2::AddPostProcess(std::function<void()> fn)
		{
			m_postprocess_fns.push_back(fn);
		}

		bool OpenGLObject2::_init()
		{
			// Merge attribute data to temp array
			size_t attribute_size = m_attribute_binder.GetAttributes().size();
			EXIT_IF_FALSE(attribute_size > 0)
			
			size_t total_byte_size = 0;
			for (const auto& attribute : m_attribute_binder.GetAttributes())
			{
				total_byte_size += attribute.second->GetData().GetArrayDataByteSize();
			}

			LPtr<RAIIBufferData> buffer_data = new RAIIBufferData(total_byte_size);

			size_t vertex_count = m_attribute_binder.GetElementCount();

			char* current_buffer_data = static_cast<char*>( buffer_data->GetArrayData());
			for (size_t i = 0; i < vertex_count; i++)
			{
				for (const auto& attribute : m_attribute_binder.GetAttributes())
				{
					const char* attribute_data = static_cast<const char*>(attribute.second->GetData().GetArrayData());
					attribute_data += i * attribute.second->GetByteSizePerElement();

					memcpy(current_buffer_data, attribute_data, attribute.second->GetByteSizePerElement());
					current_buffer_data += attribute.second->GetByteSizePerElement();
				}
			}

			// Init VAO
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			// Create a buffer to store vertex.
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			// Bind the triangle vertex data to buffer.
			glBufferData(GL_ARRAY_BUFFER, buffer_data->GetArrayDataByteSize(), buffer_data->GetArrayData(), GL_STATIC_DRAW);
			GLuint uOffset = 0u;

			for (const auto& attribute : m_attribute_binder.GetAttributes())
			{
				// TODO: modify hard code.
				auto element_component_count = attribute.second->GetByteSizePerElement() / sizeof(float);

				glVertexAttribPointer(attribute.first, element_component_count, GL_FLOAT, GL_FALSE, attribute.second->GetByteSizePerElement(), (GLvoid*)uOffset);
				glEnableVertexAttribArray(attribute.first);

				uOffset += attribute.second->GetByteSizePerElement();
			}

			// Set index buffer
			if (m_attribute_binder.HasIndexAttribute())
			{
				auto& index_attribute = m_attribute_binder.GetIndexAttribute();

				glGenBuffers(1, &m_IBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_attribute.GetData().GetArrayDataByteSize(), index_attribute.GetData().GetArrayData(), GL_STATIC_DRAW);
			}

			// Unbind VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Unbind VAO
			glBindVertexArray(0);

			return true;
		}

	}
}