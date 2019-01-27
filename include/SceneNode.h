#pragma once

#include <vector>
#include "BaseMath.h"
#include "LPtr.h"
#include "IPickable.h"

namespace Leviathan
{
	class IMesh;
	class AABB;

	class SceneNode : public IPickable
	{
	public:
		SceneNode();
		~SceneNode();

		bool LoadModelFile(const char* szFileName);
		bool GetAABB(AABB& out) const;
		bool GetWorldCoordCenter(float* out) const;
		bool Pick(float* rayPos, float* rayDir, PickInfo& pickInfo);
		const Vector3f& GetWorldCoord() const;
		Matrix4f GetWorldTransform() const;
		std::vector<Leviathan::LPtr<Leviathan::IMesh>> GetMeshVec() const;
		
		bool AddMesh(LPtr<IMesh> pMesh);
		void SetWorldCoord(const Vector3f& coord);

	private:
		SceneNode(const SceneNode& rhs) = delete;
		SceneNode(const SceneNode&& rhs) = delete;
		SceneNode& operator=(const SceneNode& rhs) = delete;

		Vector3f m_worldCoord;
		std::vector< Leviathan::LPtr<Leviathan::IMesh>> m_pMeshVec;
	};
}