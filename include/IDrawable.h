#pragma once

#include "GLPass.h"

namespace Leviathan
{
	class IDrawable
	{
	public:
		IDrawable() {};

		// Register self to GLPass
		virtual bool RegisterSelfToGLPass(GLPass& refPass) { return false; };
		virtual bool RemoveSelfFromGLPass(GLPass& refPass) { return false; };

		virtual ~IDrawable() {};
	};
}