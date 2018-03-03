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

	// 텍스쳐 셋팅
	g_pTextureManager->AddTexture("Grass", "Texture/Grass.jpg");

	return S_OK;
}

HRESULT cMapTerrainTool::Update()
{
	// 지형 높이 증가
	if (g_pKeyManager->isOnceKeyDown('U'))
	{

	}
	// 지형 높이 감소
	else if (g_pKeyManager->isOnceKeyDown('D'))
	{

	}
	// 텍스쳐 입히기
	else if (g_pKeyManager->isOnceKeyDown('T'))
	{

	}
	// 기본 텍스쳐로 변경 
	else if (g_pKeyManager->isOnceKeyDown('E'))
	{

	}
	// 와이어 프레임 출력
	else if (g_pKeyManager->isOnceKeyDown('W'))
	{

	}
	// 저장
	else if (g_pKeyManager->isOnceKeyDown('S'))
	{

	}
	// 로드
	else if (g_pKeyManager->isOnceKeyDown('L'))
	{
		
	}
	// 파일 경로
	else if (g_pKeyManager->isOnceKeyDown('1'))
	{

	}
	else if (g_pKeyManager->isOnceKeyDown('2'))
	{

	}
	else if (g_pKeyManager->isOnceKeyDown('3'))
	{

	}

	return S_OK;
}

HRESULT cMapTerrainTool::Render()
{
	Matrix4 matW;
	D3DXMatrixIdentity(&matW);

	g_pDevice->SetTransform(D3DTS_WORLD, &matW);
	g_pDevice->SetMaterial(&WHITE_MTRL);
	g_pDevice->SetTexture(0, g_pTextureManager->GetTexture("Grass"));
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	
	for each (auto stPT in m_vecPTVertex)
	{
		//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPNVertex.size() / 3,
		//	&m_vecPNVertex[0], sizeof(ST_PN_VERTEX));
	}

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);

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
            _0 = x + (SizeX + 1) * z;
            _1 = x + (SizeX + 1) * (z + 1);
            _2 = x + 1 + (SizeX + 1) * z;
            _3 = x + 1 + (SizeX + 1) * (z + 1);
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
        vec = Vector3(n % (SizeX + 1), DEFAULT_TERRAIN_HEIGHT, n / (SizeX + 1));
		m_vecPTVertex.push_back(ST_PT_VERTEX(vec, Vector2(n % (SizeX + 1), n / (SizeX + 1))));
        c << (char)vec.y;
    }



	return S_OK;

}


// 브러쉬 사이즈 설정 (브러쉬 사이즈)
HRESULT cMapTerrainTool::SetBrushSize(IN float fSize)
{
	return E_NOTIMPL;
}

// 브러쉬 농도 사이즈 설정(농도 사이즈)
HRESULT cMapTerrainTool::SetBrushDensity(IN float fSize)
{
	return E_NOTIMPL;
}

// 지형 높이 설정 (센터 포지션, 증감될 높이 값)
HRESULT cMapTerrainTool::SetHeight(IN Vector2 vPosition, IN float fHeight)
{
	return E_NOTIMPL;
}

// 텍스쳐의 밀도 설정 (증감될 밀도 값) : 이는 브러쉬의 속성을 설정해줌
HRESULT cMapTerrainTool::SetTextureDensity(IN float& fDensity)
{
	return E_NOTIMPL;
}

// 텍스쳐 타입 설정 (변경될 텍스쳐 타입)
HRESULT cMapTerrainTool::SetTextureType(IN E_GROUND_TYPE eGroundType)
{
	return E_NOTIMPL;
}

// 물 브러쉬 사이즈 설정 (물 브러쉬 사이즈)
HRESULT cMapTerrainTool::SetWaterBrushSize(IN float fSize)
{
	return E_NOTIMPL;
}

// 물의 유속 설정 (증감될 유속 값) : 물의 밀도와 움직임 값을 계산 및 설정
HRESULT cMapTerrainTool::SetWaterSpeed(IN float fSpeed)
{
	return E_NOTIMPL;
}

// 지형에 텍스쳐 입히기 (센터 포지션, 지형 타입)
HRESULT cMapTerrainTool::SetDrawTexture(IN Vector2 vPosition, IN E_GROUND_TYPE eGroundType)
{
	return E_NOTIMPL;
}

// 지형 높이 복제 (센터 포지션, 복제될 면 정보)
HRESULT cMapTerrainTool::SetDuplicateHeight(IN Vector2 vPosition, IN ST_TERRAIN_FACE_INFO stFaceInfo)
{
	return E_NOTIMPL;
}

// 지형맵 파일 저장하기
HRESULT cMapTerrainTool::SaveFile(IN string sFolderName, IN string sFileName)
{
	return E_NOTIMPL;
}

// 지형맵 파일 로드하기
HRESULT cMapTerrainTool::LoadFile(IN string sFolderName, IN string sFileName)
{
	return E_NOTIMPL;
}
