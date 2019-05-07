#include <Eigen/Dense>

#include <fstream>
#include <vector>
#include <thread>

#include "UserInterface.h"
#include "GridRemover.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevRAttrObjectColor.h"
#include "LevScheduler.h"
#include "ViewScheduler.h"
#include "SceneGraph.h"
#include "AABB.h"
#include "LevMeshObject.h"
#include "MeshImpl.h"

using namespace Leviathan;

bool LoadFrameData(const char * dataFilePath, std::vector<Point3D>& result)
{
	std::fstream frameFile(dataFilePath, std::ios::in);
	if (!frameFile.is_open()) return false;

	char line[300];
	unsigned vertexCount = 0;
	while (true)
	{
		frameFile.getline(line, 300);
		std::string _line = line;
		if (_line.find("element vertex") != std::string::npos)
		{
			std::string vertexCountStr = _line.substr(15, _line.length() - 15);
			vertexCount = std::atoi(vertexCountStr.c_str());
		}

		if (_line == "end_header") break;
	}

	// Skip first two line
	frameFile.getline(line, sizeof(line));
	frameFile.getline(line, sizeof(line));

	//Leviathan::DynamicArray<float> databuffer(vertexCount * 6 * sizeof(float));
	float* _data = new float[vertexCount * 6];

	auto pCoord = _data;
	auto pNormal = _data + vertexCount * 3;

	for (unsigned i = 0; i < vertexCount; i++)
	{
		float vertexData[7];
		for (unsigned i = 0; i < 7; i++)
		{
			frameFile >> vertexData[i];
		}

		memcpy(pCoord + 3 * i, vertexData + 1, 3 * sizeof(float));
		memcpy(pNormal + 3 * i, vertexData + 4, 3 * sizeof(float));

		result.push_back(std::move(Point3D(vertexData + 1)));
	}

	return true;
}

int main(int argc, char** argv)
{
	if (argc < 2 || !argv[1])
	{
		return -1;
	}

	std::thread renderer([]
		{
			UserInterface::Init(1080, 720, 0);
			while (true)
			{
				UserInterface::UpdatePresenter();
			}
		});

	renderer.detach();

	int nCount = 100;
	int nCurrent = 0;

	std::string path = argv[1];
	path += "\\frame_%04d.ply";
	char buf[300];

	std::vector<Point3D> points;
	std::vector<Point3D> tsdfFrame;
	GridRemover remover;
	auto& viewScheduler = UserInterface::GetViewScheduler();

	std::vector<LPtr<Scene::LevSceneNode>> meshes;

	while (true)
	{
		// Load
		if(nCount > nCurrent)
		{
			memset(buf, 0, 300);
			snprintf(buf, 300, path.c_str(), nCurrent++);
			LPtr<Scene::LevSceneNode> pMeshNode;
			UserInterface::LoadPointCloudFile(buf, pMeshNode);
			meshes.push_back(pMeshNode);
			std::vector<Point3D> frame;
			LoadFrameData(buf, frame);
			points.insert(points.end(), frame.begin(), frame.end());

			if (nCurrent == 50)
			{
				tsdfFrame = frame;
			}

			continue;
		}

		remover.SetTSDFCloud(tsdfFrame);
		std::vector<bool> testResult;
		remover.TestOverlap(Eigen::Matrix4f::Identity(), points, testResult);

		// Update original data
		unsigned currentPointIndex = 0;
		for (auto& mesh : meshes)
		{
			auto& objDesc = mesh->GetNodeData()->GetObjDesc();
			if (objDesc.GetType() & LevSceneObjectDescType::ELSOD_MESH == 0)
			{
				continue;
			}

			Scene::LevMeshObject* pMesh = dynamic_cast<Scene::LevMeshObject*>(&objDesc);
			if (!pMesh)
			{
				continue;
			}

			Scene::LevObjectColorData colorData;
			colorData.pure_color[0] = 0.1f;
			colorData.pure_color[1] = 0.5f;
			colorData.pure_color[2] = 0.1f;

			auto _updateColor = [pMesh, &colorData](Leviathan::CoPullType<int>&)
			{
				pMesh->SetColorData(Scene::ELOCT_PURE_COLOR, colorData);
			};

			viewScheduler.DoSyncTask(_updateColor);

// 			auto& attributes = mesh->GetNodeData()->GetObjAttributes();
// 
// 			for (auto& attr : attributes)
// 			{
// 				if (attr->GetType() != Scene::ELSOAT_RENDER)
// 				{
// 					continue;
// 				}
// 
// 				Scene::LevRAttrObjectColor* pColorAttr = dynamic_cast<Scene::LevRAttrObjectColor*>(attr.Get());
// 				if (pColorAttr)
// 				{
// 					// Reset color data array.
// 					LEV_ASSERT(pColorAttr->GetColorType() == Scene::ELOCT_COLOR_ARRAY);
// 					auto* pColorArrayData = pColorAttr->GetColorData().color_array;
// 
// 					auto _updateColorArray = [&testResult, &currentPointIndex, pColorAttr, pColorArrayData](Leviathan::CoPullType<int>&)
// 					{
// 						auto vertexCount = pColorAttr->GetColorData().color_array_byte_size / (3 * sizeof(float));
// 
// 						for (unsigned i = 0; i < vertexCount; i++)
// 						{
// 							float* pcolor = pColorArrayData + 3 * i;
// 							if (testResult[currentPointIndex + i])
// 							{
// 								pcolor[0] = 0.0f;
// 								pcolor[1] = 0.0f;
// 								pcolor[2] = 0.0f;
// 							}
// 						}
// 
// 						currentPointIndex += vertexCount;
// 					};
// 
// 					viewScheduler.DoSyncTask(_updateColorArray);
//				}
//			}

			viewScheduler.DoTask([&mesh](Leviathan::CoPullType<int>&)
			{
				mesh->GetNodeData()->SetState(Leviathan::Scene::ELSOS_UPDATE);
			});
		}

		// Add Grid geometry
		auto& grids = remover.GetGridBars();
		for (auto& grid : grids)
		{
			float min[3], max[3];
			grid.GetBoxRange(min, max);

			min[2] = grid.tsdf;
			//min[2] = -2.0f;
			max[2] = 0.0f;

			AABB aabb(min, max);

			float _vertexCoord[] =
			{
				min[0], min[1], min[2],
				min[0], min[1], max[2],
				min[0], max[1], min[2],
				min[0], max[1], max[2],
				max[0], min[1], min[2],
				max[0], min[1], max[2],
				max[0], max[1], min[2],
				max[0], max[1], max[2],
			};

			unsigned _index[] =
			{
				0,2,3,
				0,3,1,
				0,1,5,
				0,5,4,
				0,2,6,
				0,6,4,
				7,4,2,
				7,2,3,
				7,5,4,
				7,4,6,
				7,5,1,
				7,1,3
			};

			LPtr<MeshImpl> pMesh = new MeshImpl(8, 12);
			pMesh->SetVertexCoordData(_vertexCoord);
			pMesh->SetPrimitiveIndexData(_index);

			viewScheduler.LoadCustomMesh(TryCast<MeshImpl, IMesh>(pMesh));
		}

		break;
	}

	std::chrono::milliseconds timespan(100000);
	std::this_thread::sleep_for(timespan);

	return 0;
}