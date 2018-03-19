#include "stdafx.h"
#include "cFontManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


cFontManager::cFontManager()
{
}

cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(eFontType e)
{
    // ã�� ��Ʈ�� ���� ��� ����
    if (m_mapFont.find(e) == m_mapFont.end())
    {
        switch (e)
        {
            case cFontManager::E_ALERT:
            {
                D3DXCreateFontA(g_pDevice,
                                75, 0,
                                FW_DONTCARE, 1, false, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, false,
                                "Consolas", &m_mapFont[e]);
                break;
            }
            case cFontManager::E_QUEST:
            {
                D3DXCreateFontA(g_pDevice,
                                25, 0,
                                FW_DONTCARE, 1, false, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, false,
                                "Consolas", &m_mapFont[e]);
                break;
            }
            case cFontManager::E_DEBUG:
            {
                D3DXCreateFontA(g_pDevice, 25, 0,
                                FW_DONTCARE, 1, false, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, false,
                                "Consolas", &m_mapFont[e]);
                break;
            }
            case cFontManager::E_NORMAL:
                break;
            case cFontManager::E_CHAT:
                break;
        }
    }

    return m_mapFont[e];
}

void cFontManager::Destory()
{
    for each (auto p in m_mapFont)
    {
        SAFE_RELEASE(p.second);
    }

    m_mapFont.clear();
}
