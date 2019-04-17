#include <fstream>
#include <vector>
#include "UserInterface.h"
#include "GridRemover.h"
#include "LevSceneNode.h"

using namespace Leviathan;

bool LoadFrameData(const char * dataFilePath, std::vector<Point3D> result)
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
	UserInterface::Init(1080, 720, 0);

	if (argc < 2 || !argv[1])
	{
		return -1;
	}

	int nCount = 100;
	int nCurrent = 0;

	std::string path = argv[1];
	path += "\\frame_%04d.ply";
	char buf[300];

	while (true)
	{
		if(nCount > nCurrent)
		{
			memset(buf, 0, 300);
			snprintf(buf, 300, path.c_str(), nCurrent++);
			LPtr<Scene::LevSceneNode> pMeshNode;
			UserInterface::LoadPointCloudFile(buf, pMeshNode);
		}
		
		UserInterface::UpdatePresenter();
	}
}