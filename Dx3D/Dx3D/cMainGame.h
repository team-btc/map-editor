#pragma once

class cCamera;
class cMapTool;

class cMainGame
{
private:
    cCamera*                m_pCamera;

    LPEFFECT                m_pEffect;
    LPMESH                  m_pMesh;
    LPTEXTURE9              m_pDiffuseMap;
    LPTEXTURE9              m_pSpecularMap;
    cMapTool*               m_pMapTool;
public:
    cMainGame();
    ~cMainGame();

    void Setup();
    void Update();
    void Render();

    void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

