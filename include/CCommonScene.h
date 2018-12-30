#pragma once
#include "IScene.h"
#include "GLCamera.h"
#include "RenderWrapper.h"
#include "TriDObjectGLPass.h"
#include "TriDGLObject.h"
#include "GLShaderProgram.h"
#include "LPtr.h"
#include "IModelStruct.h"
#include "SceneGraph.h"
#include "SceneBase.h"
#include "PointCloud.h"

namespace Leviathan
{
	class CommonScene : public IScene
	{
	public:
		CommonScene(GLFWwindow* pRenderWindow, int width, int height);
		~CommonScene();

		// User interface
		void UpdatePointCloud(PointCloudf& pPoints);
		void Update();

	private:
		CommonScene(const CommonScene& rhs);
		CommonScene(const CommonScene&& rhs) = delete;
		CommonScene& operator=(const CommonScene& rhs) = delete;

		void _firstUpdate();
		bool _initSceneObject();
		bool _initShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath);		
		bool _initCamera(unsigned width, unsigned height);
		bool _initLight();
		void _resetCamera();
		void _sceneGraphUpdate(LPtr<Node<SceneNode>> pBeginNode = nullptr);

		std::string _getShaderSource(const char* pczShaderSourcePath);

		GLFWwindow* m_pGLFWWindow;
		LPtr<RenderWrapper> m_pRenderWarpper;
		LPtr<TriDObjectGLPass> m_pMeshPass;
		LPtr<GLShaderProgram> m_pShaderProgram;
		LPtr<SceneGraph> m_pSceneGraph;
	};
}