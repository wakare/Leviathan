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

	bool Leviathan::SceneNode::GetModelAABB(AABB& out) const
	{
		EXIT_IF_FALSE(m_pMeshVec.size() > 0);
		
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

	bool SceneNode::GetWorldAABB(AABB & out) const
	{
		AABB modelAABB; GetModelAABB(modelAABB);
		float min[3], max[3];
		
		memcpy(min, modelAABB.center, 3 * sizeof(float));
		memcpy(max, modelAABB.center, 3 * sizeof(float));

		for (unsigned i = 0; i < 8; i++)
		{
			bool bPositiveX = i & 0x1; 
			bool bPositiveY = i & 0x2;
			bool bPositiveZ = i & 0x4;

			float coord[3] =
			{
				(bPositiveX) ? modelAABB.max[0] : modelAABB.min[0],
				(bPositiveY) ? modelAABB.max[1] : modelAABB.min[1],
				(bPositiveZ) ? modelAABB.max[2] : modelAABB.min[2], 
			};

			Eigen::Vector4f worldCoord(coord[0], coord[1], coord[2], 1.0f);
			worldCoord = GetWorldTransform() * worldCoord;

			if (worldCoord[0] < min[0]) min[0] = worldCoord[0];
			if (worldCoord[1] < min[1]) min[1] = worldCoord[1];
			if (worldCoord[2] < min[2]) min[2] = worldCoord[2];

			if (worldCoord[0] > max[0]) max[0] = worldCoord[0];
			if (worldCoord[1] > max[1]) max[1] = worldCoord[1];
			if (worldCoord[2] > max[2]) max[2] = worldCoord[2];
		}

		out.SetData(min, max);
		return true;
	}

	bool Leviathan::SceneNode::GetWorldCoordCenter(float * out) const
	{
		AABB _sceneNodeAABB; if (!GetModelAABB(_sceneNodeAABB)) return false; 

		Eigen::Vector4f modelCoord(_sceneNodeAABB.center); modelCoord[3] = 1.0f;
		Eigen::Vector4f worldAABBCenter = GetWorldTransform() * modelCoord;
		memcpy(out, worldAABBCenter.data(), sizeof(float) * 3);
		return true;
	}

	bool Leviathan::SceneNode::Pick(float* rayPos, float* rayDir, PickInfo& pickInfo)
	{
		/*auto distance = VertexToRayDistance(rayPos, rayDir, &m_worldCoord.x);
		if (distance < 10.0f)
		{
			pickInfo.pSceneNode = this;
			return true;
		}*/
		
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
		Eigen::Matrix4f trans = Eigen::Matrix4f::Identity();
		memcpy(trans.data() + 12, m_worldCoord.data(), 3 * sizeof(float));
		return trans;
	}
}