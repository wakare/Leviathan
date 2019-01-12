#pragma once
#include "LPtr.h"

namespace Leviathan
{
	class RenderData;
	class RenderWrapper;

	template<typename T>
	class Node;

	class SceneRenderDataSet
	{
	public:
		SceneRenderDataSet();

	private:
		LPtr<Node<RenderData>> m_renderDataTree;
		LPtr<RenderWrapper> m_pRenderWrapper;
	};
}