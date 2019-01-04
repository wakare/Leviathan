#pragma once

namespace Leviathan
{
	class IScene
	{
	public:
		IScene() {}
		virtual ~IScene() {};

		virtual void Update() = 0;
	};
}