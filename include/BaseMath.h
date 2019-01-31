#pragma once
#include <memory.h>
#include "VectorOperation.h"

namespace Leviathan
{
	struct Vector3f;

	template <typename T>
	T VertexToRayDistance(T* rayPos, T* rayDir, T* vertexCoord)
	{
		Normalize<T, 3>(rayDir);
		T delta[3] = { rayPos[0] - vertexCoord[0], rayPos[1] - vertexCoord[1], rayPos[2] - vertexCoord[2] };
		T out[3];
		Vec3Cross<T>(rayDir, delta, out);
		return length<T, 3>(out);
	};

	struct Vector3f
	{
		Vector3f(float _x, float _y, float _z) :
			x(_x), y(_y), z(_z)
		{

		};

		Vector3f(float* data) :
			x(data[0]), y(data[1]), z(data[2])
		{

		}

		float x;
		float y;
		float z;
	};

	struct Vector4f;

	struct Matrix4f
	{
	public:
		friend Vector4f;

		Matrix4f() { _setIdentity(); }
		Matrix4f(float* data) { memcpy(m_data, data, sizeof(float) * 16); }
		Matrix4f(const Matrix4f& ref) { memcpy(m_data, ref.m_data, sizeof(float) * 16); }
		Matrix4f& operator=(const Matrix4f& ref) { memcpy(m_data, ref.m_data, sizeof(float) * 16); return *this; }
		Matrix4f operator*(const Matrix4f& ref)
		{
			float result[4][4];
			for (unsigned i = 0; i < 4; i++)
			{
				for (unsigned j = 0; j < 4; j++)
				{
					result[i][j] =
						m_data[i][0] * ref.m_data[0][j] +
						m_data[i][1] * ref.m_data[1][j] +
						m_data[i][2] * ref.m_data[2][j] +
						m_data[i][3] * ref.m_data[3][j];
				}
			}

			return Matrix4f(reinterpret_cast<float*>(result));
		}

		Matrix4f GetInverseMatrix()
		{
			float newMatrixData[4][4] =
			{
				m_data[0][0], m_data[1][0], m_data[2][0], m_data[3][0],
				m_data[0][1], m_data[1][1], m_data[2][1], m_data[3][1],
				m_data[0][2], m_data[1][2], m_data[2][2], m_data[3][2],
				m_data[0][3], m_data[1][3], m_data[2][3], m_data[3][3],
			};

			return Matrix4f(reinterpret_cast<float*>(newMatrixData));
		}

		Matrix4f& InverseSelf()
		{
			float newMatrixData[4][4] =
			{
				m_data[0][0], m_data[1][0], m_data[2][0], m_data[3][0],
				m_data[0][1], m_data[1][1], m_data[2][1], m_data[3][1],
				m_data[0][2], m_data[1][2], m_data[2][2], m_data[3][2],
				m_data[0][3], m_data[1][3], m_data[2][3], m_data[3][3],
			};

			memcpy(m_data, newMatrixData, sizeof(float) * 16);

			return *this;
		}

		void SetData(float* data) { memcpy(m_data, data, GetDataSize()); }
		float* GetData() const { return (float*)(*m_data); };
		unsigned GetDataSize() { return sizeof(float) * 16; }

		static Matrix4f GetIdentityMatrix()
		{
			static float identityMatrix[16] =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};

			return Matrix4f(identityMatrix);
		}

		static Matrix4f GetTranslateMatrix(float x, float y, float z)
		{
			float translateMatrix[16] =
			{
				1.0f,	0.0f,	0.0f,	0.0f,
				0.0f,	1.0f,	0.0f,	0.0f,
				0.0f,	0.0f,	1.0f,	0.0f,
				x,		y,		z,		1.0f,
			};

			return Matrix4f(translateMatrix);
		}

		static void GetTranslateMatrix(float x, float y, float z, Matrix4f& outMatrix)
		{
			float translateMatrix[16] =
			{
				1.0f,	0.0f,	0.0f,	0.0f,
				0.0f,	1.0f,	0.0f,	0.0f,
				0.0f,	0.0f,	1.0f,	0.0f,
				x,		y,		z,		1.0f,
			};

			outMatrix = translateMatrix;
		}

	private:
		void _setIdentity()
		{
			static float identityMatrix[16] =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};

			memcpy(m_data, identityMatrix, sizeof(float) * 16);
		}

		float m_data[4][4];
	};

	struct Vector4f
	{
	public:
		Vector4f(float* data) { memcpy(m_data, data, sizeof(m_data)); }
		float* GetData() { return m_data; }
		unsigned GetDataSize() { return 4; }

		Vector4f operator*(const Matrix4f& ref)
		{
			float result[4];
			for (unsigned i = 0; i < 4; i++)
			{
				result[i] =
					m_data[0] * ref.m_data[0][i] +
					m_data[1] * ref.m_data[1][i] +
					m_data[2] * ref.m_data[2][i] +
					m_data[3] * ref.m_data[3][i];
			}

			return Vector4f(result);
		}
		operator Vector3f() { return Vector3f(m_data); }
	private:
		float m_data[4];
	};
}