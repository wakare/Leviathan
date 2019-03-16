#include "PointCloudScene.h"
#include "GLObject.h"
#include "MeshImpl.h"
#include "PointCloud.h"
#include "DrawableNode.h"
#include "SceneNode.h"
#include "SceneGraph.h"
#include "SceneLogicDataSet.h"

namespace Leviathan
{
	PointCloudScene::PointCloudScene(GLFWwindow* pRenderWindow, int width, int height): 
		CommonScene(pRenderWindow, width, height)
	{

	}

	void PointCloudScene::UpdatePointCloud(PointCloudf& refPoints)
	{
		static std::vector<LPtr<GLObject>> _lastAddPointCloud;

		// Set last add pointCloudColor
		for (auto& pPointCloud : _lastAddPointCloud)
		{
			pPointCloud->SetDefaultVertexColorEnable(false);
			pPointCloud->SetLightEnable(true);
		}

		// convert pointCloud to GLObject
		LPtr<CMesh> pMesh = new CMesh(refPoints.m_pointCount, refPoints.m_pointCount, IMesh::EPT_POINTS);
		pMesh->SetVertexCoordData(refPoints.m_pCoord->m_pData);
		if (refPoints.HasNormal())
		{
			pMesh->SetVertexNormalData(refPoints.m_pNormal->m_pData);
		}

		auto pSceneNode = LPtr<SceneNode>(new SceneNode());
		pSceneNode->AddMesh(TryCast<CMesh, IMesh>(pMesh));
		LPtr<DrawableNode<SceneNode>> pDentalNode = new DrawableNode<SceneNode>(TryCast<CMesh, IMesh>(pMesh), pSceneNode);
		m_pSceneLogicData->AddNode(TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pDentalNode));

		_lastAddPointCloud = pDentalNode->GetGLObject();
		for (auto& pPointCloud : _lastAddPointCloud)
		{
			pPointCloud->SetDefaultVertexColorEnable(true);
			pPointCloud->SetLightEnable(false);
		}

		float center[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float radius;
		refPoints.GetCenterAndRadius(center, radius);

		_resetCamera(center);
	}

	bool PointCloudScene::_firstUpdate()
	{
		// Init light
		EXIT_IF_FALSE(_initLight());

		if (!_initSceneObject())
		{
			LeviathanOutStream << "[ERROR] Init scene object failed." << std::endl;
		}

		_resetCamera();

		return true;
	}

	bool PointCloudScene::_initSceneObject()
	{
		auto _addPointCloud = [this]()
		{
			constexpr int uCount = 3000;
			float testPointCoord[3 * uCount];
			float testPointNormal[3 * uCount];

			constexpr float fMaxRange = 100.0f;

			for (unsigned i = 0; i < uCount; i++)
			{
				testPointCoord[3 * i] = RAND_FLOAT_ZERO_TO_ONE * fMaxRange;
				testPointCoord[3 * i + 1] = RAND_FLOAT_ZERO_TO_ONE * fMaxRange;
				testPointCoord[3 * i + 2] = RAND_FLOAT_ZERO_TO_ONE * fMaxRange;

				testPointNormal[3 * i] = 1.0f;
				testPointNormal[3 * i + 1] = 0.0f;
				testPointNormal[3 * i + 2] = 0.0f;
			}

			PointCloudf points(uCount, testPointCoord, testPointNormal);
			UpdatePointCloud(points);
		};

		EXIT_IF_FALSE(m_pSceneLogicData->PushDataUpdateRequest(_addPointCloud));
		EXIT_IF_FALSE(m_pSceneLogicData->PushDataUpdateRequest(_addPointCloud));

		return true;
	}

}