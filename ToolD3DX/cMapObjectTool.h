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

    void PickMouse();                                                                                                   // 마우스를 픽킹 했을 때 발동
};

