#include "CFileImportFactory.h"
#include "CModelStruct.h"
#include <string>
#include <mutex>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "DynamicArray.h"

using namespace Leviathan;

LPtr<IFileImportFactory> CFileImportFactory::m_spFileImportFactory = nullptr;

std::vector<LPtr<IModelStruct>> Leviathan::CFileImportFactory::LoadFile(const char* czFileName)
{
	std::string fileNameString(czFileName);
	return LoadFile(fileNameString);
}

Leviathan::LPtr<Leviathan::IFileImportFactory> Leviathan::CFileImportFactory::GetFileImportFactory()
{
	static std::once_flag sFlag;

	if (!m_spFileImportFactory)
	{
		std::call_once(sFlag, [&]()
		{
			LeviathanOutStream << "[WARN] File import factory inited." << std::endl;
			m_spFileImportFactory = LPtr<IFileImportFactory>(new CFileImportFactory());
		});
	}

	return m_spFileImportFactory;
}

bool Leviathan::CFileImportFactory::RegisterImporter(std::string typeName, LPtr<IFileImporter> pImporter)
{
	auto itImporter = m_registerFileImport.find(typeName);
	if (itImporter != m_registerFileImport.end())
	{
		LeviathanOutStream << "[WARN] Try to add exist file importer." << std::endl;
		return false;
	}

	m_registerFileImport.insert(std::make_pair(typeName, pImporter));
	return true;
}

Leviathan::CFileImportFactory::CFileImportFactory()
{

}

std::vector<LPtr<IModelStruct>> Leviathan::CFileImportFactory::_loadModelByAssimp(const std::string& strFileName)
{
	Assimp::Importer importer;
	const aiScene* importerScene = importer.ReadFile(strFileName, aiProcessPreset_TargetRealtime_Fast);

	auto lastOfDotIndex = strFileName.find_last_of("/\\");
	std::string absDirectoryPath;
	if (lastOfDotIndex != std::string::npos)
	{
		absDirectoryPath = strFileName.substr(0, lastOfDotIndex + 1);
	}

	if (!importerScene->HasMeshes())
	{
		LeviathanOutStream << "[INFO] Assimp load file: " << strFileName << " failed." << std::endl;
		return std::vector<LPtr<IModelStruct>>();
	}

	std::vector<LPtr<IModelStruct>> result;

	// Get meshes
	auto pMeshes = importerScene->mMeshes;
	auto pMaterial = importerScene->HasMaterials() ? importerScene->mMaterials : nullptr;
	
	LeviathanOutStream << importerScene->HasTextures() << std::endl;

	for (unsigned i = 0; i < importerScene->mNumMeshes; i++)
	{
		auto*& pMesh = pMeshes[i];
		
		auto pModelStruct = new CModelStruct();
		if (!pMesh->HasPositions())
		{
			LeviathanOutStream << "[WARN] Mesh has no position, skip..." << std::endl;
			continue;
		}

		DynamicArray<float> vertexCoordData(pMesh->mNumVertices * 3 * sizeof(float));
		for (unsigned j = 0; j < pMesh->mNumVertices; j++)
		{
			auto vertexCoord = pMesh->mVertices[j];
			float* pVertexData = vertexCoordData.m_pData + 3 * j;

			pVertexData[0] = vertexCoord.x;
			pVertexData[1] = vertexCoord.y;
			pVertexData[2] = vertexCoord.z;
		}

		pModelStruct->SetVertexCoordData(pMesh->mNumVertices, vertexCoordData.m_pData);

		if (pMesh->HasFaces())
		{
			DynamicArray<unsigned> indexData(pMesh->mNumFaces * 3 * sizeof(unsigned));

			for (unsigned j = 0; j < pMesh->mNumFaces; j++)
			{
				auto indexVec = pMesh->mFaces[j];
				unsigned* pIndexData = indexData.m_pData + 3 * j;

				memcpy(pIndexData, indexVec.mIndices, sizeof(unsigned) * 3);
			}

			pModelStruct->SetTriangleIndexData(pMesh->mNumFaces, indexData.m_pData);
		}

		// Only select level-0 texture
		if (pMesh->HasTextureCoords(0))
		{
			DynamicArray<float> vertexTexData(pMesh->mNumVertices * 2 * sizeof(float));
			for (unsigned j = 0; j < pMesh->mNumVertices; j++)
			{
				auto vertexCoord = pMesh->mTextureCoords[0][j];
				float* pTexData = vertexTexData.m_pData + 2 * j;

				pTexData[0] = vertexCoord.x;
				pTexData[1] = vertexCoord.y;
			}

			pModelStruct->SetVertexTex2DData(pMesh->mNumVertices, vertexTexData.m_pData);
		}

		if (pMaterial)
		{
			std::string absPath = absDirectoryPath;
			aiMaterial* meshMaterial = pMaterial[pMesh->mMaterialIndex];
			aiReturn texFound = AI_SUCCESS;
			aiString texturePath;
			int texIndex = 0;

			while (texFound == aiReturn_SUCCESS)
			{
				texFound = meshMaterial->GetTexture(aiTextureType_DIFFUSE, texIndex++, &texturePath);
				if (texFound == aiReturn_SUCCESS)
				{
					if (texIndex == 2)
					{
						throw "Too many textures";
					}

					absPath += texturePath.C_Str();
					LeviathanOutStream << "[INFO] Texture path: " << absPath << std::endl;
				}
			}

			aiColor4D aiDiffuse;
			aiColor4D aiSpecular;
			aiColor4D aiAmbient;
			aiColor4D aiEmission;
			ai_real aiShininess;

			Vector3f diffuse(0.0f, 0.0f, 0.0f);
			Vector3f specular(0.0f, 0.0f, 0.0f);
			Vector3f ambient(0.0f, 0.0f, 0.0f);

			if (AI_SUCCESS == aiGetMaterialColor(meshMaterial, AI_MATKEY_COLOR_DIFFUSE, &aiDiffuse))
			{
				diffuse = { aiDiffuse.r, aiDiffuse.g, aiDiffuse.b };
			}

			if (AI_SUCCESS == aiGetMaterialColor(meshMaterial, AI_MATKEY_COLOR_SPECULAR, &aiSpecular))
			{
				specular = { aiSpecular.r, aiSpecular.g, aiSpecular.b };
			}

			if (AI_SUCCESS == aiGetMaterialColor(meshMaterial, AI_MATKEY_COLOR_AMBIENT, &aiAmbient))
			{
				ambient = { aiAmbient.r, aiAmbient.g, aiAmbient.b };
			}

			unsigned uMaxArrayLength = 1;
			aiGetMaterialFloatArray(meshMaterial, AI_MATKEY_SHININESS, &aiShininess, &uMaxArrayLength);

			pModelStruct->SetMaterial(new Material(ambient, diffuse, specular, aiShininess, (texturePath.length > 0) ? (absPath.length() > 0 ? absPath : "") : ""));
		}

		result.push_back(pModelStruct);
	}

	return result;
}

std::vector<LPtr<IModelStruct>> Leviathan::CFileImportFactory::LoadFile(std::string strFileName)
{
	auto pModelStruct = _loadModelByAssimp(strFileName);
	if (pModelStruct.size() > 0)
	{
		return pModelStruct;
	}

	// Get file extension type
	auto uLastDotIndex = strFileName.find_last_of('.');
	if (uLastDotIndex == std::string::npos)
	{
		LeviathanOutStream << "[ERROR] Invalid file name." << std::endl;
		return std::vector<LPtr<IModelStruct>>();
	}

	auto strFileExtension = strFileName.substr(uLastDotIndex + 1);
	auto itImporter = m_registerFileImport.find(strFileExtension);
	if (itImporter == m_registerFileImport.end())
	{
		LeviathanOutStream << "[WARN] Unsupported file extension : " << strFileExtension <<std::endl;
		return std::vector<LPtr<IModelStruct>>();
	}

	return itImporter->second->LoadFile(strFileName.c_str());
}
