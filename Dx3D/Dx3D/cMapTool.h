#pragma once
#define DEFAULT_Y   128
class cMapTool
{
private:
    vector<Vector3> m_vecVertex;                // ¸Ê¿¡ »ç¿ëÇÒ Á¡ º¤ÅÍ
    vector<int> m_vecVertexIndex;               // Height¸Ê ÁÂÇ¥ ÀÎµ¦½º º¤ÅÍ

public:
    void CreateNewMap(int SizeX, int SizeZ);            // Å©±â ¼³Á¤ÇÑ ¸Ê »ý¼º

    cMapTool();
    ~cMapTool();
};

