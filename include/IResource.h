#pragma once

namespace Leviathan
{
	typedef unsigned ResourceHandle;

	enum EResourceType
	{
		ERT_MESH,
		ERT_LIGHT,
	};

	class IResource
	{
	public:
		IResource()
		{
			static ResourceHandle _res_handle = 0;
			m_handle = _res_handle++;
		}

		virtual ~IResource() = default;

		virtual EResourceType Type() const = 0;

	private:
		ResourceHandle m_handle;
	};
}