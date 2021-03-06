#include "OpenGLRenderEntry.h"
#include "OpenGLNumericalUniform.h"
#include "OpenGLRenderStateManager.h"
#include "LevRAttrRenderStateManager.h"
#include "OpenGLRStateDepthFunc.h"
#include "LevRenderStatePointSize.h"
#include "LevSceneObject.h"
#include "OpenGLRStatePointSize.h"
#include "OpenGLRenderResourceManager.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderEntry::OpenGLRenderEntry(OpenGLRenderResourceManager& render_entry_manager, const Scene::LevSceneObject& object)
			: IOpenGLRenderResource(render_entry_manager)
			, m_attribute_binder(nullptr)
			, m_inited(false)
			, m_primitive_type(GL_INVALID_ENUM)
			, m_id(object.GetID())
			, m_frame_buffer_object(nullptr)
		{
			object.GetAttribute<Scene::LevRAttrRenderObjectAttributeBinder>(m_attribute_binder);
			LEV_ASSERT(m_attribute_binder);

			switch (m_attribute_binder->GetPrimitiveType())
			{
			case Scene::EROPT_POINTS:
				m_primitive_type = GL_POINTS;
				break;

			case Scene::EROPT_LINES:
				m_primitive_type = GL_LINES;
				break;

			case Scene::EROPT_TRIANGLES:
				m_primitive_type = GL_TRIANGLES;
				break;

			default:
				m_primitive_type = GL_INVALID_ENUM;
				break;
			}
		}

		OpenGLRenderEntry::~OpenGLRenderEntry()
		{
			if (m_VAO) IOR_PUSH_SYNC_RENDER_COMMAND(glDeleteVertexArrays(1, &m_VAO));
			if (m_VBO) IOR_PUSH_SYNC_RENDER_COMMAND(glDeleteBuffers(1, &m_VBO));
			if (m_IBO) IOR_PUSH_SYNC_RENDER_COMMAND(glDeleteBuffers(1, &m_IBO));
		}

		/*
			A Empty object
		*/
		OpenGLRenderEntry::OpenGLRenderEntry(OpenGLRenderResourceManager& render_entry_manager, unsigned id)
			: IOpenGLRenderResource(render_entry_manager)
			, m_attribute_binder(nullptr)
			, m_inited(false)
			, m_primitive_type(GL_INVALID_ENUM)
			, m_id(id)
		{

		}

		void OpenGLRenderEntry::SetRenderStateManager(const Scene::LevRAttrRenderStateManager& render_state)
		{
			const auto& states = render_state.GetAllRenderState();
			if (states.empty())
			{
				return;
			}

			for (const auto& state : states)
			{
				switch (state.first)
				{
				case Scene::ELRST_DEPTH_FUNC:
				{
					const auto* depth_func = dynamic_cast<const Scene::LevRenderStateDepthFunc*>(state.second.Get());
					LEV_ASSERT(depth_func);

					LSPtr<IOpenGLRenderState> depth_func_state = new OpenGLRStateDepthFunc(*depth_func);
					m_render_states.push_back(depth_func_state);
				}
				break;

				case Scene::ELRST_POINT_SIZE:
				{
					const auto* point_size = dynamic_cast<const Scene::LevRenderStatePointSize*>(state.second.Get());
					LEV_ASSERT(point_size);

					LSPtr<IOpenGLRenderState> point_size_state = new OpenGLRStatePointSize(point_size->GetPointSize());
					m_render_states.push_back(point_size_state);
				}
				break;

				}
			}
		}

		void OpenGLRenderEntry::SetFrameBufferObject(LSPtr<OpenGLFrameBufferObject> frame_buffer)
		{
			m_frame_buffer_object = frame_buffer;
		}

		LSPtr<OpenGLFrameBufferObject> OpenGLRenderEntry::GetFrameBufferObject()
		{
			return m_frame_buffer_object;
		}

		void OpenGLRenderEntry::AddRenderState(LSPtr<IOpenGLRenderState> render_state)
		{
			m_render_states.push_back(render_state);
		}

		void OpenGLRenderEntry::AddUniform(LSPtr<IOpenGLUniform> uniform)
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
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindVertexArray(m_VAO));

			LEV_ASSERT(m_attribute_binder);
			const bool use_index = m_attribute_binder->HasIndexAttribute();
			if (use_index)
			{
				IOR_PUSH_ASYNC_RENDER_COMMAND(glDrawElements(m_primitive_type, m_attribute_binder->GetVertexCount(), GL_UNSIGNED_INT, 0));
			}
			else
			{
				IOR_PUSH_ASYNC_RENDER_COMMAND(glDrawArrays(m_primitive_type, 0, m_attribute_binder->GetVertexCount()));
			}

			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindVertexArray(0));

			return true;
		}

		unsigned OpenGLRenderEntry::GetID() const
		{
			return m_id;
		}

		const std::vector<LSPtr<IOpenGLRenderState>>& OpenGLRenderEntry::GetRenderState() const
		{
			return m_render_states;
		}

		const std::vector<LSPtr<IOpenGLUniform>>& OpenGLRenderEntry::GetUniforms() const
		{
			return m_uniforms;
		}

		bool OpenGLRenderEntry::_init()
		{
			LEV_ASSERT(m_attribute_binder);

			// Merge attribute data to temp array
			size_t attribute_size = m_attribute_binder->GetAttributes().size();
			EXIT_IF_FALSE(attribute_size > 0)
			
			size_t element_byte_size = 0;

			for (const auto& attribute : m_attribute_binder->GetAttributes())
			{
				element_byte_size += attribute.second->GetByteSizePerElement();
			}

			const size_t vertex_count = m_attribute_binder->GetElementCount();
			LSPtr<RAIIBufferData> buffer_data = new RAIIBufferData(element_byte_size * vertex_count);

			char* current_buffer_data = static_cast<char*>( buffer_data->GetArrayData());
			for (size_t i = 0; i < vertex_count; i++)
			{
				for (const auto& attribute : m_attribute_binder->GetAttributes())
				{
					const char* attribute_data = static_cast<const char*>(attribute.second->GetData().GetArrayData());
					attribute_data += i * attribute.second->GetByteSizePerElement();

					memcpy(current_buffer_data, attribute_data, attribute.second->GetByteSizePerElement());
					current_buffer_data += attribute.second->GetByteSizePerElement();
				}
			}

			// Init VAO
			IOR_PUSH_ASYNC_RENDER_COMMAND(glGenVertexArrays(1, &m_VAO));
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindVertexArray(m_VAO));

			// Create a buffer to store vertex.
			IOR_PUSH_ASYNC_RENDER_COMMAND(glGenBuffers(1, &m_VBO));
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));

			// Bind the triangle vertex data to buffer.
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBufferData(GL_ARRAY_BUFFER, buffer_data->GetArrayDataByteSize(), buffer_data->GetArrayData(), GL_STATIC_DRAW));
			GLuint uOffset = 0u;

			for (const auto& attribute : m_attribute_binder->GetAttributes())
			{
				// TODO: modify hard code.
				auto element_component_count = attribute.second->GetByteSizePerElement() / sizeof(float);

				IOR_PUSH_ASYNC_RENDER_COMMAND(glVertexAttribPointer(attribute.first, element_component_count, GL_FLOAT, GL_FALSE, element_byte_size, (GLvoid*)uOffset));
				IOR_PUSH_ASYNC_RENDER_COMMAND(glEnableVertexAttribArray(attribute.first));

				uOffset += attribute.second->GetByteSizePerElement();
			}

			// Set index buffer
			if (m_attribute_binder->HasIndexAttribute())
			{
				auto& index_attribute = m_attribute_binder->GetIndexAttribute();

				IOR_PUSH_ASYNC_RENDER_COMMAND(glGenBuffers(1, &m_IBO));
				IOR_PUSH_ASYNC_RENDER_COMMAND(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
				IOR_PUSH_ASYNC_RENDER_COMMAND(glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_attribute.GetData().GetArrayDataByteSize(), index_attribute.GetData().GetArrayData(), GL_STATIC_DRAW));
			}

			// Unbind VBO
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindBuffer(GL_ARRAY_BUFFER, 0));

			// Unbind VAO
			IOR_PUSH_ASYNC_RENDER_COMMAND(glBindVertexArray(0));

			return true;
		}
	}
}
