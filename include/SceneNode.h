#pragma once

#include <vector>
#include <Eigen/Dense>
#include "LPtr.h"
#include "IPickable.h"

class  AABB;

namespace Leviathan
{
	class IMesh;

	class SceneNode : public IPickable
	{
	public:
		SceneNode();
		~SceneNode();

		bool LoadModelFile(const char* szFileName);
		bool GetModelAABB(AABB& out) const;
		bool GetWorldAABB(AABB& out) const;
		bool GetWorldCoordCenter(float* out) const;
		bool Pick(float* rayPos, float* rayDir, PickInfo& pickInfo);
		const Eigen::Vector3f& GetWorldCoord() const;
		Eigen::Matrix4f GetWorldTransform() const;
		std::vector<Leviathan::LPtr<Leviathan::IMesh>> GetMeshVec() const;
		
		bool AddMesh(LPtr<IMesh> pMesh);
		void SetWorldCoord(const Eigen::Vector3f& coord);

	private:
		SceneNode(const SceneNode& rhs) = delete;
		SceneNode(const SceneNode&& rhs) = delete;
		SceneNode& operator=(const SceneNode& rhs) = delete;

		Eigen::Vector3f m_worldCoord;
		std::vector< Leviathan::LPtr<Leviathan::IMesh>> m_pMeshVec;
	};
}