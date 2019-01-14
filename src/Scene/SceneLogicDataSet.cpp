#include "SceneLogicDataSet.h"
#include "SceneGraph.h"
#include "Node.h"
#include "SceneNode.h"
#include "AABB.h"
#include "GLPass.h"

namespace Leviathan
{
	SceneLogicDataSet::SceneLogicDataSet(LPtr<GLPass> pass):
		m_pGLPass(pass)
	{
		m_pSceneGraph = new SceneGraph(pass);
	}

	bool SceneLogicDataSet::AddNode(LPtr<Node<SceneNode>> pNode)
	{
		return m_pSceneGraph->AddNode(pNode);
	}

	void SceneLogicDataSet::Update()
	{
		m_pSceneGraph->Update();
		m_dataUpdateRequestQueueLock.lock();
		for (auto& request : m_dataUpdateResquestQueue)
		{
			request();
		}
		m_dataUpdateResquestQueue.clear();
		m_dataUpdateRequestQueueLock.unlock();
	}

	bool SceneLogicDataSet::PushDataUpdateRequest(DataUpdateRequest request)
	{
		m_dataUpdateRequestQueueLock.lock();
		m_dataUpdateResquestQueue.push_back(request);
		m_dataUpdateRequestQueueLock.unlock();

		return true;
	}

	bool SceneLogicDataSet::PushDataUpdateRequest(const std::vector<DataUpdateRequest>& request)
	{
		m_dataUpdateRequestQueueLock.lock();
		m_dataUpdateResquestQueue.insert(m_dataUpdateResquestQueue.end(), request.begin(), request.end());
		m_dataUpdateRequestQueueLock.unlock();

		return true;
	}

	bool SceneLogicDataSet::ClearAllData()
	{
		m_pGLPass->ClearGLObject();
		m_pSceneGraph.Reset(new SceneGraph(m_pGLPass));
		return true;
	}

	Leviathan::AABB SceneLogicDataSet::GetAABB() const
	{
		return m_pSceneGraph->GetAABB();
	}

}