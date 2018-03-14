#include "stdafx.h"
#include "cMapDataManager.h"
#include "cMapTool.h"

cMapDataManager::cMapDataManager()
{
}


cMapDataManager::~cMapDataManager()
{
}

void cMapDataManager::SetMapData()
{
    g_pTextureManager->AddTexture("Soil.jpg", "Texture/Soil.jpg");
    g_pTextureManager->AddTexture("Grass.jpg", "Texture/Grass.jpg");
    g_pTextureManager->AddTexture("Stone.jpg", "Texture/Stone.jpg");
    g_pTextureManager->AddTexture("Cement.jpg", "Texture/Cement.jpg");
    g_pTextureManager->AddTexture("Drymud.jpg", "Texture/Drymud.jpg");
    g_pTextureManager->AddTexture("DarkSky.jpg", "Texture/DarkSky.jpg");
    g_pTextureManager->AddTexture("Rocky.jpg", "Texture/Rocky.jpg");
    g_pTextureManager->AddTexture("Snow.jpg", "Texture/Snow.jpg");
    g_pTextureManager->AddTexture("Lava.jpg", "Texture/Lava.jpg");
    g_pTextureManager->AddTexture("Space.jpg", "Texture/Space.jpg");
    g_pTextureManager->AddTexture("mecha.jpg", "Texture/mecha.jpg");


    g_pTextureManager->AddTexture("Water.jpg", "Shader/Texture/Water.jpg");
    g_pTextureManager->AddTexture("Magma.jpg", "Shader/Texture/magma.jpg");


    g_pTextureManager->AddTexture("Cloudy.dds", "Shader/Texture/Cloudy.dds");
    g_pTextureManager->AddTexture("DeepNight.dds", "Shader/Texture/DeepNight.dds");
    g_pTextureManager->AddTexture("Interstellar.dds", "Shader/Texture/Interstellar.dds");
    g_pTextureManager->AddTexture("Islands.dds", "Shader/Texture/Islands.dds");
    g_pTextureManager->AddTexture("MidNight.dds", "Shader/Texture/MidNight.dds");
    g_pTextureManager->AddTexture("SkyBlue.dds", "Shader/Texture/SkyBlue.dds");
    g_pTextureManager->AddTexture("Volcano.dds", "Shader/Texture/Volcano.dds");

}

json cMapDataManager::SaveMapData(string strFilePath, string strFileTitle)
{
    return m_pMapTool->SaveByJson(strFilePath, strFileTitle);
}

void cMapDataManager::LoadMapData(string strFileTitle)
{
    m_pMapTool->LoadByJson(strFileTitle);
}
