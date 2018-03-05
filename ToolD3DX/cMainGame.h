#pragma once
#include "d3dapp.h"
#include <d3dx9math.h>
#include <D3dx9shape.h>

#include "cCamera.h"
#include "cMapTool.h"

class cMainGame : public CD3DApp
{
private:
    cCamera*		m_pCamera;

    Vector3			m_vRot;

    CStringA		m_szText;

	cMapTool*		m_pMapTool;

public:
    cMainGame(void);
    ~cMainGame(void);

private:
    virtual void OnInit();
    virtual void OnRender();
    virtual void OnUpdate();
    virtual void OnRelease();

public:
    void SetText(CStringA szText) { m_szText = szText; }
};

