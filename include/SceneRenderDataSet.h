#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	class GLObject;
	class RenderData;
	class RenderWrapper;

	template<typename T>
	class Node;

	class SceneRenderDataSet
	{
	public:
		SceneRenderDataSet();
		bool AddNode(LPtr<GLObject> pGLObject);	
		bool AddNode(LPtr<Node<RenderData>> pRenderDataNode);
		std::vector<LPtr<RenderData>>& GetRenderData();
		void Update();
		
	private:
		bool _updateCache();
		bool m_bCacheNeedUpdate;
		std::vector<LPtr<RenderData>> m_renderDataCache;
		LPtr<Node<RenderData>> m_renderDataTree;
	};
}