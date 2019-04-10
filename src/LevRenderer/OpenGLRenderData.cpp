#include "OpenGLRenderData.h"
#include "IMesh.h"
#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevMeshObject.h"
#include "OpenGL3DObject.h"
#include "DynamicArray.h"
#include "GeometryCalculator.h"
#include "OpenGLMaterial.h"
#include "PictureObject.h"
#include "GLTexture.h"
#include "OpenGLTexture.h"
#include "OpenGL3DPass.h"
#include "OpenGLShaderProgram.h"

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
		{
		}
	
		void OpenGLRenderData::UpdateInputData(const Scene::LevSceneData & sceneData)
		{
			auto& sceneTree = sceneData.GetSceneTree();

			auto& sceneObjects = sceneTree.GetNodes();

			static bool bFirst = true;

			if (bFirst)
			{
				//Find camera
				for (const auto& sceneObject : sceneObjects)
				{
					const auto& objData = *sceneObject->GetNodeData();
					if ((objData.GetType() | Scene::LSOT_CAMERA) > 0)
					{
						auto pCamera = dynamic_cast<const Scene::LevCamera*>(&objData);
						_createDefaultPass(pCamera);
						break;
					}
				}

				bFirst = false;
			}
			
			LEV_ASSERT(m_passes.size() > 0);

			for (const auto& sceneObject : sceneObjects)
			{
				const auto& objData = *sceneObject->GetNodeData();
				if ((objData.GetType() & Scene::LSOT_UNRENDERABLE) > 0)
				{
					continue;
				}

				auto& objDesc = objData.GetObjDesc();
				if (objDesc.GetType() != ELSOD_MESH)
				{
					continue;
				}

				// TODO: change style to get mesh data?
				const Scene::LevMeshObject* pMesh = dynamic_cast<const Scene::LevMeshObject*>(&objDesc);
				if (!pMesh)
				{
					continue;
				}

				std::vector<LPtr<OpenGLObject>> pObjects;
				LEV_ASSERT(ConvertMeshToGLObject(*pMesh, pObjects));

				for (auto& pObject : pObjects)
				{
					_registerToPass(pObject);
				}
				
				auto& attributes = objData.GetObjAttributes();
				// TODO: Handle different attributes
			}
		}

		bool OpenGLRenderData::ConvertMeshToGLObject(const Scene::LevMeshObject& mesh, std::vector<LPtr<OpenGLObject>>& out)
		{
			out.clear();

			for (auto pMesh : mesh.GetMesh())
			{
				LPtr<OpenGLObject> pObject = nullptr;

				if (pMesh->GetPrimitiveType() == IMesh::EPT_TRIANGLES && !_convertTriangleMeshToGLObject(pMesh, pObject))
				{
					LeviathanOutStream << "[ERROR] Convert triangle mesh to GLObject failed." << std::endl;
					continue;
				}

				/*if (pMesh->GetPrimitiveType() == IMesh::EPT_POINTS && !_convertPointMeshToGLObject(pMesh, pObject))
				{
					LeviathanOutStream << "[ERROR] Convert triangle mesh to GLObject failed." << std::endl;
					continue;
				}*/

				out.push_back(pObject);
			}

			return true;
		}

		bool OpenGLRenderData::_convertTriangleMeshToGLObject(LPtr<IMesh> pMesh, LPtr<OpenGLObject>& out)
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

			out = new OpenGL3DObject(GL_TRIANGLES, pVertexData.m_pData, pMesh->GetVertexCount(),
				uVertexTypeMask, nullptr, pGLMaterial, pMesh->GetPrimitiveIndexArray(), pMesh->GetPrimitiveCount() * 3);

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
			LEV_ASSERT(pass->Init());
			m_passes.push_back(pass);
		}

		void OpenGLRenderData::_registerToPass(LPtr<OpenGLObject> pObject)
		{
			if (m_passes.size() == 0)
			{
				return;
			}

			m_passes[0]->AddGLObject(pObject);
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


