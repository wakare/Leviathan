#pragma once
#include "GLPass.h"

namespace Leviathan
{
	class IDrawable
	{
	public:
		IDrawable() {};

		// Register self to GLPass
		virtual bool RegisterSelfToGLPass(GLPass& refPass) {};
		virtual bool RemoveSelfFromGLPass(GLPass& refPass) {};

		virtual ~IDrawable() {};
	};
}