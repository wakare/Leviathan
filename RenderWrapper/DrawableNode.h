#pragma once
#include "IDrawable.h"
#include "IModelStruct.h"
#include "Node.h"

namespace Leviathan
{
	template<class T>
	class DrawableNode : public IDrawable, public Node<T>
	{
	public:
		DrawableNode(LPtr<IModelStruct> pModel, LPtr<T> pNode);
		DrawableNode(LPtr<GLObject> pGLObject, LPtr<T> pNode);
		~DrawableNode();

		bool RegisterSelfToGLPass(GLPass& refPass);
		bool RemoveSelfFromGLPass(GLPass& refPass);
		LPtr<GLObject> GetGLObject();

		void Accept(NodeVisitor<T>& nodeVisitor);
		void UpdateModelMatrix(const Matrix4f& modelMatrix);
	private:
		LPtr<GLObject> _convertModelStructToGLObject(bool bUseIndex = true);

		LPtr<IModelStruct> m_pModelStruct;
		LPtr<GLObject> m_pGLObject;
	};

	template<class T>
	void Leviathan::DrawableNode<T>::UpdateModelMatrix(const Matrix4f& modelMatrix)
	{
		if (!m_pGLObject)
		{
			LeviathanOutStream << "[ERROR] No object need update." << std::endl;
			return;
		}

		m_pGLObject->SetModelMatrix(modelMatrix);
	}

	template<class T>
	Leviathan::DrawableNode<T>::DrawableNode(LPtr<GLObject> pGLObject, LPtr<T> pNode):
		Node<T>(pNode),
		m_pGLObject(pGLObject),
		m_pModelStruct(nullptr)
	{

	}

	template<class T>
	Leviathan::LPtr<Leviathan::GLObject> Leviathan::DrawableNode<T>::GetGLObject()
	{
		if (!m_pGLObject)
		{
			m_pGLObject = _convertModelStructToGLObject();
			if (!m_pGLObject)
			{
				LeviathanOutStream << "[FATAL] Convert to GLObject failed." << std::endl;
			}
		}

		return m_pGLObject;
	}

	template<class T>
	Leviathan::LPtr<Leviathan::GLObject> Leviathan::DrawableNode<T>::_convertModelStructToGLObject(bool bUseIndex)
	{
		const unsigned uVertexFloatCount = 10;

		DynamicArray<float> glData(m_pModelStruct->GetTriangleCount() * 3 * uVertexFloatCount * sizeof(float));

		static float defaultColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		bool bDefaultColor = false;

		auto color = m_pModelStruct->GetVertexColorArray();
		if (!color)
		{
			bDefaultColor = true;
		}

		if (bUseIndex)
		{
			std::map<unsigned, std::vector<Vector3f>> vertexNormalVec;

			// Calculate vertex normal
			for (unsigned i = 0; i < m_pModelStruct->GetTriangleCount(); i++)
			{
				unsigned* vertexIndex = m_pModelStruct->GetTriangleIndexArray() + 3 * i;
				float* vertices[3] = 
				{
					m_pModelStruct->GetVertex3DCoordArray() + 3 * vertexIndex[0],
					m_pModelStruct->GetVertex3DCoordArray() + 3 * vertexIndex[1],
					m_pModelStruct->GetVertex3DCoordArray() + 3 * vertexIndex[2],
				};

				float fNormal[3];
				GeometryCalculator::CalNormal(vertices[0], vertices[1], vertices[2], fNormal);

				vertexNormalVec[vertexIndex[0]].push_back(fNormal);
				vertexNormalVec[vertexIndex[1]].push_back(fNormal);
				vertexNormalVec[vertexIndex[2]].push_back(fNormal);
			}

			DynamicArray<float> pVertexData(m_pModelStruct->GetVertexCount() * uVertexFloatCount * sizeof(float));
			
			for (unsigned i = 0; i < m_pModelStruct->GetVertexCount(); i++)
			{
				float* pData = pVertexData.m_pData + i * uVertexFloatCount;
				memcpy(pData, m_pModelStruct->GetVertex3DCoordArray() + 3 * i, sizeof(float) * 3);

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
			}

			return new TriDGLObject(GL_TRIANGLES, pVertexData.m_pData, m_pModelStruct->GetVertexCount(), GLObject::VERTEX_ATTRIBUTE_XYZ | GLObject::VERTEX_ATTRIBUTE_RGBA | GLObject::VERTEX_ATTRIBUTE_NXYZ, nullptr, nullptr, m_pModelStruct->GetTriangleIndexArray(), m_pModelStruct->GetTriangleCount() * 3);
		}

		else
		{
			// Only use vertex buffer
			for (unsigned i = 0; i < m_pModelStruct->GetTriangleCount(); i++)
			{
				unsigned* vertexIndex = m_pModelStruct->GetTriangleIndexArray() + 3 * i;
				float* vertices[3];

				for (unsigned j = 0; j < 3; j++)
				{
					float* vertexCoord = m_pModelStruct->GetVertex3DCoordArray() + 3 * vertexIndex[j];
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

			return new TriDGLObject(GL_TRIANGLES, glData.m_pData, m_pModelStruct->GetTriangleCount() * 3, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ);
		}
	}

	template<class T>
	Leviathan::DrawableNode<T>::DrawableNode(LPtr<IModelStruct> pModel, LPtr<T> pNode):
		Node(pNode),
		m_pGLObject(nullptr),
		m_pModelStruct(pModel)
	{
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
		if (!m_pGLObject)
		{
			LeviathanOutStream << "[FATAL] Delete self before init." << std::endl;
			return false;
		}

		refPass.DelGLObject(m_pGLObject);
		return true;
	}

	template<class T>
	bool DrawableNode<T>::RegisterSelfToGLPass(GLPass& refPass)
	{
		if (!m_pGLObject)
		{
			m_pGLObject = _convertModelStructToGLObject();
			if (!m_pGLObject)
			{
				LeviathanOutStream << "[FATAL] convert to GLObject failed." << std::endl;
				return false;
			}
		}

		refPass.AddGLObject(m_pGLObject);
		return true;
	}
};