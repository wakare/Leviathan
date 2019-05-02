#include "OpenGLRenderData.h"

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

#include "OpenGL3DPass.h"
#include "OpenGL3DObject.h"
#include "OpenGLTexture.h"
#include "OpenGLMaterial.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLPointLight.h"
#include "OpenGLResourceMgr.h"
#include "LevSceneRenderAttribute.h"
#include "LevLRAttrModelTransform.h"
#include "LevLRAttrWorldTransform.h"
#include "OpenGLUniform.h"
#include "OpenGLEmptyObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		std::string _getShaderSource(const char* pczShaderSourcePath)
		{
			std::ifstream shaderSourceFileStream(pczShaderSourcePath, std::ios::in);
			if (!shaderSourceFileStream.is_open())
			{
				throw "std::string Scene::_getShaderSource(const char* pczShaderSourcePath) --> Invalid ShaderSource paths.";
				return std::string();
			}

			std::stringstream strStream;
			strStream << shaderSourceFileStream.rdbuf();
			return strStream.str();
		}

		OpenGLRenderData::OpenGLRenderData()
			: m_traverseVisitor(new Scene::LevSceneTreeTraverseVisitor)
			, m_searchVisitor(new Scene::LevSceneTreeSearchVisitor)
			, m_resourceMgr(new OpenGLResourceMgr)
		{
			// Default pass callback
			auto _sceneObjectTraverseCallback = [this](const Scene::LevSceneObject& object, const std::vector<const Node<Scene::LevSceneObject>*>& stack)
			{
				// update scene drawable objects
				if (!object.HasModified())
				{
					return true;
				}

				if ((object.GetType() & Scene::ELSOT_CAMERA) > 0)
				{
					const Scene::LevCamera* pCamera = dynamic_cast<const Scene::LevCamera*>(&object);
					if (pCamera)
					{
						_updateCamera(*pCamera);
					}
				}

				// Update light
				if ((object.GetType() & Scene::ELSOT_LIGHT) > 0)
				{
					const Scene::LevLight* pLight = dynamic_cast<const Scene::LevLight*>(&object);
					if (pLight)
					{
						_updateLight(*pLight);
					}
				}

				if ((object.GetType() & Scene::ELSOT_UNRENDERABLE) > 0)
				{
					return true;
				}

				auto& objDesc = object.GetObjDesc();
				if (objDesc.GetType() != ELSOD_MESH)
				{
					return true;
				}

				// TODO: change style to get mesh data?
				const Scene::LevMeshObject* pMesh = dynamic_cast<const Scene::LevMeshObject*>(&objDesc);
				if (!pMesh)
				{
					return true;
				}

				// Get OpenGLObjects
				std::vector<LPtr<OpenGLObject>> pObjects;

				switch (object.GetState())
				{
				case Scene::ELSOS_ADDED:
				{
					auto inited = ConvertMeshToGLObject(object.GetID(), *pMesh, pObjects);
					LEV_ASSERT(inited && pObjects.size() > 0);
					_registerToPass(object.GetID(), pObjects);
					break;
				}

				case Scene::ELSOS_UPDATE:
				{
					_unregisterFromPass(object.GetID());
					auto inited = ConvertMeshToGLObject(object.GetID(), *pMesh, pObjects);
					LEV_ASSERT(inited && pObjects.size() > 0);
					_registerToPass(object.GetID(), pObjects);
					break;
				}

				}

				for (auto& attribute : object.GetObjAttributes())
				{
					const Scene::LevSceneRenderAttribute* pAttribute = dynamic_cast<const Scene::LevSceneRenderAttribute*>(attribute.Get());
					if (!pAttribute)
					{
						continue;
					}

					EXIT_IF_FALSE(_applyRenderAttribute(pObjects, *pAttribute));
				}

				return true;
			};

			m_traverseVisitor->SetTraverseCallback(_sceneObjectTraverseCallback);
		}
	
		void OpenGLRenderData::UpdateInputData(const Scene::LevSceneData & sceneData)
		{
			auto& sceneTree = sceneData.GetSceneTree();

			// Init default pass in first data processing
			if (m_passes.size() == 0)
			{
				auto _findFirstCamera = [this](const Scene::LevSceneObject& object, const std::vector<const Node<Scene::LevSceneObject>*>& stack, bool& stopSearch)
				{
					if ((object.GetType() & Scene::ELSOT_CAMERA) > 0)
					{
						auto pCamera = dynamic_cast<const Scene::LevCamera*>(&object);
						LEV_ASSERT(pCamera);
						_createDefaultPass(pCamera);

						stopSearch = true;
						return false;
					}

					return true;
				};

				m_searchVisitor->SetTraverseCallback(_findFirstCamera);
				m_searchVisitor->Apply(sceneTree.GetRoot());

				LEV_ASSERT(m_passes.size() > 0);
			}
			
			m_traverseVisitor->Apply(sceneTree.GetRoot());
		}

		bool OpenGLRenderData::ConvertMeshToGLObject(unsigned id, const Scene::LevMeshObject& mesh, std::vector<LPtr<OpenGLObject>>& out)
		{
			out.clear();

			for (auto pMesh : mesh.GetMesh())
			{
				LPtr<OpenGLObject> pObject = nullptr;

				if (pMesh->GetPrimitiveType() == IMesh::EPT_TRIANGLES && !_convertTriangleMeshToGLObject(id, pMesh, pObject))
				{
					LeviathanOutStream << "[ERROR] Convert triangle mesh to GLObject failed." << std::endl;
					continue;
				}

				if (pMesh->GetPrimitiveType() == IMesh::EPT_POINTS && !_convertPointMeshToGLObject(id, pMesh, pObject))
				{
					LeviathanOutStream << "[ERROR] Convert triangle mesh to GLObject failed." << std::endl;
					continue;
				}

				out.push_back(pObject);
			}

			return true;
		}

		bool OpenGLRenderData::_updateLight(const Scene::LevLight & light)
		{
			LPtr<OpenGLLight> pGLLight = nullptr;
			switch (light.GetLightType())
			{ 
			case Scene::ELLT_POINT_LIGHT:
			{
				const Scene::LevPointLight* pPointLight = dynamic_cast<const Scene::LevPointLight*>(&light);
				pGLLight = new OpenGLPointLight(*pPointLight);
				break;
			}

			default:
				break;
			}

			if (pGLLight)
			{
				m_lights.push_back(pGLLight);
			}

			_currentPass().AddGLLight(pGLLight);
			return true;
		}

		bool OpenGLRenderData::_updateCamera(const Scene::LevCamera & camera)
		{
			LPtr<OpenGLEmptyObject> pCameraObject = new OpenGLEmptyObject(camera.GetID());
			LPtr<OpenGLUniform> pViewTransform = new OpenGLUniform("viewMatrix", OpenGLUniform::TYPE_FLOAT_MAT4);
			LPtr<OpenGLUniform> pProjTransform = new OpenGLUniform("projMatrix", OpenGLUniform::TYPE_FLOAT_MAT4);
			LPtr<OpenGLUniform> pViewPos = new OpenGLUniform("viewPos", OpenGLUniform::TYPE_FLOAT_VEC3);
			
			pViewTransform->SetData(camera.GetViewportMatrix().data(), 16);
			pProjTransform->SetData(camera.GetProjectMatrix().data(), 16);
			pViewPos->SetData(camera.GetEyePos().data(), 3);

			pCameraObject->AddUniform(pViewTransform);
			pCameraObject->AddUniform(pProjTransform);
			pCameraObject->AddUniform(pViewPos);
			
			std::vector<LPtr<OpenGLObject>> cameraObjs;
			cameraObjs.push_back(TryCast<OpenGLEmptyObject, OpenGLObject>(pCameraObject));
			_registerToPass(camera.GetID(), cameraObjs);
			return true;
		}

		bool OpenGLRenderData::_convertTriangleMeshToGLObject(unsigned id, LPtr<IMesh> pMesh, LPtr<OpenGLObject>& out)
		{
			unsigned uVertexFloatCount = 10;
			auto pMaterial = pMesh->GetMaterial();
			bool bUseTexture = pMaterial && (pMaterial->m_textureName.length() > 0);
			unsigned uVertexTypeMask = OpenGLObject::VERTEX_ATTRIBUTE_XYZ | OpenGLObject::VERTEX_ATTRIBUTE_RGBA | OpenGLObject::VERTEX_ATTRIBUTE_NXYZ;

			if (bUseTexture) uVertexFloatCount += 2;
			DynamicArray<float> glData(pMesh->GetPrimitiveCount() * 3 * uVertexFloatCount * sizeof(float));

			static float defaultColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
			auto color = pMesh->GetVertexColorArray();

			std::map<unsigned, std::vector<Eigen::Vector3f>> vertexNormalVec;

			// Calculate vertex normal
			for (unsigned i = 0; i < pMesh->GetPrimitiveCount(); i++)
			{
				unsigned* vertexIndex = pMesh->GetPrimitiveIndexArray() + 3 * i;
				float* vertices[3] =
				{
					pMesh->GetVertex3DCoordArray() + 3 * vertexIndex[0],
					pMesh->GetVertex3DCoordArray() + 3 * vertexIndex[1],
					pMesh->GetVertex3DCoordArray() + 3 * vertexIndex[2],
				};

				float fNormal[3];
				GeometryCalculator::CalNormal(vertices[0], vertices[1], vertices[2], fNormal);

				Eigen::Vector3f normalVec(fNormal);
				vertexNormalVec[vertexIndex[0]].push_back(normalVec);
				vertexNormalVec[vertexIndex[1]].push_back(normalVec);
				vertexNormalVec[vertexIndex[2]].push_back(normalVec);
			}

			DynamicArray<float> pVertexData(pMesh->GetVertexCount() * uVertexFloatCount * sizeof(float));

			for (unsigned i = 0; i < pMesh->GetVertexCount(); i++)
			{
				float* pData = pVertexData.m_pData + i * uVertexFloatCount;
				memcpy(pData, pMesh->GetVertex3DCoordArray() + 3 * i, sizeof(float) * 3);
				memcpy(pData + 3, color ? color : defaultColor, sizeof(float) * 4);

				// Calculate average normal
				Eigen::Vector3f normal(0.0f, 0.0f, 0.0f);
				for (auto& subNormal : vertexNormalVec[i])
				{
					normal.x() += subNormal.x();
					normal.y() += subNormal.y();
					normal.z() += subNormal.z();
				}

				normal.x() /= vertexNormalVec[i].size();
				normal.y() /= vertexNormalVec[i].size();
				normal.z() /= vertexNormalVec[i].size();

				memcpy(pData + 7, normal.data(), sizeof(float) * 3);

				// Texture coord
				if (bUseTexture)
				{
					auto pTextureData = pMesh->GetVertexTexArray() + 2 * i;
					if (!pTextureData)
					{
						LeviathanOutStream << "[ERROR] Can not get texture data" << std::endl;
					}

					memcpy(pData + 10, pTextureData, sizeof(float) * 2);
				}
			}

			OpenGLMaterial* pGLMaterial = nullptr;
			if (pMaterial)
			{
				pGLMaterial = new OpenGLMaterial(pMaterial->m_ambient.data(), pMaterial->m_diffuse.data(), pMaterial->m_specular.data(), pMaterial->m_fShininess);

				PictureObject texture(pMaterial->m_textureName.c_str());
				if (texture.IsValid())
				{
					uVertexTypeMask |= OpenGLObject::VERTEX_ATTRIBUTE_TEX;
					if (!pGLMaterial->AddTexture2D(new OpenGLTexture(texture.m_pData, texture.m_nWidth, texture.m_nHeight)))
					{
						LeviathanOutStream << "[WARN] Add texture2d failed." << std::endl;
					}
				}
			}

			out = new OpenGL3DObject(id, GL_TRIANGLES, pVertexData.m_pData, pMesh->GetVertexCount(),
				uVertexTypeMask,pGLMaterial, pMesh->GetPrimitiveIndexArray(), pMesh->GetPrimitiveCount() * 3);

			return true;
		}

		bool OpenGLRenderData::_convertPointMeshToGLObject(unsigned id, LPtr<IMesh> pMesh, LPtr<OpenGLObject>& out)
		{
			int vertexMask = OpenGLObject::VERTEX_ATTRIBUTE_XYZ;
			unsigned vertexDataSize = 3;

			// Check with normal
			if (pMesh->GetVertexNormalArray())
			{
				vertexMask |= OpenGLObject::VERTEX_ATTRIBUTE_NXYZ;
				vertexDataSize += 3;
			}

			if (pMesh->GetVertexColorArray())
			{
				vertexMask |= OpenGLObject::VERTEX_ATTRIBUTE_RGBA;
				vertexDataSize += 4;
			}

			DynamicArray<float> tempArray(pMesh->GetVertexCount() * vertexDataSize * sizeof(float));

			for (unsigned i = 0; i < pMesh->GetVertexCount(); i++)
			{
				float* pData = tempArray.m_pData + vertexDataSize * i;
				
				// Fill vertex coord array
				float* pCoord = pMesh->GetVertex3DCoordArray() + 3 * i;
				memcpy(pData, pCoord, 3 * sizeof(float));
				pData += 3;

				if (vertexMask & OpenGLObject::VERTEX_ATTRIBUTE_RGBA)
				{
					float* color = pMesh->GetVertexColorArray() + 3 * i;
					memcpy(pData, color, 3 * sizeof(float));
					pData[3] = 1.0f;
					pData += 4;
				}

				if(vertexMask & OpenGLObject::VERTEX_ATTRIBUTE_NXYZ)
				{
					float* pNormal = pMesh->GetVertexNormalArray() + 3 * i;
					memcpy(pData, pNormal, 3 * sizeof(float));
					pData += 3;
				}
			}

			LPtr<OpenGLMaterial> defaultPointMateial = new OpenGLMaterial({ 0.2f, 0.2f, 0.2f }, { 0.3f, 0.3f, 0.3f }, { 1.0f, 1.0f, 1.0f }, 32.0f);
			out = new OpenGL3DObject(id, GL_POINTS, tempArray.m_pData, pMesh->GetVertexCount(), vertexMask, defaultPointMateial);

			return true;
		}

		void OpenGLRenderData::_createDefaultPass(const Scene::LevCamera* pCamera)
		{
			if (m_passes.size() > 0)
			{
				return;
			}

			const GLchar* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
			const GLchar* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";

			std::string vertexShaderStr = _getShaderSource(pczVertexShaderPath);
			std::string fragmentShaderStr = _getShaderSource(pczFragmentShaderPath);

			auto _czpVertexShader = vertexShaderStr.c_str();
			auto _czpFragmentShader = fragmentShaderStr.c_str();

			LPtr<OpenGLShaderProgram> pShaderProgram = new OpenGLShaderProgram(&_czpVertexShader, &_czpFragmentShader, nullptr);
			LPtr<OpenGLPass> pass = new OpenGL3DPass(pShaderProgram, pCamera);
			bool inited = pass->Init();
			LEV_ASSERT(inited);
			m_passes.push_back(pass);

			bool _seted = _setCurrentPass(pass);
			LEV_ASSERT(_seted);
		}

		void OpenGLRenderData::_registerToPass(unsigned index, const std::vector<LPtr<OpenGLObject>>& pObjects)
		{
			if (!m_resourceMgr->ExistObject(index))
			{
				m_resourceMgr->AddGLObject(index, pObjects);
				_currentPass().AddGLObject(index, pObjects);
			}
			else
			{
				m_resourceMgr->ReplaceGLObject(index, pObjects);
				_currentPass().ReplaceGLObject(index, pObjects);
			}
		}

		void OpenGLRenderData::_unregisterFromPass(unsigned index)
		{
			if (!m_resourceMgr->ExistObject(index)) return;

			_currentPass().RemoveGLObject(index);
			m_resourceMgr->RemoveResource(index);
		}

		bool OpenGLRenderData::_setCurrentPass(LPtr<OpenGLPass> pPass)
		{
			LEV_ASSERT(pPass);
			m_pCurrentPass = pPass;
			return true;
		}

		bool OpenGLRenderData::_applyRenderAttribute(std::vector<LPtr<OpenGLObject>>& objects, const Scene::LevSceneRenderAttribute& render_attribute)
		{
			// Model Transform
			const Scene::LevLRAttrModelTransform* modelTransform = dynamic_cast<const Scene::LevLRAttrModelTransform*>(&render_attribute);
			if (modelTransform)
			{
				for (auto& pObject : objects)
				{
					LPtr<OpenGLUniform> pModelTransUniform = new OpenGLUniform("modelMatrix", OpenGLUniform::TYPE_FLOAT_MAT4);
					pModelTransUniform->SetData(modelTransform->GetTransform().data(), 16);
					pObject->AddUniform(pModelTransUniform);
				}

				return true;
			}

			// World Transform
			const Scene::LevLRAttrWorldTransform* worldTransform = dynamic_cast<const Scene::LevLRAttrWorldTransform*>(&render_attribute);
			if (worldTransform)
			{
				for (auto& pObject : objects)
				{
					LPtr<OpenGLUniform> pWorldTransUniform = new OpenGLUniform("worldMatrix", OpenGLUniform::TYPE_FLOAT_MAT4);
					pWorldTransUniform->SetData(worldTransform->GetTransform().data(), 16);
					pObject->AddUniform(pWorldTransUniform);
				}

				return true;
			}

			return true;
		}

		OpenGLPass & OpenGLRenderData::_currentPass()
		{
			LEV_ASSERT(m_pCurrentPass);
			return *m_pCurrentPass;
		}

		void OpenGLRenderData::Render()
		{
			for (auto& pass : m_passes)
			{
				pass->Render();
			}
		}

	}
}


