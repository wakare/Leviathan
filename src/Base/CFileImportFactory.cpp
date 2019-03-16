#include "CFileImportFactory.h"
#include "MeshImpl.h"
#include "DynamicArray.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <mutex>

using namespace Leviathan;

LPtr<IFileImportFactory> CFileImportFactory::m_spFileImportFactory = nullptr;

std::vector<LPtr<IMesh>> Leviathan::CFileImportFactory::LoadFile(const char* czFileName)
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
			LeviathanOutStream << "[INFO] File import factory inited." << std::endl;
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
= default;

void _processMesh(const aiMesh& mesh, const aiScene& scene, const std::string& absDirectoryPath, std::vector<LPtr<IMesh>>& result)
{
	auto pMaterial = scene.HasMaterials() ? scene.mMaterials : nullptr;

	if (!mesh.HasPositions())
	{
		LeviathanOutStream << "[WARN] Mesh has no position, skip..." << std::endl;
		return;
	}

	auto pMesh = new MeshImpl(mesh.mNumVertices, mesh.mNumFaces);

	DynamicArray<float> vertexCoordData(mesh.mNumVertices * 3 * sizeof(float));
	for (unsigned j = 0; j < mesh.mNumVertices; j++)
	{
		auto vertexCoord = mesh.mVertices[j];
		float* pVertexData = vertexCoordData.m_pData + 3 * j;

		pVertexData[0] = vertexCoord.x;
		pVertexData[1] = vertexCoord.y;
		pVertexData[2] = vertexCoord.z;
	}

	pMesh->SetVertexCoordData( vertexCoordData.m_pData);

	if (mesh.HasFaces())
	{
		DynamicArray<unsigned> indexData(mesh.mNumFaces * 3 * sizeof(unsigned));

		for (unsigned j = 0; j < mesh.mNumFaces; j++)
		{
			auto indexVec = mesh.mFaces[j];
			unsigned* pIndexData = indexData.m_pData + 3 * j;

			memcpy(pIndexData, indexVec.mIndices, sizeof(unsigned) * 3);
		}

		pMesh->SetPrimitiveIndexData(indexData.m_pData);
	}

	// Only select level-0 texture
	if (mesh.HasTextureCoords(0))
	{
		DynamicArray<float> vertexTexData(mesh.mNumVertices * 2 * sizeof(float));
		for (unsigned j = 0; j < mesh.mNumVertices; j++)
		{
			auto vertexCoord = mesh.mTextureCoords[0][j];
			float* pTexData = vertexTexData.m_pData + 2 * j;

			pTexData[0] = vertexCoord.x;
			pTexData[1] = vertexCoord.y;
		}

		pMesh->SetVertexTex2DData(vertexTexData.m_pData);
	}

	if (pMaterial)
	{
		std::string absPath = absDirectoryPath;
		aiMaterial* meshMaterial = pMaterial[mesh.mMaterialIndex];
		aiReturn texFound = AI_SUCCESS;
		aiString texturePath;
		bool bTexPathFound = false;
		int texIndex = 0;

		for (int nType = aiTextureType_DIFFUSE; nType != aiTextureType_UNKNOWN + 1; nType++)
		{
			texFound = meshMaterial->GetTexture(static_cast<aiTextureType>(nType), texIndex++, &texturePath);
			if (texFound == aiReturn_SUCCESS)
			{
				bTexPathFound = true;
				absPath += texturePath.C_Str();
				LeviathanOutStream << "[INFO] Find Texture path: " << absPath << " , texture type: " << nType << std::endl;
				break;
			}
		}

		aiColor4D aiDiffuse;
		aiColor4D aiSpecular;
		aiColor4D aiAmbient;
		aiColor4D aiEmission;
		ai_real aiShininess;

		Eigen::Vector3f diffuse(0.0f, 0.0f, 0.0f);
		Eigen::Vector3f specular(0.0f, 0.0f, 0.0f);
		Eigen::Vector3f ambient(0.0f, 0.0f, 0.0f);

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

		if (!bTexPathFound)
		{
			LeviathanOutStream << "[WARN] Texture path not found." << std::endl;
		}

		pMesh->SetMaterial(new Material(ambient, diffuse, specular, (aiShininess > 1.0f) ? aiShininess : 1.0f, (texturePath.length > 0) ? (absPath.length() > 0 ? absPath : "") : ""));
	}

	result.push_back(pMesh);
}

void _recursionLoadModel(const aiNode& node, const aiScene& scene, const std::string& absDirectoryPath, std::vector<LPtr<IMesh>>& result)
{
	for (unsigned i = 0; i < node.mNumMeshes; i++)
	{
		aiMesh* pMesh = scene.mMeshes[node.mMeshes[i]];
		_processMesh(*pMesh, scene, absDirectoryPath, result);
	}

	for (unsigned i = 0; i < node.mNumChildren; i++)
	{
		_recursionLoadModel(*node.mChildren[i], scene, absDirectoryPath, result);
	}
}

std::vector<LPtr<IMesh>> Leviathan::CFileImportFactory::_loadModelByAssimp(const std::string& strFileName)
{
	Assimp::Importer importer;
	const aiScene* importerScene = importer.ReadFile(strFileName, aiProcessPreset_TargetRealtime_Fast);
	if (importerScene == nullptr)
	{
		LeviathanOutStream << "[INFO] Load file failed.";

		throw "exception";
		return std::vector<LPtr<IMesh>>();
	}

	auto lastOfDotIndex = strFileName.find_last_of("/\\");
	std::string absDirectoryPath;
	if (lastOfDotIndex != std::string::npos)
	{
		absDirectoryPath = strFileName.substr(0, lastOfDotIndex + 1);
	}

	if (!importerScene->HasMeshes())
	{
		LeviathanOutStream << "[INFO] Assimp load file: " << strFileName << " failed." << std::endl;
		return std::vector<LPtr<IMesh>>();
	}

	std::vector<LPtr<IMesh>> result;
	LogLine( "[INFO] Has texture? " << (importerScene->HasTextures() ? "True" : "False") );

	_recursionLoadModel(*(importerScene->mRootNode), *importerScene, absDirectoryPath, result);

	return result;
}

std::vector<LPtr<IMesh>> Leviathan::CFileImportFactory::LoadFile(std::string strFileName)
{
	auto pMesh = _loadModelByAssimp(strFileName);
	if (!pMesh.empty())
	{
		return pMesh;
	}

	// Get file extension type
	auto uLastDotIndex = strFileName.find_last_of('.');
	if (uLastDotIndex == std::string::npos)
	{
		LeviathanOutStream << "[ERROR] Invalid file name." << std::endl;
		return std::vector<LPtr<IMesh>>();
	}

	auto strFileExtension = strFileName.substr(uLastDotIndex + 1);
	auto itImporter = m_registerFileImport.find(strFileExtension);
	if (itImporter == m_registerFileImport.end())
	{
		LeviathanOutStream << "[WARN] Unsupported file extension : " << strFileExtension <<std::endl;
		return std::vector<LPtr<IMesh>>();
	}

	return itImporter->second->LoadFile(strFileName.c_str());
}
