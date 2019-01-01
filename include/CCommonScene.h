#pragma once

#include "IScene.h"
#include "PointCloud.h"
#include "LPtr.h"
#include <mutex>

struct GLFWwindow;

namespace Leviathan
{
	class SceneNode;
	class RenderWrapper;
	class TriDObjectGLPass;
	class GLShaderProgram;
	class SceneGraph;
	
	template <typename T>
	class Node;

	class CommonScene : public IScene
	{
	public:
		typedef std::function<void()> DataUpdateRequest;

		CommonScene(GLFWwindow* pRenderWindow, int width, int height);
		~CommonScene();

		// User interface
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
		void _sceneGraphUpdate(LPtr<Node<SceneNode>> pBeginNode = nullptr);

		std::string _getShaderSource(const char* pczShaderSourcePath);

		GLFWwindow* m_pGLFWWindow;
		LPtr<RenderWrapper> m_pRenderWarpper;
		LPtr<TriDObjectGLPass> m_pMeshPass;
		LPtr<GLShaderProgram> m_pShaderProgram;
		LPtr<SceneGraph> m_pSceneGraph;

		std::vector<DataUpdateRequest> m_dataUpdateResquestQueue;
		std::mutex m_dataUpdateRequestQueueLock;
	};
}