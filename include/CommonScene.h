#pragma once

#include <mutex>
#include <vector>
#include "IScene.h"
#include "PointCloud.h"
#include "LPtr.h"

struct GLFWwindow;

namespace Leviathan
{
	class SceneNode;
	class RenderWrapper;
	class TriDObjectGLPass;
	class GLShaderProgram;
	class SceneGraph;
	class Camera;
	class GLLight;
	
	template <typename T>
	class Node;

	class CommonScene : public IScene
	{
	public:
		typedef std::function<void()> DataUpdateRequest;

		CommonScene(GLFWwindow* pRenderWindow, int width, int height);
		~CommonScene();

		Camera& GetCamera();
		const std::vector<LPtr<GLLight>>& GetLightVec() const;

		bool PushDataUpdateRequest(DataUpdateRequest request);
		bool PushDataUpdateRequest(const std::vector<DataUpdateRequest>& request);
		bool AddNode(LPtr<Node<SceneNode>> pNode);
		SceneLogicDataSet& GetSceneData();
		virtual void Update();

	protected:
		virtual bool _firstUpdate();
		virtual bool _initSceneObject();	
		bool _initCamera(unsigned width, unsigned height);
		bool _initLight();
		void _resetCamera(float* coord = nullptr, float fDistance = -1.0f);

		GLFWwindow* m_pGLFWWindow;
		LPtr<Camera> m_pCamera;
		std::vector<LPtr<GLLight>> m_pLights;
		LPtr<RenderWrapper> m_pRenderWarpper;
		LPtr<TriDObjectGLPass> m_pMeshPass;
		LPtr<GLShaderProgram> m_pShaderProgram;
		LPtr<SceneLogicDataSet> m_pSceneLogicData;
	};
}