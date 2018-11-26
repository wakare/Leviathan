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
	class CommonScene : public IScene
	{
	public:
		CommonScene(GLFWwindow* pRenderWindow, int width, int height);
		~CommonScene();
		void Update();

	private:
		CommonScene(const CommonScene& ref);

		bool InitSceneObject();
		
		bool InitShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath);
		
		bool InitCamera(unsigned width, unsigned height);
		
		CommonScene& operator=(const CommonScene& ref);

		std::string _getShaderSource(const char* pczShaderSourcePath);
		LPtr<GLObject> _convertModelFileToGLObject(LPtr<IModelStruct> modelFile);
		LPtr<GLObject> _convertAABBtoGLObject(const AABB& aabb);
		LPtr<GLObject> _getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData = nullptr);

		GLFWwindow* m_pGLFWWindow;

		LPtr<RenderWrapper> m_pRenderWarpper;
		LPtr<TriDObjectGLPass> m_pMeshPass;
		LPtr<GLShaderProgram> m_pShaderProgram;
		LPtr<SceneGraph> m_pSceneGraph;
	};
}