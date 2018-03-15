#pragma once
#include "cSkinnedMesh.h"

class cMapObject
{
private:
    // 내부에서 활용할 값 //
    cSkinnedMesh*           m_pSkinnedMesh;     // 스킨드 메쉬
    Matrix4                 m_matScale;         // 스케일, 같은 값 반복 
    Matrix4                 m_matRot;           // X,Y,Z 가 모두 적용된 매트릭스 
    Matrix4                 m_matTrans;         
    Matrix4                 m_matWorld;
    int                     m_nId;              // Object 벡터 내에서 식별 값 
    // 저장할 자료 //        
    Vector3                 m_vScale;           // 스케일
    Vector3                 m_vRotXYZ;          // 회전 X, Y, Z
    Vector3                 m_vPosition;        // 위치
    string                  m_sKey;             // 메쉬키
    string                  m_sFilePath;        // 파일 경로
    string                  m_sFileName;        // 파일이름
    bool                    m_isCollision;      // 충돌 할 수 있는
    bool                    m_isDestruction;    // 부실 수 있는
    bool                    m_isEnemy;

public:
    cMapObject();
    cMapObject(string key, string filePath, string fileName);
    virtual ~cMapObject();
    /*----------- 내부 활용용 -------------*/
    // 아이디
    int     GetId() { return m_nId; }         
    void    SetId(int n) { m_nId = n; }

	Matrix4 GetRotMatrix() { return m_matRot; }
	Matrix4 GetTransMatrix() { return m_matTrans; }
    // 월드
    Matrix4 GetWorldMatrix() { return m_matWorld; }
    void    SetWorldMatrix(Matrix4 matWorld) { m_matWorld = matWorld; }
    // 세팅
    void    Setup(Vector3 vScale, Vector3 vRotationXYZ, Vector3 vPosition);
    // 렌더
    void    Render();
    // 월드 매트릭스 갱신
    void    UpdateMatrix();
    void    UpdateMatrix(Vector3 vPos);
    /*----------- 저장 용 -------------*/
    // 스케일 
    Vector3 GetScale() const { return m_vScale; }
    void    SetScale(Vector3 vScale) { m_vScale = vScale; }
    // 회전 
    Vector3 GetRotationXYZ() const { return m_vRotXYZ; }
    void    SetRotationXYZ(Vector3 vRotationXYZ) { m_vRotXYZ = vRotationXYZ; }
    // 위치
    Vector3 GetPositon() const { return m_vPosition; }
    void    SetPosition(Vector3 vPosition) { m_vPosition = vPosition; }
    // 키 
    string  GetKey() const { return m_sKey; }
    void    SetKey(string sMeshKey) { m_sKey = sMeshKey; }
    // 파일 패스
    string  GetFilePath() const { return m_sFilePath; }
    void    SetFilePath(string sFilePath) { m_sFilePath = sFilePath; }
    // 파일 명 
    string  GetFileName() const { return m_sFileName; }
    void    SetFileName(string sFileName) { m_sFileName = sFileName; }
    // 충돌가능 여부 
    bool    GetCollision() const { return m_isCollision; }
    void    SetCollision(bool collision) { m_isCollision = collision; }
    // 부서지는지 여부
    bool    GetDestruction() const { return m_isDestruction; }
    void    SetDestruction(bool destruction) { m_isDestruction = destruction; }
    // 몬스터인지 건물인지 여부
    bool    GetEnemy() const { return m_isEnemy; }
    void    SetEnemy(bool enemy) { m_isEnemy = enemy; }
};