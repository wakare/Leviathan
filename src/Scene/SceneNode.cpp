#include "SceneNode.h"
#include "IMesh.h"
#include "CFileImportFactory.h"
#include "AABB.h"

namespace Leviathan
{
	Leviathan::SceneNode::SceneNode() :
		m_worldCoord({ 0.0f, 0.0f, 0.0f })
	{

	}

	Leviathan::SceneNode::~SceneNode()
	{

	}

	bool Leviathan::SceneNode::LoadModelFile(const char* szFileName)
	{
		if (m_pMeshVec.size() > 0)
		{
			LeviathanOutStream << "[WARN] Already load file." << std::endl;
			return false;
		}

		m_pMeshVec = CFileImportFactory::GetFileImportFactory()->LoadFile(szFileName);
		if (m_pMeshVec.size() == 0)
		{
			LeviathanOutStream << "[WARN] Load file failed." << std::endl;
			return false;
		}

		return true;
	}

	std::vector<Leviathan::LPtr<Leviathan::IMesh>> Leviathan::SceneNode::GetMeshVec() const
	{
		return m_pMeshVec;
	}

	bool Leviathan::SceneNode::AddMesh(LPtr<IMesh> pMesh)
	{
		m_pMeshVec.push_back(pMesh);
		return true;
	}

	bool Leviathan::SceneNode::GetAABB(AABB& out) const
	{
		EXIT_GET_FALSE(m_pMeshVec.size() > 0);
		
		float _min[3], _max[3];
		memcpy(_min, m_pMeshVec[0]->GetAABB().min, 3 * sizeof(float));
		memcpy(_max, m_pMeshVec[0]->GetAABB().max, 3 * sizeof(float));
		for (const auto& pModelFile : m_pMeshVec)
		{
			AABB _aabb = pModelFile->GetAABB();
			for (unsigned i = 0; i < 3; i++)
			{
				if (_aabb.min[i] < _min[i])
				{
					_min[i] = _aabb.min[i];
				}
			}

			for (unsigned i = 0; i < 3; i++)
			{
				if (_aabb.max[i] > _max[i])
				{
					_max[i] = _aabb.max[i];
				}
			}
		}

		out.SetData(_min, _max);
		return true;
	}

	bool Leviathan::SceneNode::GetWorldCoordCenter(float * out) const
	{
		AABB _sceneNodeAABB; if (!GetAABB(_sceneNodeAABB)) return false; 

		Eigen::Vector4f modelCoord(_sceneNodeAABB.center); modelCoord[3] = 1.0f;
		Eigen::Vector4f worldAABBCenter = GetWorldTransform() * modelCoord;
		memcpy(out, worldAABBCenter.data(), sizeof(float) * 3);
		return true;
	}

	bool Leviathan::SceneNode::Pick(float* rayPos, float* rayDir, PickInfo& pickInfo)
	{
		//auto distance = VertexToRayDistance(rayPos, rayDir, &m_worldCoord.x);
		//if (distance < 10.0f)
		//{
		//	pickInfo.pSceneNode = this;
		//	return true;
		//}
		
		return false;
	}

	void Leviathan::SceneNode::SetWorldCoord(const Eigen::Vector3f& coord)
	{
		m_worldCoord = coord;
	}

	const Eigen::Vector3f& Leviathan::SceneNode::GetWorldCoord() const
	{
		return m_worldCoord;
	}

	Eigen::Matrix4f Leviathan::SceneNode::GetWorldTransform() const
	{
		Eigen::Matrix4f trans;
		memcpy(trans.data() + 12, m_worldCoord.data(), 3 * sizeof(float));
		return trans;
	}
}