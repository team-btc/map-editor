#include "stdafx.h"
#include "cBrush.h"



cBrush::cBrush()
{

}


cBrush::~cBrush()
{

}

void cBrush::SetBrush(Vector4 v, float br, float sr, float drawdensity, float tex1density, float tex2density, float tex3density)
{
    int nSize = (g_pMapDataManager->GetMapSize() + 1) * 64;

    m_pPick = v;
    m_fBrushRadius = br;
    m_fSprayRadius = sr;
    m_fDrawDensity = drawdensity;
    m_fTex1Density = tex1density;
    m_fTex2Density = tex2density;
    m_fTex3Density = tex3density;

    m_fPickX = v.x * nSize;
    m_fPickZ = v.z * nSize;
    m_fNR = br * nSize;
    m_fFR = sr * nSize;
    m_fdR = m_fFR - m_fNR;

    GetRect();
}

void cBrush::GetRect()
{
    int nSize = (g_pMapDataManager->GetMapSize() + 1) * 64;

    int nMinX = (m_pPick.x - m_fBrushRadius);
    if (nMinX < 0)
    {
        nMinX = 0;
    }

    int nMaxX = (m_pPick.x + m_fBrushRadius) * nSize + 1;
    if (nMaxX > nSize)
    {
        nMaxX = nSize;
    }

    int nMinZ = (m_pPick.z - m_fBrushRadius) * nSize;
    if (nMinZ < 0)
    {
        nMinZ = 0;
    }

    int nMaxZ = (m_pPick.z + m_fBrushRadius) * nSize + 1;
    if (nMaxZ > nSize)
    {
        nMaxZ = nSize;
    }

    m_nNearMaxX = nMaxX;
    m_nNearMaxZ = nMaxZ;
    m_nNearMinX = nMinX;
    m_nNearMinZ = nMinZ;

    nMinX = ((m_pPick.x - m_fSprayRadius) * nSize);
    if (nMinX < 0)
    {
        nMinX = 0;
    }

    nMaxX = ((m_pPick.x + m_fSprayRadius) * nSize + 1);
    if (nMaxX > nSize)
    {
        nMaxX = nSize;
    }

    nMinZ = ((m_pPick.z - m_fSprayRadius) * nSize);
    if (nMinZ < 0)
    {
        nMinZ = 0;
    }

    nMaxZ = ((m_pPick.z + m_fSprayRadius) * nSize + 1);
    if (nMaxZ > nSize)
    {
        nMaxZ = nSize;
    }

    m_nFarMaxX = nMaxX;
    m_nFarMaxZ = nMaxZ;
    m_nFarMinX = nMinX;
    m_nFarMinZ = nMinZ;
    
}
