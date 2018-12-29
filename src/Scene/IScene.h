#pragma once
#include "GLCamera.h"
#include "LPtr.h"
#include <vector>
#include "GLLIght.h"

namespace Leviathan
{
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