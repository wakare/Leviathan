#pragma once

#include "IScene.h"
#include "PointCloud.h"
#include "LPtr.h"
#include <mutex>
#include <vector>

struct GLFWwindow;

namespace Leviathan
{
	class SceneNode;
	class RenderWrapper;
	class TriDObjectGLPass;
	class GLShaderProgram;
	class SceneGraph;
	class GLCamera;
	class GLLight;

	template <typename T>
	class Node;

	class CommonScene : public IScene
	{
	public:
		typedef std::function<void()> DataUpdateRequest;

		CommonScene(GLFWwindow* pRenderWindow, int width, int height);
		~CommonScene();

		// User interface
		GLCamera& GetCamera();
		const std::vector<LPtr<GLLight>>& GetLightVec() const;

		void UpdatePointCloud(PointCloudf& pPoints);
		bool PushDataUpdateRequest(DataUpdateRequest request);
		bool PushDataUpdateRequest(std::vector<DataUpdateRequest> request);
		
		void Update();

	private:
		CommonScene(const CommonScene& rhs);
		CommonScene(const CommonScene&& rhs) = delete;
		CommonScene& operator=(const CommonScene& rhs) = delete;

		bool _dataUpdate();
		bool _firstUpdate();
		bool _initSceneObject();
		bool _initShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath);		
		bool _initCamera(unsigned width, unsigned height);
		bool _initLight();
		void _resetCamera(float* coord = nullptr, float fDistance = -1.0f);
		void _sceneGraphUpdate(LPtr<Node<SceneNode>> pBeginNode = nullptr, bool bResursive = true);

		std::string _getShaderSource(const char* pczShaderSourcePath);

		GLFWwindow* m_pGLFWWindow;
		LPtr<GLCamera> m_pCamera;
		std::vector<LPtr<GLLight>> m_pLights;
		LPtr<RenderWrapper> m_pRenderWarpper;
		LPtr<TriDObjectGLPass> m_pMeshPass;
		LPtr<GLShaderProgram> m_pShaderProgram;
		LPtr<SceneGraph> m_pSceneGraph;

		std::vector<DataUpdateRequest> m_dataUpdateResquestQueue;
		std::mutex m_dataUpdateRequestQueueLock;
	};
}