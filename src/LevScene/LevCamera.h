#pragma once

#include <Eigen/Dense>
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevCamera : public LevSceneObject
		{
		public:
			enum class CameraType
			{
				eObserveBallMode,
				eFPS,
			};

			LevCamera();

			bool Set(float* eye, float* lookAt, float* up, float fovy, float aspect, float zNear, float zFar);
			Eigen::Matrix4f GetViewportMatrix() const;
			Eigen::Matrix4f GetPerspectiveMatrix() const;
			const Eigen::Vector3f& GetEyePos() const;

			void Translate(float x, float y, float z);
			void MouseDrag(float x, float y);
			void MouseTranslate(float x, float y, float z);
			void MouseRotate(float x, float y);
			void Rotate(float x, float y, float z);
			bool LookAt(const Eigen::Vector3f& worldCoord, float fDistance /*= 100.0f*/);
			void TargetTranslate(float x, float y);

		private:
			float _getDistance();
			void _getNUVVector(Eigen::Vector3f& N, Eigen::Vector3f& U, Eigen::Vector3f& V) const;
			bool _updateCurrentDistance(float newDistance = -1.0f);

			Eigen::Vector3f m_fEye;
			Eigen::Vector3f m_fLookAt;
			Eigen::Vector3f m_fUp;

			float m_fovy;
			float m_fAspect;
			float m_fZNear;
			float m_fZFar;
			float m_currentDistance;
			float m_mouseOperationScaleRatio;
			float m_minDistanceOfCameraToLookAt;
		};
	}
}