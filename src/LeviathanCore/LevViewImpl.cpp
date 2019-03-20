#include "LevViewimpl.h"

namespace Leviathan
{
	LevViewImpl::LevViewImpl(Presenter& presenter):
		m_presenter(presenter),
		m_pView(new View(presenter))
	{

	}
}