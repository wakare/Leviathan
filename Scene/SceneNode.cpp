#include "SceneNode.h"

Leviathan::SceneNode::SceneNode()
{

}

void Leviathan::SceneNode::SetModelMatrix(Matrix4f& modelMatrix)
{
	m_modelMatrix = modelMatrix;
}

const Matrix4f& Leviathan::SceneNode::GetModelMatrix() const
{
	return m_modelMatrix;
}
