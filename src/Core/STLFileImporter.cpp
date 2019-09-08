#include "STLFileImporter.h"
#include "DynamicArray.h"
#include "FileImportFactory.h"
#include <fstream>
#include <set>
#include <mutex>

struct _point3D
{
	unsigned index;
	float coord[3];

	bool operator<(const _point3D& rhs) const
	{
		for (unsigned i = 0; i < 3; i++)
		{
			if (coord[i] < rhs.coord[i])
			{
				return true;
			}

			if (coord[i] > rhs.coord[i])
			{
				return false;
			}
		}

		return false;
	}
};

namespace Leviathan
{
	STLFileImporter::STLFileImporter()
	{
		
	}

	IFileImporter& STLFileImporter::GetInstance()
	{
		return Singleton<STLFileImporter>::Instance();
	}

	std::string STLFileImporter::TypeName()
	{
		return "stl";
	}

	std::vector<LSPtr<IMesh>> STLFileImporter::LoadFile(const char* fileName)
	{
		std::ifstream fileStream(fileName, std::ios::in | std::ios::binary);
		if (!fileStream.is_open())
		{
			LeviathanOutStream << "[ERROR] Invalid file name." << std::endl;
			return std::vector<LSPtr<IMesh>>();
		}

		// Skip file head
		char header[80];
		fileStream.read(header, sizeof(header));
	
		// Load vertexNumber
		unsigned uTriangleNumber;
		fileStream.read(reinterpret_cast<char*>(&uTriangleNumber), sizeof(uTriangleNumber));

		auto pMesh = new MeshImpl(3 * uTriangleNumber, uTriangleNumber);

		// Load data
		std::set <_point3D> vertexSet;
		
		DynamicArray<unsigned> triangleArray(sizeof(unsigned) * uTriangleNumber * 3);
		unsigned* triangleIndex = triangleArray.m_pData;

		unsigned uCurrentIndex = 0;

		static auto _GetOrCreateVertexIndex = [](_point3D& vertexCoord, std::set<_point3D>& vertexSet, unsigned& currentIndex)
		{
			auto itFind = vertexSet.find(vertexCoord);
			if (itFind != vertexSet.end())
			{
				return itFind->index;
			}

			vertexCoord.index = currentIndex++;
			vertexSet.insert(vertexCoord);

			return vertexCoord.index;
		};
		
		for (unsigned i = 0; i < uTriangleNumber; i++)
		{
			_point3D _vertexPoints[4];
			for (unsigned j = 0; j < 4; j++)
			{
				fileStream.read(reinterpret_cast<char*>(_vertexPoints[j].coord), sizeof(float) * 3);
			}

			for (unsigned j = 0; j < 3; j++)
			{
				triangleIndex[3 * i + j] = _GetOrCreateVertexIndex(_vertexPoints[j + 1], vertexSet, uCurrentIndex);
			}

			char bitOffset[2];
			fileStream.read(bitOffset, sizeof(char) * 2);
		}

		fileStream.close();

		DynamicArray<float> vertexCoordArray(sizeof(float) * vertexSet.size() * 3);
		for (auto& point : vertexSet)
		{
			memcpy(reinterpret_cast<char*>(vertexCoordArray.m_pData + 3 * point.index), point.coord, sizeof(float) * 3);
		}

		pMesh->SetPrimitiveIndexData(triangleIndex);
		pMesh->SetVertexCoordData(vertexCoordArray.m_pData);

		return std::vector<LSPtr<IMesh>>(LSPtr<IMesh>(pMesh));
	}

	bool STLFileImporter::RegisterToFactory()
	{
		return FileImportFactory::GetFileImportFactory()->RegisterImporter(STLFileImporter::TypeName(), this);
	}
}

