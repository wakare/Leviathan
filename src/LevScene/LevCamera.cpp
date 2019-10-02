#include "LevCamera.h"

namespace Leviathan
{
	namespace Scene
	{
		LevCamera::LevCamera()
			: LevSceneObject(ELSOT_CAMERA | ELSOT_UNRENDERABLE |ELSOT_DYNAMIC)
			, m_receive_input(true)
		{
			SetRecalculateWorldTransform(false);
		}

		void LevCamera::_getNUVVector(Eigen::Vector3f& N, Eigen::Vector3f& U, Eigen::Vector3f& V) const
		{
			N = m_fLookAt - m_fEye;
			N.normalize();
			U = m_fUp.cross(N);
			U.normalize();
			V = N.cross(U);
			V.normalize();
		}

		float LevCamera::_getDistance()
		{
			float fDistance[3] =
			{
				m_fLookAt[0] - m_fEye[0],
				m_fLookAt[1] - m_fEye[1],
				m_fLookAt[2] - m_fEye[2],
			};

			return sqrtf(fDistance[0] * fDistance[0] + fDistance[1] * fDistance[1] + fDistance[2] * fDistance[2]);
		}

		bool LevCamera::_updateCurrentDistance(float newDistance /*= -1.0f*/)
		{
			m_currentDistance = (newDistance > 0.0f) ? newDistance : _getDistance();
			return true;
		}

		void LevCamera::_setEyePosition(const Eigen::Vector3f & position)
		{
			m_fEye = position;
			Eigen::Matrix4f cameraWorldTransform = Eigen::Matrix4f::Identity();
			cameraWorldTransform(0, 3) = m_fEye[0];
			cameraWorldTransform(1, 3) = m_fEye[1];
			cameraWorldTransform(2, 3) = m_fEye[2];
			SetWorldTransform(cameraWorldTransform);
		}

		bool LevCamera::Set(float* eye, float* lookAt, float* up, float fovy, float aspect, float zNear, float zFar)
		{
			m_minDistanceOfCameraToLookAt = 0.01f;
			m_mouseOperationScaleRatio = 1.0f;

			EXIT_IF_FALSE(Set(eye, lookAt, up));
			EXIT_IF_FALSE(Set(fovy, aspect, zNear, zFar));

			return true;
		}

		bool LevCamera::Set(float * eye, float * lookAt, float * up)
		{
			memcpy(m_fEye.data(), eye, sizeof(float) * 3);
			memcpy(m_fLookAt.data(), lookAt, sizeof(float) * 3);
			memcpy(m_fUp.data(), up, sizeof(float) * 3);

			_setEyePosition(m_fEye);
			_updateCurrentDistance();
			SetModified();
			return true;
		}

		bool LevCamera::Set(float fovy, float aspect, float zNear, float zFar)
		{
			m_fovy = fovy;
			m_fAspect = aspect;
			m_fZNear = zNear;
			m_fZFar = zFar;

			SetModified();
			return true;
		}

		Eigen::Matrix4f LevCamera::GetViewportMatrix() const
		{
			Eigen::Vector3f N, U, V;
			_getNUVVector(N, U, V);

			float data[16] =
			{
				U[0], U[1], U[2], -U.dot(m_fEye),
				V[0], V[1], V[2], -V.dot(m_fEye),
				N[0], N[1], N[2], -N.dot(m_fEye),
				0.0f, 0.0f, 0.0f,			1.0f,
			};

			return Eigen::Matrix4f(data).transpose();
		};

		Eigen::Matrix4f LevCamera::GetProjectMatrix() const
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
				0.0f,				0.0f,			  -M / N,		   2 * L / N,
				0.0f,				0.0f,				1.0f,				0.0f
			};

			return Eigen::Matrix4f(data).transpose();
		}

		const Eigen::Vector3f & LevCamera::GetEyePos() const
		{
			return m_fEye;
		}

		void LevCamera::Translate(float x, float y, float z)
		{
			Eigen::Vector3f N, U, V;
			_getNUVVector(N, U, V);
			m_fUp = V;

			float _newEyeCoord[3] =
			{
				m_fEye[0] + (x * U[0] + y * V[0] + z * N[0]),
				m_fEye[1] + (x * U[1] + y * V[1] + z * N[1]),
				m_fEye[2] + (x * U[2] + y * V[2] + z * N[2])
			};

			Eigen::Vector3f newEyeCoord;
			memcpy(newEyeCoord.data(), _newEyeCoord, 3 * sizeof(float));
			Eigen::Vector3f _N = m_fLookAt - newEyeCoord;

			if (_N.norm() < m_minDistanceOfCameraToLookAt)
			{
				LeviathanOutStream << "Arrive minDistanceOfCameraToLookAt." << std::endl;
				return;
			}

			_setEyePosition(newEyeCoord);
			_updateCurrentDistance();
		}

		void LevCamera::MouseDrag(float x, float y)
		{
			if (!m_receive_input)
			{
				return;
			}

			TargetTranslate(x * m_currentDistance, -y * m_currentDistance);
			SetModified();
		}

		void LevCamera::MouseTranslate(float x, float y, float z)
		{
			if (!m_receive_input)
			{
				return;
			}

			float length = (m_fEye - m_fLookAt).norm();
			float scaleRatio = length * m_mouseOperationScaleRatio;

			Translate(scaleRatio * x, scaleRatio * y, scaleRatio * z);
			SetModified();
		}

		void LevCamera::MouseRotate(float x, float y)
		{
			if (!m_receive_input)
			{
				return;
			}

			Eigen::Vector3f N, U, V;
			_getNUVVector(N, U, V);
			m_fUp = V;

			float RotateVec[3] =
			{
				y * U[0] + x * V[0],
				y * U[1] + x * V[1],
				y * U[2] + x * V[2],
			};

			Rotate(RotateVec[0], RotateVec[1], RotateVec[2]);
			SetModified();
		}

		void LevCamera::Rotate(float x, float y, float z)
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

			Eigen::Matrix4f xMatrix(reinterpret_cast<float*>(XRotate));
			Eigen::Matrix4f yMatrix(reinterpret_cast<float*>(YRotate));
			Eigen::Matrix4f zMatrix(reinterpret_cast<float*>(ZRotate));

			Eigen::Matrix4f rotateMatrix = xMatrix * yMatrix * zMatrix;

			static auto _updateCameraAttribute = [](Eigen::Vector3f& attribute, const Eigen::Matrix4f& rotateMatrix)
			{
				Eigen::Vector4f attributeVector; 
				attributeVector[0] = attribute[0];
				attributeVector[1] = attribute[1];
				attributeVector[2] = attribute[2];
				attributeVector[3] = 1.0f;
				attributeVector = rotateMatrix * attributeVector;

				if (fabs(attributeVector[3]) < FLT_EPSILON)
				{
					throw "Error attribute array.";
				}

				attributeVector[0] /= attributeVector[3];
				attributeVector[1] /= attributeVector[3];
				attributeVector[2] /= attributeVector[3];

				memcpy(attribute.data(), attributeVector.data(), sizeof(float) * 3);
			};

			Eigen::Vector3f N = m_fLookAt - m_fEye;
			_updateCameraAttribute(N, rotateMatrix);

			_setEyePosition(m_fLookAt - N);
			_updateCameraAttribute(m_fUp, rotateMatrix);
		}

		bool LevCamera::LookAt(const Eigen::Vector3f& worldCoord, float fDistance /*= 100.0f*/)
		{
			Eigen::Vector3f N, U, V;
			_getNUVVector(N, U, V);

			m_fLookAt = worldCoord;
			_updateCurrentDistance(fDistance);

			_setEyePosition(m_fLookAt - m_currentDistance * N);

			if (m_fZFar < 4 * fDistance)
			{
				m_fZFar = 4 * fDistance;
			}
			
			SetModified();
			return true;
		}

		void LevCamera::TargetTranslate(float x, float y)
		{
			//_updateCurrentDistance();

			Eigen::Vector3f N, U, V;
			_getNUVVector(N, U, V);

			m_fLookAt[0] -= (U[0] * x + V[0] * y);
			m_fLookAt[1] -= (U[1] * x + V[1] * y);
			m_fLookAt[2] -= (U[2] * x + V[2] * y);

			_setEyePosition(m_fLookAt - m_currentDistance * N);

			SetModified();
		}

		void LevCamera::SetReceiveInput(bool receive)
		{
			m_receive_input = receive;
		}
	}
}