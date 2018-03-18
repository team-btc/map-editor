#include "stdafx.h"
#include "cMapObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cMapObject::cMapObject()
{
    m_pSkinnedMesh = NULL;
    D3DXMatrixIdentity(&m_matScale);
    D3DXMatrixIdentity(&m_matRot);
    D3DXMatrixIdentity(&m_matTrans);
    D3DXMatrixIdentity(&m_matWorld);
    m_nId = -1;
    m_vScale = Vector3(1, 1, 1);
    m_vRotXYZ = Vector3(0, 0, 0);
    m_vPosition = Vector3(0, 0, 0);
    m_isCollision = false;
    m_isDestruction = false;
    m_isEnemy = false;
}

cMapObject::cMapObject(string key, string filePath, string fileName)
{
    cMapObject();
    m_pSkinnedMesh = g_pMeshManager->GetMesh(key, filePath, fileName);
}

cMapObject::~cMapObject()
{
    m_pSkinnedMesh = NULL;
}

void cMapObject::Setup(Vector3 vScale, Vector3 vRotationXYZ, Vector3 vPosition)
{
    m_vScale = vScale;
    m_vRotXYZ = vRotationXYZ;
    m_vPosition = vPosition;
    // ��Ʈ���� ���� 
    UpdateMatrix();
}

void cMapObject::Render()
{
    m_pSkinnedMesh->UpdateAndRender(&m_matWorld);
}

void cMapObject::UpdateMatrix()
{
    Matrix4 rotX, rotY, rotZ;

    D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);

    D3DXMatrixRotationX(&rotX, m_vRotXYZ.x);
    D3DXMatrixRotationY(&rotY, m_vRotXYZ.y);
    D3DXMatrixRotationZ(&rotZ, m_vRotXYZ.z);
    m_matRot = rotX * rotY * rotZ;

    D3DXMatrixTranslation(&m_matTrans, m_vPosition.x, m_vPosition.y, m_vPosition.z);
    m_matWorld = m_matScale * m_matRot * m_matTrans;
}

void cMapObject::UpdateMatrix(Vector3 vPos)
{
    m_vPosition = vPos;
    D3DXMatrixTranslation(&m_matTrans, m_vPosition.x, m_vPosition.y, m_vPosition.z);

    m_matWorld = m_matScale * m_matRot * m_matTrans;
}
