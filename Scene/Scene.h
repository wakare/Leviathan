#pragma once
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
	class Scene
	{
	public:
		Scene(GLFWwindow* pRenderWindow, int width, int height);

		virtual void Update();

		LPtr<GLCamera> m_pCamera;
	private:
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