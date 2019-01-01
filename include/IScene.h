#pragma once

#include "LPtr.h"
#include <vector>

namespace Leviathan
{
	class GLCamera;
	class GLLight;

	class IScene
	{
	public:
		IScene() : m_pCamera(nullptr) {}
		virtual ~IScene() {};

		virtual void Update() = 0;
		GLCamera& GetCamera() { return *m_pCamera; }
		std::vector<LPtr<GLLight>>& GetLightVec() { return m_pLights; }

	protected:
		LPtr<GLCamera> m_pCamera;
		std::vector<LPtr<GLLight>> m_pLights;
	};
}