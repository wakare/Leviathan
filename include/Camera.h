#pragma once

#include <memory>
#include <iostream>
#include "VectorOperation.h"
#include "BaseMath.h"
#include "GlobalDef.h"

namespace Leviathan
{
	class Camera
	{
	private:
		float _getDistance();
		void _getNUVVector(float* N, float* U, float* V);
		bool _updateCurrentDistance(float newDistance = -1.0f);

	public:
		enum class eCameraType
		{
			eObserveBallMode,
			eFPS,
		};

		Camera(float* eye, float* lookAt, float* up, float fovy, float aspect, float zNear, float zFar);
		Matrix4f GetViewportTransformMatrix();
		Matrix4f GetPerspectiveTransformMatrix();

		void Translate(float x, float y, float z);
		void MouseDrag(float x, float y);
		void MouseTranslate(float x, float y, float z);
		void MouseRotate(float x, float y);
		void Rotate(float x, float y, float z);
		bool LookAt(const Vector3f& worldCoord, float fDistance /*= 100.0f*/);
		void TargetTranslate(float x, float y);
		void UpdateViewPosUniform(unsigned shaderProgram);

		float m_fEye[3];
		float m_fLookAt[3];
		float m_fUp[3];

		float m_fovy;
		float m_fAspect;
		float m_fZNear;
		float m_fZFar;
		float m_currentDistance;
		float m_mouseOperationScaleRatio;
		const float m_minDistanceOfCameraToLookAt;
	};
}