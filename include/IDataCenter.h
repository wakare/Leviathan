#pragma once

#include <memory>
#include "IResource.h"

namespace Leviathan
{
	class IDataCenter
	{
	public:
		virtual IResource& GetResource(ResourceHandle handle) = 0;
		virtual ResourceHandle LoadResource(std::unique_ptr<IResource> pResource) = 0;
	};

}