#pragma once
#include "cSkinnedMesh.h"

class cSkinnedMesh;

class cMapObject
{
private:
    cSkinnedMesh*      m_pSkinnedMesh;
    Matrix4            m_matScale;
    Matrix4            m_matRot;
    Matrix4            m_matTrans;
    Matrix4            m_matWorld;
    int                m_nId;

public:
    cMapObject();
    virtual ~cMapObject();
    cMapObject(string key, string filePath, string fileName);

    void Setup(Matrix4 Scale, Matrix4 Rotation, Matrix4 Translation);
    void Render();

    void    SetId(int n) { m_nId = n; }
    int     GetId() { return m_nId; }
    Matrix4 GetWorldMatrix() { return m_matWorld; }
};

