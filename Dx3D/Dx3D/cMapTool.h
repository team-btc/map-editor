#pragma once
#define DEFAULT_Y   128
class cMapTool
{
private:
    vector<Vector3> m_vecVertex;                // �ʿ� ����� �� ����
    vector<int> m_vecVertexIndex;               // Height�� ��ǥ �ε��� ����

public:
    void CreateNewMap(int SizeX, int SizeZ);            // ũ�� ������ �� ����

    cMapTool();
    ~cMapTool();
};

