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

	template<typename T>
	class Node;

	class SceneLogicDataSet
	{
	public:
		typedef std::function<void()> DataUpdateRequest;

		SceneLogicDataSet(LPtr<GLPass> pass);
		bool AddNode(LPtr<Node<SceneNode>> pNode);
		void Update();

		bool PushDataUpdateRequest(DataUpdateRequest request);
		bool PushDataUpdateRequest(const std::vector<DataUpdateRequest>& request);
		AABB GetAABB() const;

	private:
		std::vector<DataUpdateRequest> m_dataUpdateResquestQueue;
		std::mutex m_dataUpdateRequestQueueLock;
		LPtr<SceneGraph> m_pSceneGraph;
	};
}