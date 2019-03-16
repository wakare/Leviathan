#include "Presenter.h"

namespace Leviathan
{
	Presenter::Presenter() :
		m_pStateControl(new LevStateControl),
		m_pModelVisitor(new LevModelVisitor)
	{

	}

	LevStateControl & Presenter::StateControl()
	{
		return *m_pStateControl;
	}

	LevModelVisitor & Presenter::ModelVisitor()
	{
		return *m_pModelVisitor;
	}
}