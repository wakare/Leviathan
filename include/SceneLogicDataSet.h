#pragma once
#include "LPtr.h"
#include <mutex>
#include <vector>

namespace Leviathan
{
	class SceneGraph;
	class SceneNode;
	class GLPass;
	class AABB;
	class GLLight;
	class PickInfo;

	template<typename T>
	class Node;

	class SceneLogicDataSet
	{
	public:
		typedef std::function<void()> DataUpdateRequest;

		SceneLogicDataSet(LPtr<GLPass> pass);
		bool AddNode(LPtr<Node<SceneNode>> pNode);
		bool Pick(float* rayPos, float* rayDir, PickInfo& info);
		void Update();

		bool PushDataUpdateRequest(DataUpdateRequest request);
		bool PushDataUpdateRequest(const std::vector<DataUpdateRequest>& request);
		bool ClearAllData();
		AABB GetAABB() const;

	private:
		std::vector<DataUpdateRequest> m_dataUpdateResquestQueue;
		std::mutex m_dataUpdateRequestQueueLock;
		LPtr<GLPass> m_pGLPass;
		LPtr<SceneGraph> m_pSceneGraph;
	};
}