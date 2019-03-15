#pragma once
#include <SOIL.h>
#include "GlobalDef.h"

class PictureObject
{
public:
	PictureObject(const char* pczFileName):
		m_pData(nullptr)
	{
		m_pData = SOIL_load_image(pczFileName, &m_nWidth, &m_nHeight, 0, SOIL_LOAD_RGB);
		if (!m_pData)
		{
			LeviathanOutStream << "[WARN] Load picture failed, path: " << pczFileName << std::endl;
		}
		else
		{
			LeviathanOutStream << "[INFO] Load picture succeed, path: " << pczFileName << std::endl;
		}
	}

	~PictureObject()
	{
		if (m_pData)
		{ 
			SOIL_free_image_data(m_pData);
		}
	}

	bool IsValid() const 
	{
		return m_pData != nullptr;
	}

	int m_nWidth;
	int m_nHeight;
	unsigned char* m_pData;
};