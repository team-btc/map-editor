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
    // strFilepath�� �̸��� Ȯ���ڸ��� �����ϰ� ����
    //AddMapData();???
}
