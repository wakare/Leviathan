#pragma once
#include "BaseMath.h"
#include "IMesh.h"
#include "LPtr.h"
#include <vector>

namespace Leviathan
{
	class SceneNode
	{
	public:
		SceneNode();
		~SceneNode();

		bool LoadModelFile(const char* szFileName);
		std::vector<Leviathan::LPtr<Leviathan::IMesh>> GetMeshVec() const;
		bool AddMesh(LPtr<IMesh> pMesh);
		bool GetAABB(AABB& out) const;
		bool GetWorldCoordCenter(float* out) const;
		void SetWorldCoord(const Vector3f& coord);
		const Vector3f& GetWorldCoord() const;
		Matrix4f GetWorldTransform() const;

	private:
		SceneNode(const SceneNode& rhs) = delete;
		SceneNode(const SceneNode&& rhs) = delete;
		SceneNode& operator=(const SceneNode& rhs) = delete;

		Vector3f m_worldCoord;
		std::vector< Leviathan::LPtr<Leviathan::IMesh>> m_pMeshVec;
	};
}