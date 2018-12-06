#pragma once
#include <SOIL.h>

class PictureObject
{
public:
	PictureObject(const char* czFileName):
		m_pData(nullptr)
	{
		m_pData = SOIL_load_image(czFileName, &m_nWidth, &m_nHeight, 0, SOIL_LOAD_RGB);
		if (!m_pData)
		{
			LeviathanOutStream << "[WARN] Load picture failed." << std::endl;
		}
	}

	~PictureObject()
	{
		if (m_pData)
		{ 
			SOIL_free_image_data(m_pData);
		}
	}

	int m_nWidth;
	int m_nHeight;
	unsigned char* m_pData;
};