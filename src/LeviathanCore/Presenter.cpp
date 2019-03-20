#include "Presenter.h"

namespace Leviathan
{
	Presenter::Presenter() :
		m_pStateControl(new LevStateControl),
		m_pModelVisitor(new LevModelVisitor),
		m_pViewImpl(new LevViewImpl(*this))
	{

	}

	Leviathan::Presenter& Presenter::Instance()
	{
		return Singleton<Presenter>::Instance();
	}

	LevStateControl & Presenter::StateControl()
	{
		return *m_pStateControl;
	}

	LevModelVisitor & Presenter::ModelVisitor()
	{
		return *m_pModelVisitor;
	}

	Leviathan::LevViewImpl& Presenter::ViewImpl()
	{
		return *m_pViewImpl;
	}

}