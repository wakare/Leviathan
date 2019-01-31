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
	class SceneRenderDataSet;

	template <typename T>
	class Node;

	class CommonScene : public IScene
	{
	public:
		CommonScene(GLFWwindow* pRenderWindow, int width, int height);
		~CommonScene();

		Camera& GetCamera();
		const std::vector<LPtr<GLLight>>& GetLightVec() const;
		SceneLogicDataSet& GetSceneData();
		bool Pick(unsigned x, unsigned y);
		virtual void Update();
		bool Clear();

	protected:
		void _generateWorldRayFromScreenCoord(unsigned x, unsigned y, float* rayPos, float* rayDir);
		virtual bool _firstUpdate();
		virtual bool _initSceneObject();	

		bool _initLight();
		bool _initCamera(unsigned width, unsigned height);
		void _resetCamera(float* coord = nullptr, float fDistance = -1.0f);

		int m_width;
		int m_height;
		GLFWwindow* m_pGLFWWindow;
		LPtr<Camera> m_pCamera;
		std::vector<LPtr<GLLight>> m_pLights;
		LPtr<RenderWrapper> m_pRenderWrapper;
		LPtr<TriDObjectGLPass> m_pMeshPass;
		LPtr<GLShaderProgram> m_pShaderProgram;
		LPtr<SceneLogicDataSet> m_pSceneLogicData;
		LPtr<SceneRenderDataSet> m_pSceneRenderData;
	};
}