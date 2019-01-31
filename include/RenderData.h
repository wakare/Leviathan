#pragma once

#include "LPtr.h"
#include "GLObject.h"

namespace Leviathan
{
	class RenderData
	{
	public:
		RenderData(LPtr<GLObject> pGLObject);
		LPtr<GLObject> m_pGLObject;
	};

	inline RenderData::RenderData(LPtr<GLObject> pGLObject):
		m_pGLObject(pGLObject)	
	{

	}

}