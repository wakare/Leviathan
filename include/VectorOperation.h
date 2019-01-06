#pragma once

#include <float.h>
#include <math.h>

template<typename T, int count>
T length(T* vec)
{
	float temp = 0.0f;
	for (unsigned i = 0; i < count; i++)
	{
		temp += (vec[i] * vec[i]);
	}

	return sqrt(temp);
}

template<typename T, int count>
bool Normalize(T* vec)
{
	const float fLength = length<T, count>(vec);
	if (fLength < FLT_EPSILON)
	{
		return false;
	}

	for (unsigned i = 0; i < count; i++)
	{
		vec[i] /= fLength;
	}

	return true;
}

template <typename T, int count>
T VecDot(T* vec0, T* vec1)
{
	T result = 0;
	for (unsigned i = 0; i < count; i++)
	{
		result += (vec0[i] * vec1[i]);
	}

	return result;
}

template <typename T>
void Vec3Cross(T* vec0, T* vec1, T* outVec, bool bNormalize = false)
{
	outVec[0] = vec0[1] * vec1[2] - vec0[2] * vec1[1];
	outVec[1] = vec0[2] * vec1[0] - vec0[0] * vec1[2];
	outVec[2] = vec0[0] * vec1[1] - vec0[1] * vec1[0];

	if (bNormalize)
	{
		Normalize<T, 3>(outVec);
	}
}