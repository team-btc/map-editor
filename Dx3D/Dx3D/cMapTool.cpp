#include "stdafx.h"
#include "cMapTool.h"


cMapTool::cMapTool()
{
}


cMapTool::~cMapTool()
{
}

// 크기 설정한 맵 생성, NewMap.raw 파일로 높이 저장 
// Defalut 128
void cMapTool::CreateNewMap(int SizeX, int SizeZ)
{
    // ex) 128 * 128
    Vector3 vec;
    int _0;
    int _1;
    int _2;
    int _3;
    ofstream c; 
    c.open("NewMap.raw");

    // 인덱스 벡터                   

    //   1 3
    //   0 2

    for (int z = 0; z < SizeZ; ++z)
    {
        for (int x = 0; x < SizeX; ++x)
        {
            _0 = x + (SizeX + 1) * (z + 1);
            _1 = x + (SizeX + 1) * z;
            _2 = x + 1 + (SizeX + 1) * (z + 1);
            _3 = x + 1 + (SizeX + 1) * z;
            m_vecVertexIndex.push_back(_0);
            m_vecVertexIndex.push_back(_1);
            m_vecVertexIndex.push_back(_2);
            m_vecVertexIndex.push_back(_2);
            m_vecVertexIndex.push_back(_1);
            m_vecVertexIndex.push_back(_3);
        }

    }

    // 버텍스 벡터
    for (int n = 0; n < (SizeX + 1) * (SizeZ + 1); ++n)
    {
        vec = Vector3(n % (SizeX + 1), DEFAULT_Y, n / (SizeX + 1));
        m_vecVertex.push_back(vec);
        c << (char)vec.y;
    }

  
   
    
}
