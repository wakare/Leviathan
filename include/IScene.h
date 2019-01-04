#pragma once

namespace Leviathan
{
	class IScene
	{
	public:
		enum ESceneType
		{
			EST_COMMON,
			EST_POINTCLOUD,
			EST_TRID,
		};

		IScene() {}
		virtual ~IScene() {};

		virtual void Update() = 0;
	};
}