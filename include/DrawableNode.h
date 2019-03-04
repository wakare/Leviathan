#pragma once

#include "IDrawable.h"
#include "IMesh.h"
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
		DrawableNode(LPtr<IMesh> pModel, LPtr<T> pNode);
		DrawableNode(std::vector<LPtr<IMesh>> pModelVec, LPtr<T> pNode);
		DrawableNode(LPtr<GLObject> pGLObject, LPtr<T> pNode);
		~DrawableNode();

		bool RegisterSelfToGLPass(GLPass& refPass);
		bool RemoveSelfFromGLPass(GLPass& refPass);
		std::vector<LPtr<GLObject>> GetGLObject();

		void Accept(NodeVisitor<T>& nodeVisitor);
		void UpdateModelMatrix(const Eigen::Matrix4f& modelMatrix);
	private:
		std::vector<LPtr<GLObject>> _convertMeshToGLObject();
		bool _convertPointMeshToGLObject(LPtr<IMesh>& pMesh, LPtr<GLObject>& out);
		bool _convertTriangleMeshToGLObject(LPtr<IMesh>& pMesh, LPtr<GLObject>& out);

		bool m_bRegisted;
		std::vector<LPtr<IMesh>> m_pMeshVec;
		std::vector<LPtr<GLObject>> m_pGLObjectVec;
	};

	template<class T>
	inline Leviathan::DrawableNode<T>::DrawableNode(LPtr<IMesh> pModel, LPtr<T> pNode) :
		Node(pNode), 
		m_bRegisted(false)
	{
		m_pMeshVec.push_back(pModel);
	}

	template<class T>
	inline Leviathan::DrawableNode<T>::DrawableNode(std::vector<LPtr<IMesh>> pModelVec, LPtr<T> pNode):
		m_pMeshVec(pModelVec),
		Node<T>(pNode),
		m_bRegisted(false)
	{
	}

	template<class T>
	inline Leviathan::DrawableNode<T>::DrawableNode(LPtr<GLObject> pGLObject, LPtr<T> pNode) :
		Node<T>(pNode),
		m_bRegisted(false)
	{
		m_pGLObjectVec.push_back(pGLObject);
	}

	template<class T>
	inline void Leviathan::DrawableNode<T>::UpdateModelMatrix(const Eigen::Matrix4f& modelMatrix)
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
	inline std::vector<LPtr<GLObject>> Leviathan::DrawableNode<T>::GetGLObject()
	{
		if (m_pGLObjectVec.size() == 0)
		{
			m_pGLObjectVec = _convertMeshToGLObject();
			if (m_pGLObjectVec.size() == 0)
			{
				LeviathanOutStream << "[FATAL] Convert to GLObject failed." << std::endl;
			}
		}

		return m_pGLObjectVec;
	}

	template<class T>
	inline std::vector<LPtr<GLObject>> Leviathan::DrawableNode<T>::_convertMeshToGLObject()
	{
		std::vector<LPtr<GLObject>> result;

		for (auto pMesh : m_pMeshVec)
		{
			LPtr<GLObject> pObject = nullptr;

			if (pMesh->GetPrimitiveType() == IMesh::EPT_TRIANGLES && !_convertTriangleMeshToGLObject(pMesh, pObject))
			{
				LeviathanOutStream << "[ERROR] Convert triangle mesh to GLObject failed." << std::endl;
				continue;
			}

			if (pMesh->GetPrimitiveType() == IMesh::EPT_POINTS && !_convertPointMeshToGLObject(pMesh, pObject))
			{
				LeviathanOutStream << "[ERROR] Convert triangle mesh to GLObject failed." << std::endl;
				continue;
			}

			result.push_back(pObject);
		}

		return result;
	}

	template<class T>
	inline Leviathan::DrawableNode<T>::~DrawableNode()
	{

	}

	template<class T>
	inline void DrawableNode<T>::Accept(NodeVisitor<T>& nodeVisitor)
	{
		nodeVisitor.Apply(*this);
	}

	template<class T>
	inline bool Leviathan::DrawableNode<T>::_convertPointMeshToGLObject(LPtr<IMesh>& pMesh, Leviathan::LPtr<Leviathan::GLObject>& out)
	{
		// Check with normal
		if (pMesh->GetVertexNormalArray())
		{
			DynamicArray<float> tempArray(pMesh->GetPrimitiveCount() * 6 * sizeof(float));

			for (unsigned i = 0; i < pMesh->GetPrimitiveCount(); i++)
			{
				float* pData = tempArray.m_pData + 6 * i;
				float* pCoord = pMesh->GetVertex3DCoordArray() + 3 * i;
				float* pNormal = pMesh->GetVertexNormalArray() + 3 * i;

				memcpy(pData, pCoord, 3 * sizeof(float));
				memcpy(pData + 3, pNormal, 3 * sizeof(float));
			}

			LPtr<GLCommonMaterial> defaultPointMateial = new GLCommonMaterial({ 0.2f, 0.2f, 0.2f }, { 0.3f, 0.3f, 0.3f }, {1.0f, 1.0f, 1.0f}, 32.0f);

			out = new TriDGLObject(GL_POINTS, tempArray.m_pData, pMesh->GetPrimitiveCount(), GLObject::VERTEX_ATTRIBUTE_XYZ | GLObject::VERTEX_ATTRIBUTE_NXYZ, nullptr, defaultPointMateial);
		}
		else
		{
			out = new TriDGLObject(GL_POINTS, pMesh->GetVertex3DCoordArray(), pMesh->GetPrimitiveCount(), GLObject::VERTEX_ATTRIBUTE_XYZ);
			out->SetLightEnable(false);
		}

		return true;
	}

	template<class T>
	inline bool DrawableNode<T>::_convertTriangleMeshToGLObject(LPtr<IMesh>& pMesh, LPtr<GLObject>& out)
	{
		unsigned uVertexFloatCount = 10;
		auto pMaterial = pMesh->GetMaterial();
		bool bUseTexture = pMaterial && (pMaterial->m_textureName.length() > 0);
		unsigned uVertexTypeMask = GLObject::VERTEX_ATTRIBUTE_XYZ | GLObject::VERTEX_ATTRIBUTE_RGBA | GLObject::VERTEX_ATTRIBUTE_NXYZ;

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

		GLCommonMaterial* pCommonMaterial = nullptr;
		if (pMaterial)
		{
			pCommonMaterial = new GLCommonMaterial(pMaterial->m_ambient.data(), pMaterial->m_diffuse.data(), pMaterial->m_specular.data(), pMaterial->m_fShininess);

			PictureObject texture(pMaterial->m_textureName.c_str());
			if (texture.IsValid())
			{
				uVertexTypeMask |= GLObject::VERTEX_ATTRIBUTE_TEX;
				if (!pCommonMaterial->AddTexture2D(new GLTexture2D(texture.m_pData, texture.m_nWidth, texture.m_nHeight)))
				{
					LeviathanOutStream << "[WARN] Add texture2d failed." << std::endl;
				}
			}
		}

		out = new TriDGLObject(GL_TRIANGLES, pVertexData.m_pData, pMesh->GetVertexCount(),
			uVertexTypeMask, nullptr, pCommonMaterial, pMesh->GetPrimitiveIndexArray(), pMesh->GetPrimitiveCount() * 3);

		return true;
	}

	template<class T>
	inline bool DrawableNode<T>::RemoveSelfFromGLPass(GLPass& refPass)
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
	inline bool DrawableNode<T>::RegisterSelfToGLPass(GLPass& refPass)
	{
		if (m_bRegisted)
		{
			return true;
		}

		if (m_pGLObjectVec.size() == 0)
		{
			m_pGLObjectVec = _convertMeshToGLObject();
			if (m_pGLObjectVec.size() == 0)
			{
				LeviathanOutStream << "[FATAL] Convert to GLObject failed." << std::endl;
				return false;
			}
		}

		for (auto& pGLObject : m_pGLObjectVec)
		{
			refPass.AddGLObject(pGLObject);
		}
		
		m_bRegisted = true;

		return true;
	}
};