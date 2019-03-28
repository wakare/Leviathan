#pragma once

namespace Leviathan
{
	struct BaseData
	{

	};

	class UserInterface
	{
	public:
		static void Init(int width, int height, int parentHandle);
		static void Update();
		static void Stop();
		static BaseData GetData();

	private:
		static BaseData m_data;
	};
}