#pragma once
#include "VectorOperation.h"
#include "BaseMath.h"
#include "GlobalDef.h"
#include <gl/glew.h>
#include <memory>
#include <iostream>

namespace Leviathan
{
	class GLCamera
	{
	private:
		void _GetNUVVector(float* N, float* U, float* V)
		{
			N[0] = m_fLookAt[0] - m_fEye[0];
			N[1] = m_fLookAt[1] - m_fEye[1];
			N[2] = m_fLookAt[2] - m_fEye[2];

			Normalize<float, 3>(N);
			Vec3Cross(m_fUp, N, U, true);
			Vec3Cross(N, U, V, true);
		}

	public:
		enum class eCameraType
		{
			eObserveBallMode,
			eFPS,
		};

		GLCamera(float* eye, float* lookAt, float* up, float fovy, float aspect, float zNear, float zFar) :
			m_fovy(fovy),
			m_fAspect(aspect),
			m_fZNear(zNear),
			m_fZFar(zFar),
			m_minDistanceOfCameraToLookAt(0.01f),
			m_mouseOperationScaleRatio(1.0f)
		{
			memcpy(m_fEye, eye, sizeof(float) * 3);
			memcpy(m_fLookAt, lookAt, sizeof(float) * 3);
			memcpy(m_fUp, up, sizeof(float) * 3);
		};

		Matrix4f GetViewportTransformMatrix()
		{
			float N[3];
			float U[3];
			float V[3];

			_GetNUVVector(N, U, V);

			float data[16] =
			{
				U[0], U[1], U[2], -VecDot<float, 3>(U, m_fEye),
				V[0], V[1], V[2], -VecDot<float, 3>(V, m_fEye),
				N[0], N[1], N[2], -VecDot<float, 3>(N, m_fEye),
				0.0f, 0.0f, 0.0f,						 1.0f,
			};

			Matrix4f result = Matrix4f(data);
			return result;
		};

		Matrix4f GetPerspectiveTransformMatrix()
		{
			float tanHalfFovy = tanf(m_fovy / 2.0f);

			float data[16] =
			{
				1.0f / (m_fAspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f / tanHalfFovy , 0.0f, 0.0f,
				0.0f, 0.0f, (-m_fZNear - m_fZFar) / (m_fZNear - m_fZFar) , 2 * m_fZFar * m_fZNear / (m_fZNear - m_fZFar),
				0.0f, 0.0f, 1.0f, 0.0f
			};

			Matrix4f result = Matrix4f(data);
			return result;
		};

		void Translate(float x, float y, float z)
		{
			float N[3];
			float U[3];
			float V[3];

			_GetNUVVector(N, U, V);
			memcpy(m_fUp, V, sizeof(float) * 3);

			float newEyeCoord[3] =
			{
				m_fEye[0] + (x * U[0] + y * V[0] + z * N[0]),
				m_fEye[1] + (x * U[1] + y * V[1] + z * N[1]),
				m_fEye[2] + (x * U[2] + y * V[2] + z * N[2])
			};

			float _N[3] =
			{
				m_fLookAt[0] - newEyeCoord[0],
				m_fLookAt[1] - newEyeCoord[1],
				m_fLookAt[2] - newEyeCoord[2],
			};

			if (length<float, 3>(_N) < m_minDistanceOfCameraToLookAt)
			{
				LeviathanOutStream << "Arrive minDistanceOfCameraToLookAt." << std::endl;
				return;
			}

			memcpy(m_fEye, newEyeCoord, sizeof(float) * 3);
		}

		void MouseTranslate(float x, float y, float z)
		{
			float _lengthVec[3] = { m_fEye[0] - m_fLookAt[0], m_fEye[1] - m_fLookAt[1], m_fEye[2] - m_fLookAt[2] };
			float fLength = length<float, 3>(_lengthVec);
			float fScaleRatio = fLength * m_mouseOperationScaleRatio;

			return Translate(fScaleRatio * x, fScaleRatio * y, fScaleRatio * z);
		}

		void MouseRotate(float x, float y)
		{
			float N[3];
			float U[3];
			float V[3];

			_GetNUVVector(N, U, V);
			memcpy(m_fUp, V, sizeof(float) * 3);

			float RotateVec[3] =
			{
				y * U[0] + x * V[0],
				y * U[1] + x * V[1],
				y * U[2] + x * V[2],
			};

			Rotate(RotateVec[0], RotateVec[1], RotateVec[2]);
		}

		void Rotate(float x, float y, float z)
		{
			float sinValue[3] = { sinf(x), sinf(y), sinf(z) };
			float cosValue[3] = { cosf(x), cosf(y), cosf(z) };

			// Rotate along X axis
			float XRotate[4][4] =
			{
				1.0f,			0.0f,			0.0f,				0.0f,
				0.0f,			cosValue[0],	-sinValue[0],		0.0f,
				0.0f,			sinValue[0],	cosValue[0],		0.0f,
				0.0f,			0.0f,			0.0f,				1.0f,
			};

			// Rotate along Y axis
			float YRotate[4][4] =
			{
				cosValue[1],	0.0f,			sinValue[1],		0.0f,
				0.0f,			1.0f,			0.0f,				0.0f,
				-sinValue[1],	0.0f,			cosValue[1],		0.0f,
				0.0f,			0.0f,			0.0f,				1.0f,
			};

			// Rotate along Z axis
			float ZRotate[4][4] =
			{
				cosValue[2],	-sinValue[2],	0.0f,				0.0f,
				sinValue[2],	cosValue[2],	0.0f,				0.0f,
				0.0f,			0.0f,			1.0f,				0.0f,
				0.0f,			0.0f,			0.0f,				1.0f,
			};

			Matrix4f xMatrix(reinterpret_cast<float*>(XRotate));
			Matrix4f yMatrix(reinterpret_cast<float*>(YRotate));
			Matrix4f zMatrix(reinterpret_cast<float*>(ZRotate));

			Matrix4f rotateMatrix = xMatrix * yMatrix * zMatrix;

			static auto _updateCameraAttribute = [](float* attribute, Matrix4f& rotateMatrix)
			{
				float attributeArray[4] = { attribute[0], attribute[1], attribute[2], 1.0f };
				Vector4f attributeVector = Vector4f(attributeArray) * rotateMatrix;

				memcpy(attributeArray, attributeVector.GetData(), sizeof(attributeArray));
				if (fabs(attributeArray[3]) < FLT_EPSILON)
				{
					throw "Error attribute array.";
				}

				attributeArray[0] /= attributeArray[3];
				attributeArray[1] /= attributeArray[3];
				attributeArray[2] /= attributeArray[3];

				memcpy(attribute, attributeArray, 3 * sizeof(float));
			};

			float N[3] =
			{
				m_fLookAt[0] - m_fEye[0],
				m_fLookAt[1] - m_fEye[1],
				m_fLookAt[2] - m_fEye[2]
			};

			_updateCameraAttribute(N, rotateMatrix);
			m_fEye[0] = m_fLookAt[0] - N[0];
			m_fEye[1] = m_fLookAt[1] - N[1];
			m_fEye[2] = m_fLookAt[2] - N[2];

			_updateCameraAttribute(m_fUp, rotateMatrix);
		}

		bool LookAt(const Vector3f& worldCoord, float fDistance = 100.0f)
		{
			m_fLookAt[0] = worldCoord.x;
			m_fLookAt[1] = worldCoord.y;
			m_fLookAt[2] = worldCoord.z;

			memcpy(m_fEye, m_fLookAt, sizeof(float) * 3);
			m_fEye[0] -= fDistance;

			return true;
		}

		void UpdateViewPosUniform(GLuint shaderProgram)
		{
			GLint viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos");
			if (viewPosLocation == -1)
			{
				LeviathanOutStream << "[ERROR] Get viewPos uniform failed." << std::endl;
				return;
			}

			glUniform3f(viewPosLocation, m_fEye[0], m_fEye[1], m_fEye[2]);
		}

		float m_fEye[3];
		float m_fLookAt[3];
		float m_fUp[3];

		float m_fovy;
		float m_fAspect;
		float m_fZNear;
		float m_fZFar;
		const float m_minDistanceOfCameraToLookAt;
		float m_mouseOperationScaleRatio;
	};
}