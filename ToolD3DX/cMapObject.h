#pragma once
#include "cSkinnedMesh.h"

class cSkinnedMesh;

class cMapObject
{
private:
    cSkinnedMesh*      m_pSkinnedMesh;

    Matrix4            m_matScale;
    Matrix4            m_matRot;    // X,Y,Z �� ��� ����� ��Ʈ���� 
    Matrix4            m_matTrans;
    Matrix4            m_matWorld;

    // ���� ������ ���� ���� ����
    Vector3            m_vScale;
    Vector3            m_vRotXYZ;   // ȸ�� X, Y, Z�� ��
    Vector3            m_vPosition;

    int                m_nId;       // ���� ������ �ĺ� �� 

    // �̸� �ٲٰ� 
    bool               m_isCrashable;      // �浹 �� �� �ִ�
    bool               m_isDestructible;   // �ν� �� �ִ�
    

public:
    cMapObject();
    virtual ~cMapObject();
    cMapObject(string key, string filePath, string fileName);

    // ���̵�
    int     GetId() { return m_nId; }
    void    SetId(int n) { m_nId = n; }
    
    // ������ 
    Vector3 GetScale() { return m_vScale; }
    void    SetScale(Vector3 vScale) { m_vScale = vScale; }
    
    // ȸ�� 
    Vector3 GetRotationXYZ() { return m_vRotXYZ; }
    void    SetRotationXYZ(Vector3 vRotationXYZ) { m_vRotXYZ = vRotationXYZ; }

    // ��ġ
    Vector3 GetPositon() { return m_vPosition; }
    void    SetPosition(Vector3 vPosition) { m_vPosition = vPosition; }
    
    // ����
    Matrix4 GetWorldMatrix() { return m_matWorld; }
    void    SetWorldMatrix(Matrix4 matWorld) { m_matWorld = matWorld; }

    // ����
    void    Setup(Vector3 vScale, Vector3 vRotationXYZ, Vector3 vPosition);
    void    Render();

    // ��Ʈ���� ����
    void    UpdateMatrix();

};

