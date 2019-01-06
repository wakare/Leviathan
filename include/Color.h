#pragma once

namespace Leviathan
{
	struct Color
	{
		float r;
		float g;
		float b;

		Color(float _r, float _g, float _b) : r(_r), g(_g), b(_g)
		{

		}

		Color(float* pData) : r(pData[0]), g(pData[1]), b(pData[2])
		{

		}
	};
}