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

namespace Leviathan
{
	class CCommonScene : public IScene
	{
	public:
		CCommonScene(GLFWwindow* pRenderWindow, int width, int height);
		~CCommonScene();
		void Update();

	private:
		CCommonScene(const CCommonScene& rhs);
		CCommonScene(const CCommonScene&& rhs) = delete;
		CCommonScene& operator=(const CCommonScene& rhs) = delete;

		bool _initSceneObject();
		bool _initShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath);		
		bool _initCamera(unsigned width, unsigned height);
		bool _initLight();

		std::string _getShaderSource(const char* pczShaderSourcePath);
		
		LPtr<GLObject> _convertModelFileToGLObject(LPtr<IModelStruct> modelFile);
		LPtr<GLObject> _convertAABBtoGLObject(const AABB& aabb);
		LPtr<GLObject> _getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData = nullptr);

		GLFWwindow* m_pGLFWWindow;
		LPtr<RenderWrapper> m_pRenderWarpper;
		LPtr<TriDObjectGLPass> m_pMeshPass;
		LPtr<GLShaderProgram> m_pShaderProgram;
		LPtr<SceneGraph> m_pSceneGraph;
		std::vector<LPtr<GLLight>> m_pLights;
	};
}