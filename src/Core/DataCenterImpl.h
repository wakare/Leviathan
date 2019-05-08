#pragma once
#include "IDataCenter.h"
#include "DataStorer.h"
#include "IResource.h"

namespace Leviathan
{
	// TODO : Use datacenter class to manager all levObject
	class DataCenterImpl : public IDataCenter
	{
	public:
		DataCenterImpl();

		IResource& GetResource(ResourceHandle handle);
		ResourceHandle LoadResource(std::unique_ptr<IResource> pResource);

	private:
		std::unique_ptr<LevDataStorer> m_pDataStorer;
	};
}