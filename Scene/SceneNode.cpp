#include "SceneNode.h"
#include "CFileImportFactory.h"

Leviathan::SceneNode::SceneNode():
	m_worldCoord({0.0f, 0.0f, 0.0f}),
	m_pModelFile(nullptr)
{

}

Leviathan::SceneNode::~SceneNode()
{

}

bool Leviathan::SceneNode::LoadModelFile(const char* szFileName)
{
	if (m_pModelFile)
	{
		LeviathanOutStream << "[WARN] Already load file." << std::endl;
		return false;
	}

	m_pModelFile = CFileImportFactory::GetFileImportFactory()->LoadFile(szFileName);
	if (!m_pModelFile)
	{
		LeviathanOutStream << "[WARN] Load file failed." << std::endl;
		return false;
	}

	return true;
}

Leviathan::LPtr<Leviathan::IModelStruct> Leviathan::SceneNode::GetModelFile() const
{
	return m_pModelFile;
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
