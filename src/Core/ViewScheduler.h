#pragma once

#include "LevScheduler.h"
#include "TriDScene.h"
#include "View.h"

namespace Leviathan 
{
	class IMesh;

	class ViewScheduler : public LevScheduler<int>
	{
	public:
		ViewScheduler();
		void Update();
		void SetDone();

		bool Init(int width, int height, int parentHandle);

		int GetWindowHandle();

		bool LoadMeshFile(const char* file);
		bool LoadPointCloudFile(const char* file, LPtr<Scene::LevSceneNode>& out);
		bool AddNode(LPtr<Scene::LevSceneNode> pNode);
		bool LoadCustomMesh(LPtr<IMesh> pMesh);

	private:
		bool m_done;
		//std::unique_ptr<View> m_pView;
		std::unique_ptr<View> m_pView;
	};
}