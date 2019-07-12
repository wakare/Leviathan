#include "OpenGLRenderDataProcessor.h"

#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevMeshObject.h"
#include "LevLight.h"
#include "LevPointLight.h"
#include "LevSceneTreeTraverseVisitor.h"
#include "LevSceneTreeSearchVisitor.h"
#include "LevSceneObjectAttribute.h"
#include "LevRAttrObjectColor.h"

#include "IMesh.h"
#include "DynamicArray.h"
#include "GLTexture.h"
#include "PictureObject.h"
#include "GeometryCalculator.h"

#include "OpenGLTexture.h"
#include "OpenGLMaterial.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLPointLight.h"
#include "OpenGLResourceManager.h"
#include "LevSceneRenderAttribute.h"
#include "LevLRAttrModelTransform.h"
#include "LevLRAttrWorldTransform.h"
#include "OpenGLUniform.h"
#include "OpenGLEmptyObject.h"
#include "LevRAttrPointSize.h"
#include "LevRAttrDepthFunc.h"
#include "LevRAttrLightEnable.h"
#include "LevRAttrVisible.h"
#include "LevRAttrUniform.h"
#include "OpenGLObject.h"
#include "LevRAttrRenderObjectAttributeBinder.h"
#include "LevRAttrShaderProgram.h"
#include "LevRAttrUniformManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		std::string _getShaderSource(const char* pczShaderSourcePath)
		{
			std::ifstream shaderSourceFileStream(pczShaderSourcePath, std::ios::in);
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
			auto _sceneObjectTraverseCallback = [this](const Scene::LevSceneObject& object, const std::vector<const Node<Scene::LevSceneObject>*>& stack)
			{
				// update scene drawable objects
				if (!object.HasModified())
				{
					return true;
				}

				if ((object.GetType() & Scene::ELSOT_UNRENDERABLE) > 0)
				{
					return true;
				}

// 				if (!object.HasObjectDesc())
// 				{
// 					return true;
// 				}

				GLenum primitive_type = GL_TRIANGLES;
// 				switch (object.GetObjectDesc().GetType())
// 				{
// 				case ELSOD_MESH_TRIANGLE:
// 					primitive_type = GL_TRIANGLES;
// 					break;
// 
// 				case ELSOD_MESH_POINT:
// 					primitive_type = GL_POINTS;
// 					break;
// 
// 				case ELSOD_MESH_LINE:
// 					primitive_type = GL_LINES;
// 					break;
// 
// 				default:
// 					//LEV_ASSERT(false);
// 					//return false;
// 					primitive_type = GL_TRIANGLES;
// 				}

				LPtr<OpenGLObject> opengl_object = nullptr;

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

				switch (object.GetState())
				{
				case Scene::ELSOS_ADDED:
				{
					EXIT_IF_FALSE(attribute_binder);

					opengl_object = new OpenGLObject(object.GetID(), primitive_type, *attribute_binder);
					for (auto& attribute : object.GetAllAttributes())
					{
						const Scene::LevSceneRenderAttribute* pAttribute = dynamic_cast<const Scene::LevSceneRenderAttribute*>(attribute.Get());
						if (!pAttribute)
						{
							continue;
						}

						_applyRenderAttribute(opengl_object, *pAttribute);
					}

					m_resource_manager->AddGLObject(render_tree_id, opengl_object);
					break;
				}

				case Scene::ELSOS_UPDATE:
				{
					EXIT_IF_FALSE(attribute_binder);
					
					opengl_object = new OpenGLObject(object.GetID(), primitive_type, *attribute_binder);
					for (auto& attribute : object.GetAllAttributes())
					{
						const Scene::LevSceneRenderAttribute* pAttribute = dynamic_cast<const Scene::LevSceneRenderAttribute*>(attribute.Get());
						if (!pAttribute)
						{
							continue;
						}

						_applyRenderAttribute(opengl_object, *pAttribute);
					}

					m_resource_manager->ReplaceGLObject(render_tree_id, opengl_object);
					break;
				}

				case Scene::ELSOS_DELETED:
				case Scene::ELSOS_DISABLE:
				{
					m_resource_manager->RemoveResource(render_tree_id, object.GetID());
					return true;
				}

				}

				LEV_ASSERT(opengl_object);

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

		bool OpenGLRenderDataProcessor::_applyRenderAttribute(LPtr<OpenGLObject> objects, const Scene::LevSceneRenderAttribute& render_attribute)
		{
			// Point size attribute
			const Scene::LevRAttrPointSize* point_size = dynamic_cast<const Scene::LevRAttrPointSize*>(&render_attribute);
			if (point_size)
			{
				auto size = point_size->GetSize();
				objects->AddPreProcess([size]() {glPointSize(size); });
				objects->AddPostProcess([size]() {glPointSize(1); });
				
				return true;
			}

			// Depth func attribute
			const Scene::LevRAttrDepthFunc* depth_func = dynamic_cast<const Scene::LevRAttrDepthFunc*>(&render_attribute);
			if (depth_func)
			{
					GLenum gl_depth_parameter;
					switch (depth_func->GetDepthParameter())
					{
					case Scene::ELDFP_LESS:
						gl_depth_parameter = GL_LESS;
						break;

					case Scene::ELDFP_LEQUAL:
						gl_depth_parameter = GL_LEQUAL;
						break;

					case Scene::ELDFP_EQUAL:
						gl_depth_parameter = GL_EQUAL;
						break;

					case Scene::ELDFP_ALWAYS:
						gl_depth_parameter = GL_ALWAYS;
						break;

					case Scene::ELDFP_UNKNOWN:
					default:
						LEV_ASSERT(false);
						return false;
					}

					objects->AddPreProcess([gl_depth_parameter]() {glDepthFunc(gl_depth_parameter); });
					objects->AddPostProcess([]() {glDepthFunc(GL_LESS); });
			
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
					LPtr<OpenGLUniform> opengl_uniform = new OpenGLUniform(*uniform.second);
					objects->AddUniform(opengl_uniform);
				}

				return true;
			}

			return false;
		}
	}
}


