#pragma once

namespace Leviathan
{
	typedef unsigned ResourceHandle;

	enum EResourceType
	{
		ERT_MESH,
	};

	class IResource
	{
	public:
		virtual EResourceType Type() const = 0;
	};
}