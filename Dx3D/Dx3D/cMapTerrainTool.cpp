#include "stdafx.h"
#include "cMapTerrainTool.h"


cMapTerrainTool::cMapTerrainTool()
{
}


cMapTerrainTool::~cMapTerrainTool()
{
}

HRESULT cMapTerrainTool::Setup(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType)
{
	// 가로 세로 사이즈 계산 후 맵 만들기
	int nSize = (eMapSize + 1) * 64;
	CreateNewMap(nSize, nSize);

	return S_OK;
}

HRESULT cMapTerrainTool::Update()
{
	return S_OK;
}

HRESULT cMapTerrainTool::Render()
{
	return S_OK;
}

// 크기 설정한 맵 생성, NewMap.raw 파일로 높이 저장 
HRESULT cMapTerrainTool::CreateNewMap(int SizeX, int SizeZ)
{
    // ex) 512 * 512
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
    //  0 , 1 , 2,  // 2 , 1 , 3 순서!!

    for (int z = 0; z < SizeZ; ++z)////////////////////////////////////////////////////////////////////////////////////////
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

    //// 버텍스 벡터
    //for (int n = 0; n < (SizeX + 1) * (SizeZ + 1); ++n)
    //{
    //    vec = Vector3(n % (SizeX + 1), DEFAULT_TERRAIN_HEIGHT, n / (SizeX + 1));
    //    m_vecVertex.push_back(vec);
    //    c << (char)vec.y;
    //}


	return S_OK;

}