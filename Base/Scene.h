#pragma once
#include "GLCamera.h"
#include "RenderWrapper.h"

class Scene
{
public:
	Scene();

	virtual void Update();

private:
	std::shared_ptr<GLCamera> m_pCamera;
	std::shared_ptr<RenderWrapper> m_pRenderWarpper;
};