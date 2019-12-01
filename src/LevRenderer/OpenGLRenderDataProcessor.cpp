#include "OpenGLRenderDataProcessor.h"
#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevLight.h"
#include "LevSceneTreeTraverseVisitor.h"
#include "LevSceneTreeSearchVisitor.h"
#include "PictureObject.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLResourceManager.h"
#include "LevSceneRenderAttribute.h"
#include "OpenGLNumericalUniform.h"
#include "LevNumericalUniform.h"
#include "OpenGLRenderEntry.h"
#include "LevRAttrRenderObjectAttributeBinder.h"
#include "LevRAttrShaderProgram.h"
#include "LevRAttrUniformManager.h"
#include "LevTextureUniform.h"
#include "LevRAttrRenderStateManager.h"
#include "OpenGLTextureUniform.h"
#include "LevRAttrFrameBufferObject.h"
#include "OpenGLFrameBufferObject.h"
#include "OpenGLRenderResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		std::string _getShaderSource(const char* pczShaderSourcePath)
		{
			const std::ifstream shaderSourceFileStream(pczShaderSourcePath, std::ios::in);
			if (!shaderSourceFileStream.is_open())
			{
				LogLine("Invalid ShaderSource paths:" << pczShaderSourcePath);
				return std::string();
			}

			std::stringstream strStream;
			strStream << shaderSourceFileStream.rdbuf();
			return strStream.str();
		}

		OpenGLRenderDataProcessor::OpenGLRenderDataProcessor(OpenGLResourceManager& resource_manager)
			: m_resource_manager(resource_manager)
			, m_current_render_tree_id(-1)
			, m_searchVisitor(new Scene::LevSceneTreeSearchVisitor)
			, m_traverseVisitor(new Scene::LevSceneTreeTraverseVisitor) 
		{
			// Default pass callback
			const auto _sceneObjectTraverseCallback = [this](const Scene::LevSceneObject& object, const std::vector<const Node<Scene::LevSceneObject>*>& stack)
			{
				// update scene drawable objects
				if (!object.HasModified())
				{
					return true;
				}

				LSPtr<OpenGLRenderEntry> render_entry = nullptr;

				RenderTreeID render_tree_id = INT_MAX;

				size_t stack_size = stack.size();
				const Scene::LevRAttrShaderProgram* shader_program = nullptr;
				object.GetAttribute<Scene::LevRAttrShaderProgram>(shader_program);

				if (!shader_program)
				{
					for (unsigned i = 0; i < stack_size; i++)
					{
						unsigned index = stack_size - i - 1;

						auto& parent = stack[index];

						parent->GetNodeData()->GetAttribute<Scene::LevRAttrShaderProgram>(shader_program);

						if (shader_program)
						{
							break;
						}
					}
				}

				if (!shader_program)
				{
					return false;
				}

				render_tree_id = m_resource_manager.GetOrCreateRenderTree(*shader_program);

				const Scene::LevRAttrRenderObjectAttributeBinder* attribute_binder = nullptr;
				object.GetAttribute<Scene::LevRAttrRenderObjectAttributeBinder>(attribute_binder);

				auto& render_entry_manager = m_resource_manager.GetRenderEntryManager();
				if (stack_size > 0)
				{
					render_entry_manager.SetParent(object, *stack.back()->GetNodeData());
				}

				switch (object.GetState())
				{
				case Scene::ELSOS_ADDED:
				{
					if (attribute_binder)
					{
						render_entry_manager.CreateRenderEntry(object, render_entry);
					}
					else
					{
						render_entry_manager.CreateEmptyRenderEntry(object, render_entry);
					}
					
					for (auto& attribute : object.GetAllAttributes())
					{
						const Scene::LevSceneRenderAttribute* pAttribute = dynamic_cast<const Scene::LevSceneRenderAttribute*>(attribute.Get());
						if (!pAttribute)
						{
							continue;
						}

						_applyRenderAttribute(render_entry, *pAttribute);
					}

					m_resource_manager.AddGLObjectToRenderTree(render_tree_id, render_entry);
					break;
				}

				case Scene::ELSOS_UPDATE:
				{
					if (attribute_binder)
					{
						render_entry_manager.UpdateRenderEntry(object, render_entry);
					}
					else
					{
						render_entry_manager.UpdateEmptyRenderEntry(object, render_entry);
					}

					for (auto& attribute : object.GetAllAttributes())
					{
						auto* pAttribute = attribute.To<const Scene::LevSceneRenderAttribute>().Get();
						if (!pAttribute)
						{
							continue;
						}

						_applyRenderAttribute(render_entry, *pAttribute);
					}

					m_resource_manager.ReplaceGLObjectFromRenderTree(render_tree_id, render_entry);
					break;
				}

				case Scene::ELSOS_DELETED:
				case Scene::ELSOS_DISABLE:
				{
					render_entry_manager.RemoveRenderEntry(object.GetID());
					m_resource_manager.RemoveGLObjectFromRenderTree(render_tree_id, object.GetID());
						
					return true;
				}

				}

				LEV_ASSERT(render_entry);

				return true;
			};

			m_traverseVisitor->SetTraverseCallback(_sceneObjectTraverseCallback);
		}
	
		void OpenGLRenderDataProcessor::UpdateInputData(const Scene::LevSceneData & sceneData)
		{
			m_traverseVisitor->Apply(sceneData.GetSceneTree().GetRoot());
		}

		bool OpenGLRenderDataProcessor::_applyRenderAttribute(LSPtr<OpenGLRenderEntry> OpenGL_object, const Scene::LevSceneRenderAttribute& render_attribute)
		{
			switch (render_attribute.GetRenderAttributeType())
			{
			case Scene::ERAT_ATTACHMENT_MANAGER:
				break;

			case Scene::ERAT_DEPTH_FUNC:
				break;

			case Scene::ERAT_FRAME_BUFFER_OBJECT:
			{
				const Scene::LevRAttrFrameBufferObject* frame_buffer_object = render_attribute.ToLevRAttrFrameBufferObject();
				if (frame_buffer_object && frame_buffer_object->GetFrameBufferObject())
				{
					LSPtr<OpenGLFrameBufferObject> fbo = new OpenGLFrameBufferObject(m_resource_manager.GetObjectManager(), *frame_buffer_object->GetFrameBufferObject());
					OpenGL_object->SetFrameBufferObject(fbo);
					return true;
				}

				break;
			}

			case Scene::ERAT_RENDER_OBJECT_ATTRIBUTE_BINDER:
				break;

			case Scene::ERAT_RENDER_STATE_MANAGER:
			{
				const Scene::LevRAttrRenderStateManager* render_state_manager = render_attribute.ToLevRAttrRenderStateManager();
				if (render_state_manager)
				{
					OpenGL_object->SetRenderStateManager(*render_state_manager);
					return true;
				}

				break;
			}

			case Scene::ERAT_SHADER_PROGRAM:
				break;

			case Scene::ERAT_UNIFORM_MANAGER:
			{
				const Scene::LevRAttrUniformManager* uniform_manager = render_attribute.ToLevRAttrUniformManager();
				if (uniform_manager)
				{
					for (const auto& uniform : uniform_manager->GetUniforms())
					{
						LSPtr<IOpenGLUniform> OpenGL_uniform = nullptr;

						switch (uniform.second->GetUniformType())
						{
						case Scene::ELUT_NUMERICAL:
						{
							const Scene::LevNumericalUniform* numerical_uniform = dynamic_cast<const Scene::LevNumericalUniform*>(uniform.second.Get());
							OpenGL_uniform = new OpenGLNumericalUniform(m_resource_manager.GetObjectManager(), *numerical_uniform);
							break;
						}
						case Scene::ELUT_TEXTURE:
						{
							const Scene::LevTextureUniform* texture_uniform = dynamic_cast<const Scene::LevTextureUniform*>(uniform.second.Get());
							OpenGL_uniform = new OpenGLTextureUniform(m_resource_manager.GetObjectManager(), *texture_uniform);
							break;
						}
						}

						LEV_ASSERT(OpenGL_uniform);
						OpenGL_object->AddUniform(OpenGL_uniform);
					}

					return true;
				}

				break;
			}

			case Scene::ERAT_VISIBLE:
				break;

			case Scene::ERAT_UNKNOWN:
				break;

			default:
				assert(false);
				break;
			}

			return false;
		}
	}
}


