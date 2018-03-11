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

    void OnceLButtonDown();                                                                     // 마우스 왼쪽 버튼을 클릭 했을 때 발동
    void StayLButtonDown();                                                                     // 마우스 왼쪽 버튼을 계속 누르고 있을 때 발동
};

