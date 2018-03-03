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
	// ���� ���� ������ ��� �� �� �����
	int nSize = (eMapSize + 1) * 64;
	CreateNewMap(nSize, nSize);

	// �ؽ��� ����
	g_pTextureManager->AddTexture("Grass", "Texture/Grass.jpg");

	return S_OK;
}

HRESULT cMapTerrainTool::Update()
{
	// ���� ���� ����
	if (g_pKeyManager->isOnceKeyDown('U'))
	{

	}
	// ���� ���� ����
	else if (g_pKeyManager->isOnceKeyDown('D'))
	{

	}
	// �ؽ��� ������
	else if (g_pKeyManager->isOnceKeyDown('T'))
	{

	}
	// �⺻ �ؽ��ķ� ���� 
	else if (g_pKeyManager->isOnceKeyDown('E'))
	{

	}
	// ���̾� ������ ���
	else if (g_pKeyManager->isOnceKeyDown('W'))
	{

	}
	// ����
	else if (g_pKeyManager->isOnceKeyDown('S'))
	{

	}
	// �ε�
	else if (g_pKeyManager->isOnceKeyDown('L'))
	{
		
	}
	// ���� ���
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

// ũ�� ������ �� ����, NewMap.raw ���Ϸ� ���� ���� 
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

    // �ε��� ����                   

    //   1 3
    //   0 2
    //  0 , 1 , 2,  // 2 , 1 , 3 ����!!

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

    // ���ؽ� ����
    for (int n = 0; n < (SizeX + 1) * (SizeZ + 1); ++n)
    {
        vec = Vector3(n % (SizeX + 1), DEFAULT_TERRAIN_HEIGHT, n / (SizeX + 1));
		m_vecPTVertex.push_back(ST_PT_VERTEX(vec, Vector2(n % (SizeX + 1), n / (SizeX + 1))));
        c << (char)vec.y;
    }



	return S_OK;

}


// �귯�� ������ ���� (�귯�� ������)
HRESULT cMapTerrainTool::SetBrushSize(IN float fSize)
{
	return E_NOTIMPL;
}

// �귯�� �� ������ ����(�� ������)
HRESULT cMapTerrainTool::SetBrushDensity(IN float fSize)
{
	return E_NOTIMPL;
}

// ���� ���� ���� (���� ������, ������ ���� ��)
HRESULT cMapTerrainTool::SetHeight(IN Vector2 vPosition, IN float fHeight)
{
	return E_NOTIMPL;
}

// �ؽ����� �е� ���� (������ �е� ��) : �̴� �귯���� �Ӽ��� ��������
HRESULT cMapTerrainTool::SetTextureDensity(IN float& fDensity)
{
	return E_NOTIMPL;
}

// �ؽ��� Ÿ�� ���� (����� �ؽ��� Ÿ��)
HRESULT cMapTerrainTool::SetTextureType(IN E_GROUND_TYPE eGroundType)
{
	return E_NOTIMPL;
}

// �� �귯�� ������ ���� (�� �귯�� ������)
HRESULT cMapTerrainTool::SetWaterBrushSize(IN float fSize)
{
	return E_NOTIMPL;
}

// ���� ���� ���� (������ ���� ��) : ���� �е��� ������ ���� ��� �� ����
HRESULT cMapTerrainTool::SetWaterSpeed(IN float fSpeed)
{
	return E_NOTIMPL;
}

// ������ �ؽ��� ������ (���� ������, ���� Ÿ��)
HRESULT cMapTerrainTool::SetDrawTexture(IN Vector2 vPosition, IN E_GROUND_TYPE eGroundType)
{
	return E_NOTIMPL;
}

// ���� ���� ���� (���� ������, ������ �� ����)
HRESULT cMapTerrainTool::SetDuplicateHeight(IN Vector2 vPosition, IN ST_TERRAIN_FACE_INFO stFaceInfo)
{
	return E_NOTIMPL;
}

// ������ ���� �����ϱ�
HRESULT cMapTerrainTool::SaveFile(IN string sFolderName, IN string sFileName)
{
	return E_NOTIMPL;
}

// ������ ���� �ε��ϱ�
HRESULT cMapTerrainTool::LoadFile(IN string sFolderName, IN string sFileName)
{
	return E_NOTIMPL;
}
