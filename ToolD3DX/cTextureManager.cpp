#include "stdafx.h"
#include "cTextureManager.h"

cTextureManager::cTextureManager()
{

}

cTextureManager::~cTextureManager()
{

}

void cTextureManager::Destroy()
{
    auto iter = m_mapTexture.begin();
    for (; iter != m_mapTexture.end(); ++iter)
    {
        SAFE_RELEASE(iter->second);
    }

    m_mapTexture.clear();
}

void cTextureManager::AddTexture(string szKey, int nSize)
{
    AddTexture(szKey, nSize, nSize);
}

void cTextureManager::AddTexture(string szKey, int nWidth, int nHeight)
{
    HRESULT hr;
    LPTEXTURE9 t;
    hr = g_pDevice->CreateTexture(nWidth, nHeight, 1, 0,
        D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &t, NULL);

    D3DLOCKED_RECT  AlphaMap_Locked;
    memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));

    hr = t->LockRect(0, &AlphaMap_Locked, NULL, 0);
    LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;
    for (int j = 0; j < nHeight; ++j)
    {
        LPDWORD pDWordDST = (LPDWORD)(pDataDST + j * AlphaMap_Locked.Pitch);

        for (int i = 0; i < nWidth; ++i)
        {
            *(pDWordDST + i) = 0x00000000;
        }
    }
    hr = t->UnlockRect(0);

    m_mapTexture[szKey] = t;
}


void cTextureManager::AddTexture(string szKey, string szFilepath, bool saveImageInfo)
{
    HRESULT hr;
    if (m_mapTexture[szKey] == NULL)
    {
        LPTEXTURE9 t;
        if (saveImageInfo)
        {
            hr = D3DXCreateTextureFromFileExA(g_pDevice,
                szFilepath.c_str(),
                D3DX_DEFAULT_NONPOW2,
                D3DX_DEFAULT_NONPOW2,
                D3DX_DEFAULT,
                0,
                D3DFMT_UNKNOWN,
                D3DPOOL_MANAGED,
                D3DX_FILTER_NONE,
                D3DX_DEFAULT,
                0,
                &m_mapImageInfo[szKey],
                NULL,
                &t);

        }
        else
        {
            hr = D3DXCreateTextureFromFileA(g_pDevice,
                szFilepath.c_str(),
                &t);
        }

        if (hr == S_OK)
        {
            m_mapTexture[szKey] = t;
        }
#ifdef _DEBUG
        else
        {
            cout << "texture load error" << endl;
        }
#endif // _DEBUG
    }
}



void cTextureManager::AddCubeTexture(string szKey, string szFilepath)
{
    HRESULT hr;
    if (m_mapTexture[szKey] == NULL)
    {
        LPCUBETEXTURE9 t;
        hr = D3DXCreateCubeTextureFromFileA(g_pDevice,
            szFilepath.c_str(),
            &t);

        if (hr == S_OK)
        {
            m_mapTexture[szKey] = t;
        }
#ifdef _DEBUG
        else
        {
            cout << "cube texture load error" << endl;
        }
#endif // _DEBUG
    }
}

BASETEXTURE9* cTextureManager::GetTexture(string key, OUT IMAGE_INFO* pImageInfo)
{
    auto iter = m_mapTexture.find(key);

    if (iter != m_mapTexture.end())
    {
        if (pImageInfo)
        {
            auto iter2 = m_mapImageInfo.find(key);
            if (iter2 != m_mapImageInfo.end())
            {
                *pImageInfo = iter2->second;
            }
        }
        return iter->second;
    }
    else
    {
        return NULL;
    }
}