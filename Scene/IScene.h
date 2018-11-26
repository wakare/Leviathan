#pragma once
#include "GLCamera.h"
#include "LPtr.h"

namespace Leviathan
{
	class IScene
	{
	public:
		IScene() : m_pCamera(nullptr) {}
		virtual ~IScene() {};

		virtual void Update() = 0;
		GLCamera& GetCamera() { return *m_pCamera; }
	protected:
		LPtr<GLCamera> m_pCamera;
	};
}