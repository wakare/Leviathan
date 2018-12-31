#include "SceneNode.h"
#include "CFileImportFactory.h"

Leviathan::SceneNode::SceneNode():
	m_worldCoord({0.0f, 0.0f, 0.0f})
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
	AABB _sceneNodeAABB;

	if (m_pMeshVec.size() == 0)
	{
		return false;
	}

	for (const auto& pModelFile : m_pMeshVec)
	{
		if (!_sceneNodeAABB.HasSet())
		{
			_sceneNodeAABB = pModelFile->GetAABB();
		}

		else
		{
			_sceneNodeAABB = _sceneNodeAABB.Merge(pModelFile->GetAABB());
		}
	}

	out = _sceneNodeAABB;
	return true;
}

bool Leviathan::SceneNode::GetWorldCoordCenter(float * out) const
{
	AABB _sceneNodeAABB;
	if (!GetAABB(_sceneNodeAABB))
	{
		return false;
	}

	float _modelAABBCenter[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_sceneNodeAABB.GetAABBCenter(_modelAABBCenter);
	
	auto worldAABBCenter = Vector4f(_modelAABBCenter) * GetWorldTransform();
	memcpy(out, worldAABBCenter.GetData(), sizeof(float) * 3);

	return true;
}

void Leviathan::SceneNode::SetWorldCoord(const Vector3f& coord)
{
	m_worldCoord = coord;
}

const Vector3f& Leviathan::SceneNode::GetWorldCoord() const
{
	return m_worldCoord;
}

Matrix4f Leviathan::SceneNode::GetWorldTransform() const
{
	return Matrix4f::GetTranslateMatrix(m_worldCoord.x, m_worldCoord.y, m_worldCoord.z);
}
