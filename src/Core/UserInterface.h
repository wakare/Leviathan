#pragma once

namespace Leviathan
{
	class UserInterface
	{
	public:
		struct BaseData
		{
			int windowHandle;
		};

		static void Init(int width, int height, int parentHandle);
		static void UpdatePresenter();
		static void Stop();
		static const BaseData& GetData();

	private:
		static BaseData m_data;
	};
}