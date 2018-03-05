#pragma once

#include "cObject.h"

class cMapObjectTool : public cObject
{
private:

private:

public:
    cMapObjectTool();
    ~cMapObjectTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();
};

