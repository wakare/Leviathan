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

namespace Leviathan
{
	class CCommonScene : public IScene
	{
	public:
		CCommonScene(GLFWwindow* pRenderWindow, int width, int height);
		~CCommonScene();

		// User interface
		void UpdatePointCloud(LPtr<IModelStruct> pPoints);
		void Update();

	private:
		CCommonScene(const CCommonScene& rhs);
		CCommonScene(const CCommonScene&& rhs) = delete;
		CCommonScene& operator=(const CCommonScene& rhs) = delete;

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