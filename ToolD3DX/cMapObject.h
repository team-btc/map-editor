#pragma once
#include "cSkinnedMesh.h"

class cSkinnedMesh;

class cMapObject
{
private:
    cSkinnedMesh*      m_pSkinnedMesh;

    Matrix4            m_matScale;
    Matrix4            m_matRot;    // X,Y,Z 가 모두 적용된 매트릭스 
    Matrix4            m_matTrans;
    Matrix4            m_matWorld;

    // 나중 저장을 위해 따로 만듬
    Vector3            m_vScale;
    Vector3            m_vRotXYZ;   // 회전 X, Y, Z의 값
    Vector3            m_vPosition;

    int                m_nId;       // 벡터 내에서 식별 값 

    // 이름 바꾸고 
    bool               m_isCrashable;      // 충돌 할 수 있는
    bool               m_isDestructible;   // 부실 수 있는
    

public:
    cMapObject();
    virtual ~cMapObject();
    cMapObject(string key, string filePath, string fileName);

    // 아이디
    int     GetId() { return m_nId; }
    void    SetId(int n) { m_nId = n; }
    
    // 스케일 
    Vector3 GetScale() { return m_vScale; }
    void    SetScale(Vector3 vScale) { m_vScale = vScale; }
    
    // 회전 
    Vector3 GetRotationXYZ() { return m_vRotXYZ; }
    void    SetRotationXYZ(Vector3 vRotationXYZ) { m_vRotXYZ = vRotationXYZ; }

    // 위치
    Vector3 GetPositon() { return m_vPosition; }
    void    SetPosition(Vector3 vPosition) { m_vPosition = vPosition; }
    
    // 월드
    Matrix4 GetWorldMatrix() { return m_matWorld; }
    void    SetWorldMatrix(Matrix4 matWorld) { m_matWorld = matWorld; }

    // 세팅
    void    Setup(Vector3 vScale, Vector3 vRotationXYZ, Vector3 vPosition);
    void    Render();

    // 매트릭스 갱신
    void    UpdateMatrix();

};

