#pragma once
#include "GLPass.h"

class TriDObjectGLPass : public GLPass
{
public:
	virtual bool Init();
	virtual void Render();
};