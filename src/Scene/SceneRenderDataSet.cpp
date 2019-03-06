#include "SceneRenderDataSet.h"
#include "RenderWrapper.h"
#include "RenderData.h"
#include "GLObject.h"
#include "Node.h"

namespace Leviathan
{
	SceneRenderDataSet::SceneRenderDataSet():
		m_renderDataTree(nullptr),
		m_bCacheNeedUpdate(true)
	{

	}

	bool SceneRenderDataSet::AddNode(LPtr<GLObject> pGLObject)
	{
		return AddNode(new Node<RenderData>(new RenderData(pGLObject)));
	}

	bool SceneRenderDataSet::AddNode(LPtr<Node<RenderData>> pRenderData)
	{
		EXIT_IF_FALSE(pRenderData);
		m_renderDataTree->AddChild(pRenderData);
	}

	std::vector<LPtr<RenderData>>& SceneRenderDataSet::GetRenderData()
	{
		if (m_bCacheNeedUpdate) _updateCache();
		m_bCacheNeedUpdate = false;
		return m_renderDataCache;
	}

	void SceneRenderDataSet::Update()
	{

	}

	bool SceneRenderDataSet::_updateCache()
	{
		return true;
	}
}