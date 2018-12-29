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
	if (m_pModelFileVec.size() > 0)
	{
		LeviathanOutStream << "[WARN] Already load file." << std::endl;
		return false;
	}

	m_pModelFileVec = CFileImportFactory::GetFileImportFactory()->LoadFile(szFileName);
	if (m_pModelFileVec.size() == 0)
	{
		LeviathanOutStream << "[WARN] Load file failed." << std::endl;
		return false;
	}

	return true;
}

std::vector<Leviathan::LPtr<Leviathan::IModelStruct>> Leviathan::SceneNode::GetModelFileVec() const
{
	return m_pModelFileVec;
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
