#pragma once
#include "Singleton.h"
#include "TriDScene.h"

class ModelViewerUserInterface
{
	DECLARE_SELF_TO_SINGLETON(ModelViewerUserInterface)
	
public:
	bool LoadFile(const char* fileName);
	static ModelViewerUserInterface& Instance();

private:
	ModelViewerUserInterface();
	//Leviathan::TriDScene& _scene();
};

