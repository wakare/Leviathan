#pragma once

#include "Singleton.h"

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
		static bool LoadFile(const char * file);

	private:
		static BaseData m_data;
	};
}