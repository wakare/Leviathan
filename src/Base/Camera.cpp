#include <gl/glew.h>
#include "Camera.h"

namespace Leviathan
{
	void Camera::_getNUVVector(float* N, float* U, float* V)
	{
		N[0] = m_fLookAt[0] - m_fEye[0];
		N[1] = m_fLookAt[1] - m_fEye[1];
		N[2] = m_fLookAt[2] - m_fEye[2];

		Normalize<float, 3>(N);
		Vec3Cross(m_fUp, N, U, true);
		Vec3Cross(N, U, V, true);
	}

	float Camera::_getDistance()
	{
		float fDistance[3] =
		{
			m_fLookAt[0] - m_fEye[0],
			m_fLookAt[1] - m_fEye[1],
			m_fLookAt[2] - m_fEye[2],
		};

		return sqrtf(fDistance[0] * fDistance[0] + fDistance[1] * fDistance[1] + fDistance[2] * fDistance[2]);
	}

	bool Camera::_updateCurrentDistance(float newDistance /*= -1.0f*/)
	{
		m_currentDistance = (newDistance > 0.0f) ? newDistance : _getDistance();
		return true;
	}

	Camera::Camera(float* eye, float* lookAt, float* up, float fovy, float aspect, float zNear, float zFar) :
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

	Matrix4f Camera::GetViewportTransformMatrix()
	{
		float N[3];
		float U[3];
		float V[3];

		_getNUVVector(N, U, V);

		float data[16] =
		{
			U[0], U[1], U[2], -VecDot3f(U, m_fEye),
			V[0], V[1], V[2], -VecDot3f(V, m_fEye),
			N[0], N[1], N[2], -VecDot3f(N, m_fEye),
			0.0f, 0.0f, 0.0f,				  1.0f,
		};

		Matrix4f result = Matrix4f(data);
		return result;
	};

	Matrix4f Camera::GetPerspectiveTransformMatrix()
	{
		float T = tanf(m_fovy / 2.0f);
		float N = m_fZNear - m_fZFar;
		float M = m_fZNear + m_fZFar;
		float K = m_fAspect * T;
		float L = m_fZFar * m_fZNear;
		float data[16] =
		{
			1.0f / K,			0.0f,				0.0f,				0.0f,
			0.0f,				1.0f / T,			0.0f,				0.0f,
			0.0f,				0.0f,				-M / N ,			2 * L / N,
			0.0f,				0.0f,				1.0f,				0.0f
		};

		Matrix4f result = Matrix4f(data);
		return result;
	};

	void Camera::Translate(float x, float y, float z)
	{
		float N[3];
		float U[3];
		float V[3];

		_getNUVVector(N, U, V);
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
		_updateCurrentDistance();
	}

	void Camera::MouseDrag(float x, float y)
	{
		TargetTranslate(x * m_currentDistance, -y * m_currentDistance);
	}

	void Camera::MouseTranslate(float x, float y, float z)
	{
		float _lengthVec[3] = { m_fEye[0] - m_fLookAt[0], m_fEye[1] - m_fLookAt[1], m_fEye[2] - m_fLookAt[2] };
		float fLength = length<float, 3>(_lengthVec);
		float fScaleRatio = fLength * m_mouseOperationScaleRatio;

		return Translate(fScaleRatio * x, fScaleRatio * y, fScaleRatio * z);
	}

	void Camera::MouseRotate(float x, float y)
	{
		float N[3];
		float U[3];
		float V[3];

		_getNUVVector(N, U, V);
		memcpy(m_fUp, V, sizeof(float) * 3);

		float RotateVec[3] =
		{
			y * U[0] + x * V[0],
			y * U[1] + x * V[1],
			y * U[2] + x * V[2],
		};

		Rotate(RotateVec[0], RotateVec[1], RotateVec[2]);
	}

	void Camera::Rotate(float x, float y, float z)
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

	bool Camera::LookAt(const Vector3f& worldCoord, float fDistance /*= 100.0f*/)
	{
		float N[3], V[3], U[3];
		_getNUVVector(N, U, V);

		memcpy(m_fLookAt, &worldCoord.x, sizeof(float) * 3);
		_updateCurrentDistance(fDistance);

		m_fEye[0] = m_fLookAt[0] - m_currentDistance * N[0];
		m_fEye[1] = m_fLookAt[1] - m_currentDistance * N[1];
		m_fEye[2] = m_fLookAt[2] - m_currentDistance * N[2];

		return true;
	}

	void Camera::TargetTranslate(float x, float y)
	{
		float N[3], V[3], U[3];
		_getNUVVector(N, U, V);

		m_fLookAt[0] -= (U[0] * x + V[0] * y);
		m_fLookAt[1] -= (U[1] * x + V[1] * y);
		m_fLookAt[2] -= (U[2] * x + V[2] * y);

		m_fEye[0] = m_fLookAt[0] - m_currentDistance * N[0];
		m_fEye[1] = m_fLookAt[1] - m_currentDistance * N[1];
		m_fEye[2] = m_fLookAt[2] - m_currentDistance * N[2];
	}

	void Camera::UpdateViewPosUniform(unsigned shaderProgram)
	{
		int viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos");
		if (viewPosLocation == -1)
		{
			LeviathanOutStream << "[ERROR] Get viewPos uniform failed." << std::endl;
			return;
		}

		glUniform3f(viewPosLocation, m_fEye[0], m_fEye[1], m_fEye[2]);
	}
}