#include "stdafx.h"
#include "cMapDataManager.h"
#include "cMapTool.h"

cMapDataManager::cMapDataManager()
{
}


cMapDataManager::~cMapDataManager()
{
}

json cMapDataManager::SaveMapData(string strFileTitle)
{
    return m_pMapTool->SaveByJson(strFileTitle);
}

void cMapDataManager::LoadMapData(string strFileTitle)
{
    m_pMapTool->LoadByJson(strFileTitle);
}
