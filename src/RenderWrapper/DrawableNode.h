#pragma once
#include "IDrawable.h"
#include "IModelStruct.h"
#include "Node.h"
#include "GLCommonMaterial.h"
#include "PictureObject.h"
#include "DynamicArray.h"
#include "GeometryCalculator.h"
#include "TriDGLObject.h"

namespace Leviathan
{
	template<class T>
	class DrawableNode : public IDrawable, public Node<T>
	{
	public:
		DrawableNode(LPtr<IModelStruct> pModel, LPtr<T> pNode);
		DrawableNode(std::vector<LPtr<IModelStruct>> pModelVec, LPtr<T> pNode);
		DrawableNode(LPtr<GLObject> pGLObject, LPtr<T> pNode);
		~DrawableNode();

		bool RegisterSelfToGLPass(GLPass& refPass);
		bool RemoveSelfFromGLPass(GLPass& refPass);
		std::vector<LPtr<GLObject>> GetGLObject();

		void Accept(NodeVisitor<T>& nodeVisitor);
		void UpdateModelMatrix(const Matrix4f& modelMatrix);
	private:
		std::vector<LPtr<GLObject>> _convertModelStructToGLObject(bool bUseIndex = true);

		std::vector<LPtr<IModelStruct>> m_pModelStructVec;
		std::vector<LPtr<GLObject>> m_pGLObjectVec;
	};

	template<class T>
	Leviathan::DrawableNode<T>::DrawableNode(std::vector<LPtr<IModelStruct>> pModelVec, LPtr<T> pNode):
		m_pModelStructVec(pModelVec),
		Node<T>(pNode)
	{
		
	}

	template<class T>
	void Leviathan::DrawableNode<T>::UpdateModelMatrix(const Matrix4f& modelMatrix)
	{
		if (!m_pGLObjectVec.size() == 0)
		{
			LeviathanOutStream << "[ERROR] No object need update." << std::endl;
			return;
		}

		for (auto pGLObject : m_pGLObjectVec)
		{
			pGLObject->SetModelMatrix(modelMatrix);
		}
	}

	template<class T>
	Leviathan::DrawableNode<T>::DrawableNode(LPtr<GLObject> pGLObject, LPtr<T> pNode):
		Node<T>(pNode)
	{
		m_pGLObjectVec.push_back(pGLObject);
	}

	template<class T>
	std::vector<LPtr<GLObject>> Leviathan::DrawableNode<T>::GetGLObject()
	{
		if (m_pGLObjectVec.size() == 0)
		{
			m_pGLObjectVec = _convertModelStructToGLObject();
			if (m_pGLObjectVec.size() == 0)
			{
				LeviathanOutStream << "[FATAL] Convert to GLObject failed." << std::endl;
			}
		}

		return m_pGLObjectVec;
	}

	template<class T>
	std::vector<LPtr<GLObject>> Leviathan::DrawableNode<T>::_convertModelStructToGLObject(bool bUseIndex)
	{
		std::vector<LPtr<GLObject>> result;

		for (auto pModelStruct : m_pModelStructVec)
		{
			unsigned uVertexFloatCount = 10;
			auto pMaterial = pModelStruct->GetMaterial();
			bool bUseTexture = !(pMaterial == nullptr);
			if (bUseTexture)
			{
				uVertexFloatCount += 2;
			}

			DynamicArray<float> glData(pModelStruct->GetTriangleCount() * 3 * uVertexFloatCount * sizeof(float));

			static float defaultColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
			bool bDefaultColor = false;

			auto color = pModelStruct->GetVertexColorArray();
			if (!color)
			{
				bDefaultColor = true;
			}

			if (bUseIndex)
			{
				std::map<unsigned, std::vector<Vector3f>> vertexNormalVec;

				// Calculate vertex normal
				for (unsigned i = 0; i < pModelStruct->GetTriangleCount(); i++)
				{
					unsigned* vertexIndex = pModelStruct->GetTriangleIndexArray() + 3 * i;
					float* vertices[3] =
					{
						pModelStruct->GetVertex3DCoordArray() + 3 * vertexIndex[0],
						pModelStruct->GetVertex3DCoordArray() + 3 * vertexIndex[1],
						pModelStruct->GetVertex3DCoordArray() + 3 * vertexIndex[2],
					};

					float fNormal[3];
					GeometryCalculator::CalNormal(vertices[0], vertices[1], vertices[2], fNormal);

					vertexNormalVec[vertexIndex[0]].push_back(fNormal);
					vertexNormalVec[vertexIndex[1]].push_back(fNormal);
					vertexNormalVec[vertexIndex[2]].push_back(fNormal);
				}

				DynamicArray<float> pVertexData(pModelStruct->GetVertexCount() * uVertexFloatCount * sizeof(float));

				for (unsigned i = 0; i < pModelStruct->GetVertexCount(); i++)
				{
					float* pData = pVertexData.m_pData + i * uVertexFloatCount;
					memcpy(pData, pModelStruct->GetVertex3DCoordArray() + 3 * i, sizeof(float) * 3);

					memcpy(pData + 3, color ? color : defaultColor, sizeof(float) * 4);

					// Calculate average normal
					Vector3f normal(0.0f, 0.0f, 0.0f);
					for (auto& subNormal : vertexNormalVec[i])
					{
						normal.x += subNormal.x;
						normal.y += subNormal.y;
						normal.z += subNormal.z;
					}

					normal.x /= vertexNormalVec[i].size();
					normal.y /= vertexNormalVec[i].size();
					normal.z /= vertexNormalVec[i].size();

					memcpy(pData + 7, &normal.x, sizeof(float) * 3);

					// Texture coord
					if (bUseTexture)
					{
						auto pTextureData = pModelStruct->GetVertexTexArray() + 2 * i;
						if (!pTextureData)
						{
							LeviathanOutStream << "[ERROR] Can not get texture data" << std::endl;
						}

						memcpy(pData + 10, pTextureData, sizeof(float) * 2);
					}
				}

				auto uVertexTypeMask = GLObject::VERTEX_ATTRIBUTE_XYZ | GLObject::VERTEX_ATTRIBUTE_RGBA | GLObject::VERTEX_ATTRIBUTE_NXYZ;
				
				GLCommonMaterial* pCommonMaterial = nullptr;
				if (pMaterial)
				{
					PictureObject texture(pMaterial->m_textureName.c_str());
					if (texture.IsValid())
					{
						uVertexTypeMask |= GLObject::VERTEX_ATTRIBUTE_TEX;
						pCommonMaterial = new GLCommonMaterial(&pMaterial->m_ambient.x, &pMaterial->m_diffuse.x, &pMaterial->m_specular.x, pMaterial->m_fShininess);
						if (!pCommonMaterial->AddTexture2D(new GLTexture2D(texture.m_pData, texture.m_nWidth, texture.m_nHeight)))
						{
							LeviathanOutStream << "[WARN] Add texture2d failed." << std::endl;
						}
					}
				}

				result.push_back( new TriDGLObject(GL_TRIANGLES, pVertexData.m_pData, pModelStruct->GetVertexCount(), 
				uVertexTypeMask, nullptr, pCommonMaterial, pModelStruct->GetTriangleIndexArray(), pModelStruct->GetTriangleCount() * 3));
			}

			else
			{
				// Only use vertex buffer
				for (unsigned i = 0; i < pModelStruct->GetTriangleCount(); i++)
				{
					unsigned* vertexIndex = pModelStruct->GetTriangleIndexArray() + 3 * i;
					float* vertices[3];

					for (unsigned j = 0; j < 3; j++)
					{
						float* vertexCoord = pModelStruct->GetVertex3DCoordArray() + 3 * vertexIndex[j];
						vertices[j] = vertexCoord;
						memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j, vertexCoord, sizeof(float) * 3);

						if (bDefaultColor)
						{
							memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 3, defaultColor, sizeof(float) * 4);
						}
						else
						{
							memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 3, color + 4 * i, sizeof(float) * 4);
						}
					}

					float fNormal[3];
					GeometryCalculator::CalNormal(vertices[0], vertices[1], vertices[2], fNormal);

					for (unsigned j = 0; j < 3; j++)
					{
						memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 7, fNormal, sizeof(float) * 3);
					}
				}

				result.push_back(new TriDGLObject(GL_TRIANGLES, glData.m_pData, pModelStruct->GetTriangleCount() * 3, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ));
			}
		}

		return result;
	}

	template<class T>
	Leviathan::DrawableNode<T>::DrawableNode(LPtr<IModelStruct> pModel, LPtr<T> pNode):
		Node(pNode)
	{
		m_pModelStructVec.push_back(pModel);
	}

	template<class T>
	Leviathan::DrawableNode<T>::~DrawableNode()
	{

	}

	template<class T>
	void DrawableNode<T>::Accept(NodeVisitor<T>& nodeVisitor)
	{
		nodeVisitor.Apply(*this);
	}

	template<class T>
	bool DrawableNode<T>::RemoveSelfFromGLPass(GLPass& refPass)
	{
		if (m_pGLObjectVec.size() == 0)
		{
			LeviathanOutStream << "[FATAL] Delete self before init." << std::endl;
			return false;
		}

		for (auto pGLObject : m_pGLObjectVec)
		{
			refPass.DelGLObject(pGLObject);
		}

		return true;
	}

	template<class T>
	bool DrawableNode<T>::RegisterSelfToGLPass(GLPass& refPass)
	{
		if (m_pGLObjectVec.size() == 0)
		{
			m_pGLObjectVec = _convertModelStructToGLObject();
			if (m_pGLObjectVec.size() == 0)
			{
				LeviathanOutStream << "[FATAL] Convert to GLObject failed." << std::endl;
				return false;
			}
		}

		for (auto pGLObject : m_pGLObjectVec)
		{
			refPass.AddGLObject(pGLObject);
		}
		
		return true;
	}
};