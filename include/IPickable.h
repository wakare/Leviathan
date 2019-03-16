#pragma once
#include "LPtr.h"

namespace Leviathan
{
	class SceneNode;

	class PickInfo
	{
	public:
		PickInfo(): pSceneNode(nullptr) {}
		const SceneNode* pSceneNode;
	};

	class IPickable
	{
	public:
		virtual bool Pick(float* rayPos, float* rayDir, PickInfo& pickInfo) = 0;
	};
}