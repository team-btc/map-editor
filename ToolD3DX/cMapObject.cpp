#include "stdafx.h"
#include "cMapObject.h"
#include "cSkinnedMesh.h"

cMapObject::cMapObject()
{
    D3DXMatrixIdentity(&m_matScale);
    D3DXMatrixIdentity(&m_matRot);
    D3DXMatrixIdentity(&m_matTrans);
    D3DXMatrixIdentity(&m_matWorld);
    m_nId = -1;
}

cMapObject::cMapObject(string key, string filePath, string fileName)
{
    cMapObject();
    m_pSkinnedMesh = g_pMeshManager->GetMesh(key, filePath, fileName);
}

cMapObject::~cMapObject()
{}

void cMapObject::Setup(Matrix4 Scale, Matrix4 Rotation, Matrix4 Translation)
{
    m_matScale = Scale;
    m_matRot = Rotation;
    m_matTrans = Translation;
    m_matWorld = m_matScale * m_matRot * m_matTrans;
}

void cMapObject::Render()
{
    if(this != NULL)
        m_pSkinnedMesh->UpdateAndRender(&m_matWorld);
}
