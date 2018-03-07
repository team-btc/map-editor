#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
    SINGLETON(cTextureManager);
private:
    map<string, BASETEXTURE9*>  m_mapTexture;
    map<string, IMAGE_INFO>     m_mapImageInfo;
public:
    void Destroy();
    void AddTexture(string szKey, int nSize);
    void AddTexture(string szKey, int nWidth, int nHeight);
    void AddTexture(string szKey, string szFilepath, bool saveImageInfo = false);
    void AddCubeTexture(string szKey, string szFilepath);
    BASETEXTURE9* GetTexture(string szKey, OUT IMAGE_INFO* pImageInfo = NULL);

    void SaveTexture(string szKey, string szFilepath, D3DXIMAGE_FILEFORMAT format = D3DXIFF_PNG);
    void SaveTexture(BASETEXTURE9* pTexture, string szFilepath, D3DXIMAGE_FILEFORMAT format = D3DXIFF_PNG);
};