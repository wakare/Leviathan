#pragma once
#include "LSPtr.h"

namespace Leviathan
{
	class PictureLoader
	{
	public:
		bool Load(const char* picture_path, LSPtr<RAIIBufferData>& out_data);
	};
}
