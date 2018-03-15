#pragma once
#include "cSkinnedMesh.h"

class cMapObject
{
private:
    // ���ο��� Ȱ���� �� //
    cSkinnedMesh*           m_pSkinnedMesh;     // ��Ų�� �޽�
    Matrix4                 m_matScale;         // ������, ���� �� �ݺ� 
    Matrix4                 m_matRot;           // X,Y,Z �� ��� ����� ��Ʈ���� 
    Matrix4                 m_matTrans;         
    Matrix4                 m_matWorld;
    int                     m_nId;              // Object ���� ������ �ĺ� �� 
    // ������ �ڷ� //        
    Vector3                 m_vScale;           // ������
    Vector3                 m_vRotXYZ;          // ȸ�� X, Y, Z
    Vector3                 m_vPosition;        // ��ġ
    string                  m_sKey;             // �޽�Ű
    string                  m_sFilePath;        // ���� ���
    string                  m_sFileName;        // �����̸�
    bool                    m_isCollision;      // �浹 �� �� �ִ�
    bool                    m_isDestruction;    // �ν� �� �ִ�
    bool                    m_isEnemy;

public:
    cMapObject();
    cMapObject(string key, string filePath, string fileName);
    virtual ~cMapObject();
    /*----------- ���� Ȱ��� -------------*/
    // ���̵�
    int     GetId() { return m_nId; }         
    void    SetId(int n) { m_nId = n; }

	Matrix4 GetRotMatrix() { return m_matRot; }
	Matrix4 GetTransMatrix() { return m_matTrans; }
    // ����
    Matrix4 GetWorldMatrix() { return m_matWorld; }
    void    SetWorldMatrix(Matrix4 matWorld) { m_matWorld = matWorld; }
    // ����
    void    Setup(Vector3 vScale, Vector3 vRotationXYZ, Vector3 vPosition);
    // ����
    void    Render();
    // ���� ��Ʈ���� ����
    void    UpdateMatrix();
    void    UpdateMatrix(Vector3 vPos);
    /*----------- ���� �� -------------*/
    // ������ 
    Vector3 GetScale() const { return m_vScale; }
    void    SetScale(Vector3 vScale) { m_vScale = vScale; }
    // ȸ�� 
    Vector3 GetRotationXYZ() const { return m_vRotXYZ; }
    void    SetRotationXYZ(Vector3 vRotationXYZ) { m_vRotXYZ = vRotationXYZ; }
    // ��ġ
    Vector3 GetPositon() const { return m_vPosition; }
    void    SetPosition(Vector3 vPosition) { m_vPosition = vPosition; }
    // Ű 
    string  GetKey() const { return m_sKey; }
    void    SetKey(string sMeshKey) { m_sKey = sMeshKey; }
    // ���� �н�
    string  GetFilePath() const { return m_sFilePath; }
    void    SetFilePath(string sFilePath) { m_sFilePath = sFilePath; }
    // ���� �� 
    string  GetFileName() const { return m_sFileName; }
    void    SetFileName(string sFileName) { m_sFileName = sFileName; }
    // �浹���� ���� 
    bool    GetCollision() const { return m_isCollision; }
    void    SetCollision(bool collision) { m_isCollision = collision; }
    // �μ������� ����
    bool    GetDestruction() const { return m_isDestruction; }
    void    SetDestruction(bool destruction) { m_isDestruction = destruction; }
    // �������� �ǹ����� ����
    bool    GetEnemy() const { return m_isEnemy; }
    void    SetEnemy(bool enemy) { m_isEnemy = enemy; }
};