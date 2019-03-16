#include "DataCenterImpl.h"

namespace Leviathan
{

	DataCenterImpl::DataCenterImpl():
		m_pDataStorer(new LevDataStorer())
	{

	}

	IResource& DataCenterImpl::GetResource(ResourceHandle handle)
	{
		return m_pDataStorer->Get(handle);
	}

	ResourceHandle DataCenterImpl::LoadResource(std::unique_ptr<IResource> pResource)
	{
		m_pDataStorer->Store(std::move(pResource));
	}

}