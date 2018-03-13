#include "stdafx.h"
#include "cMapDataManager.h"
#include "cMapTool.h"

cMapDataManager::cMapDataManager()
{
}


cMapDataManager::~cMapDataManager()
{
}

json cMapDataManager::SaveMapData()
{
    return m_pMapTool->SaveByJson();
}

void cMapDataManager::LoadMapData(string strFilepath, string strFileName)
{
    // strFilepath는 이름과 확장자명을 포함하고 있음
    //AddMapData();???
}
