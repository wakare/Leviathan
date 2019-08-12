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
#include "OpenGLEmptyRenderEntry.h"
#include "LevRAttrPointSize.h"
#include "LevRAttrLightEnable.h"
#include "LevRAttrVisible.h"
#include "LevRAttrNumericalUniform.h"
#include "OpenGLRenderEntry.h"
#include "LevRAttrRenderObjectAttributeBinder.h"
#include "LevRAttrShaderProgram.h"
#include "LevRAttrUniformManager.h"
#include "LevRAttrTextureUniform.h"
#include "LevRAttrRenderStateManager.h"
#include "OpenGLRStatePointSize.h"
#include "OpenGLTextureUniform.h"

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

		OpenGLRenderDataProcessor::OpenGLRenderDataProcessor()
			: m_traverseVisitor(new Scene::LevSceneTreeTraverseVisitor)
			, m_searchVisitor(new Scene::LevSceneTreeSearchVisitor)
			, m_resource_manager(new OpenGLResourceManager)
			, m_current_render_tree_id(-1)
		{
			// Default pass callback
			const auto _sceneObjectTraverseCallback = [this](const Scene::LevSceneObject& object, const std::vector<const Node<Scene::LevSceneObject>*>& stack)
			{
				// update scene drawable objects
				if (!object.HasModified())
				{
					return true;
				}

				LPtr<OpenGLRenderEntry> gl_render_entry = nullptr;

				RenderTreeID render_tree_id = INT_MAX;

				size_t stack_size = stack.size();
				for (unsigned i = 0; i < stack_size; i++)
				{
					unsigned index = stack_size - i - 1;

					auto& parent = stack[index];
					const Scene::LevRAttrShaderProgram* shader_program = nullptr;
					parent->GetNodeData()->GetAttribute<Scene::LevRAttrShaderProgram>(shader_program);

					if (shader_program)
					{
						render_tree_id = m_resource_manager->GetOrCreateRenderTree(*shader_program);
						break;
					}
				}

				if (render_tree_id == INT_MAX)
				{
					return false;
				}

				const Scene::LevRAttrRenderObjectAttributeBinder* attribute_binder = nullptr;
				object.GetAttribute<Scene::LevRAttrRenderObjectAttributeBinder>(attribute_binder);

				GLenum primitive_type = GL_NONE;
				if (attribute_binder)
				{
					switch (attribute_binder->GetPrimitiveType())
					{
					case Scene::EROPT_POINTS:
						primitive_type = GL_POINTS;
						break;

					case Scene::EROPT_LINES:
						primitive_type = GL_LINES;
						break;

					case Scene::EROPT_TRIANGLES:
						primitive_type = GL_TRIANGLES;
						break;

					default:
						primitive_type = GL_NONE;
						break;
					}
				}

				switch (object.GetState())
				{
				case Scene::ELSOS_ADDED:
				{
					if (attribute_binder)
					{
						gl_render_entry = new OpenGLRenderEntry(object.GetID(), primitive_type, *attribute_binder);
					}
					else
					{
						gl_render_entry = new OpenGLEmptyRenderEntry(object.GetID());
					}
					
					for (auto& attribute : object.GetAllAttributes())
					{
						const Scene::LevSceneRenderAttribute* pAttribute = dynamic_cast<const Scene::LevSceneRenderAttribute*>(attribute.Get());
						if (!pAttribute)
						{
							continue;
						}

						_applyRenderAttribute(gl_render_entry, *pAttribute);
					}

					m_resource_manager->AddGLObjectToRenderTree(render_tree_id, gl_render_entry);
					break;
				}

				case Scene::ELSOS_UPDATE:
				{
					if (attribute_binder)
					{
						gl_render_entry = new OpenGLRenderEntry(object.GetID(), primitive_type, *attribute_binder);
					}
					else
					{
						gl_render_entry = new OpenGLEmptyRenderEntry(object.GetID());
					}

					for (auto& attribute : object.GetAllAttributes())
					{
						const Scene::LevSceneRenderAttribute* pAttribute = dynamic_cast<const Scene::LevSceneRenderAttribute*>(attribute.Get());
						if (!pAttribute)
						{
							continue;
						}

						_applyRenderAttribute(gl_render_entry, *pAttribute);
					}

					m_resource_manager->ReplaceGLObjectFromRenderTree(render_tree_id, gl_render_entry);
					break;
				}

				case Scene::ELSOS_DELETED:
				case Scene::ELSOS_DISABLE:
				{
					m_resource_manager->RemoveResource(render_tree_id, object.GetID());
					return true;
				}

				}

				LEV_ASSERT(gl_render_entry);

				return true;
			};

			m_traverseVisitor->SetTraverseCallback(_sceneObjectTraverseCallback);
		}
	
		void OpenGLRenderDataProcessor::UpdateInputData(const Scene::LevSceneData & sceneData)
		{
			m_traverseVisitor->Apply(sceneData.GetSceneTree().GetRoot());
		}

		OpenGLResourceManager & OpenGLRenderDataProcessor::GetResourceManager()
		{
			return *m_resource_manager;
		}

		const Leviathan::Renderer::OpenGLResourceManager& OpenGLRenderDataProcessor::GetResourceManager() const
		{
			return *m_resource_manager;
		}

		bool OpenGLRenderDataProcessor::_applyRenderAttribute(LPtr<OpenGLRenderEntry> OpenGL_object, const Scene::LevSceneRenderAttribute& render_attribute)
		{
			// Point size attribute
			const Scene::LevRAttrPointSize* point_size = dynamic_cast<const Scene::LevRAttrPointSize*>(&render_attribute);
			if (point_size)
			{
				const auto size = point_size->GetSize();
				OpenGL_object->AddRenderState(new OpenGLRStatePointSize(size));
				
				return true;
			}

			// Depth func attribute
			const Scene::LevRAttrRenderStateManager* render_state_manager = dynamic_cast<const Scene::LevRAttrRenderStateManager*>(&render_attribute);
			if (render_state_manager)
			{
				OpenGL_object->SetRenderStateManager(*render_state_manager);
				return true;
			}

			// Light enable attribute
			const Scene::LevRAttrLightEnable* light_enable = dynamic_cast<const Scene::LevRAttrLightEnable*>(&render_attribute);
			if (light_enable)
			{
// 					auto current_light_enable = m_pCurrentPass->GetLightEnable();
// 					auto enable = light_enable->GetLightEnable();
// 
// 					objects->AddPreProcess([enable, this]() {m_pCurrentPass->SetLightEnable(enable); });
// 					objects->AddPostProcess([current_light_enable, this]() {m_pCurrentPass->SetLightEnable(current_light_enable); });
			}

			// Object visible attribute
			const Scene::LevRAttrVisible* visible = dynamic_cast<const Scene::LevRAttrVisible*>(&render_attribute);
			if (visible)
			{
// 				for (auto& pObject : objects)
// 				{
// 					pObject->SetVisible(visible->GetVisible());
// 				}
// 
// 				return true;
			}

			const Scene::LevRAttrUniformManager* uniform_manager = dynamic_cast<const Scene::LevRAttrUniformManager*>(&render_attribute);
			if (uniform_manager)
			{
				for (const auto& uniform : uniform_manager->GetUniforms())
				{
					LPtr<IOpenGLUniform> OpenGL_uniform = nullptr;

					switch (uniform.second->GetUniformType())
					{
					case Scene::ELUT_NUMERICAL:
					{
						const Scene::LevRAttrNumericalUniform* numerical_uniform = dynamic_cast<const Scene::LevRAttrNumericalUniform*>(uniform.second.Get());
						OpenGL_uniform = new OpenGLNumericalUniform(*numerical_uniform);
						break;
					}	
					case Scene::ELUT_TEXTURE:
					{
						const Scene::LevRAttrTextureUniform* texture_uniform = dynamic_cast<const Scene::LevRAttrTextureUniform*>(uniform.second.Get());
						OpenGL_uniform = new OpenGLTextureUniform(*texture_uniform);
						break;
					}	
					}

					LEV_ASSERT(OpenGL_uniform);
					OpenGL_object->AddUniform(OpenGL_uniform);
				}

				return true;
			}

			return false;
		}
	}
}


