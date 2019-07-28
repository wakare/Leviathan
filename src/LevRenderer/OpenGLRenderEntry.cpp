#include "OpenGLRenderEntry.h"
#include "OpenGLNumericalUniform.h"
#include "OpenGLRenderStateManager.h"
#include "LevRAttrRenderStateManager.h"
#include "OpenGLRenderStateDepthFunc.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderEntry::OpenGLRenderEntry(unsigned id, GLenum primitive_type, const Scene::LevRAttrRenderObjectAttributeBinder& attribute_binder)
			: m_attribute_binder(attribute_binder)
			, m_render_state_manager(nullptr)
			, m_inited(false)
			, m_primitive_type(primitive_type)
			, m_id(id)
		{

		}

		/*
			A Empty object
		*/
		OpenGLRenderEntry::OpenGLRenderEntry(unsigned id)
			: m_attribute_binder(Scene::LevRAttrRenderObjectAttributeBinder(0))
			, m_render_state_manager(nullptr)
			, m_inited(false)
			, m_primitive_type(GL_INVALID_ENUM)
			, m_id(id)
		{

		}

		void OpenGLRenderEntry::SetRenderStateManager(const Scene::LevRAttrRenderStateManager& render_state)
		{
			const auto& states = render_state.GetAllRenderState();
			if (states.size() == 0)
			{
				return;
			}

			m_render_state_manager.Reset(new OpenGLRenderStateManager);
			for (const auto& state : states)
			{
				switch (state.first)
				{
				case Scene::ELRST_DEPTH_FUNC:
				{
					const Scene::LevRenderStateDepthFunc* depth_func_point = dynamic_cast<const Scene::LevRenderStateDepthFunc*>(state.second.Get());
					LEV_ASSERT(depth_func_point);

					LPtr<OpenGLRenderStateDepthFunc> depth_func = new OpenGLRenderStateDepthFunc(*depth_func_point);
					m_render_state_manager->AddRenderState(TryCast<Renderer::OpenGLRenderStateDepthFunc, OpenGLRenderState>(depth_func));
				}
				break;

				}
			}
		}

		void OpenGLRenderEntry::AddUniform(LPtr<OpenGLNumericalUniform> uniform)
		{
			m_uniforms.push_back(uniform);
		}

		bool OpenGLRenderEntry::Render(GLuint shaderProgram)
		{
			if (!m_inited)
			{
				m_inited = _init();
				LEV_ASSERT(m_inited);
			}

			EXIT_IF_FALSE(m_VAO);
			glBindVertexArray(m_VAO);

			bool use_index = m_attribute_binder.HasIndexAttribute();
			if (use_index)
			{
				glDrawElements(m_primitive_type, m_attribute_binder.GetVertexCount(), GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawArrays(m_primitive_type, 0, m_attribute_binder.GetVertexCount());
			}

			glBindVertexArray(0);

			return true;
		}

		bool OpenGLRenderEntry::PostRender(GLuint shaderProgram)
		{
			_unapplyAllState();

			for (auto& fn : m_postprocess_fns)
			{
				fn();
			}

			return true;
		}

		bool OpenGLRenderEntry::PreRender(GLuint shaderProgram)
		{
			for (auto& fn : m_preprocess_fns)
			{
				fn();
			}

			EXIT_IF_FALSE(ApplyUniform(shaderProgram));

			_applyAllState();

			return true;
		}

		bool OpenGLRenderEntry::ApplyUniform(GLuint shaderProgram)
		{
			for (auto& pUniform : m_uniforms)
			{
				EXIT_IF_FALSE(pUniform->Apply(shaderProgram));
			}

			return true;
		}

		unsigned OpenGLRenderEntry::GetID() const
		{
			return m_id;
		}

		void OpenGLRenderEntry::AddPreProcess(std::function<void()> fn)
		{
			m_preprocess_fns.push_back(fn);
		}

		void OpenGLRenderEntry::AddPostProcess(std::function<void()> fn)
		{
			m_postprocess_fns.push_back(fn);
		}

		bool OpenGLRenderEntry::_init()
		{
			// Merge attribute data to temp array
			size_t attribute_size = m_attribute_binder.GetAttributes().size();
			EXIT_IF_FALSE(attribute_size > 0)
			
			size_t total_byte_size = 0;
			size_t element_byte_size = 0;

			for (const auto& attribute : m_attribute_binder.GetAttributes())
			{
				total_byte_size += attribute.second->GetData().GetArrayDataByteSize();
				element_byte_size += attribute.second->GetByteSizePerElement();
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

				glVertexAttribPointer(attribute.first, element_component_count, GL_FLOAT, GL_FALSE, element_byte_size, (GLvoid*)uOffset);
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

		void OpenGLRenderEntry::_applyAllState()
		{
			if (m_render_state_manager)
			{
				m_render_state_manager->ApplyAllRenderState();
			}
		}

		void OpenGLRenderEntry::_unapplyAllState()
		{
			if (m_render_state_manager)
			{
				m_render_state_manager->UnApplyAllRenderState();
			}
		}

	}
}