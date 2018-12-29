#pragma once

struct GLColor 
{
	float r;
	float g;
	float b;

	GLColor(float _r, float _g, float _b) : r(_r), g(_g), b(_g)
	{

	}

	GLColor(float* pData) : r(pData[0]), g(pData[1]), b(pData[2])
	{

	}
};