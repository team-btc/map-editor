#include "stdafx.h"
#include "cHeightMap.h"
#include "cMtlTex.h"

cHeightMap::cHeightMap()
	: m_pMesh(NULL)
	, m_pMtlTex(NULL)
	, m_fSizeX(1.0f)
	, m_fSizeZ(1.0f)
    , m_nTime(0)
    , m_meshWater(NULL)
    , m_pUVAnimationShader(NULL)
    , m_pSkyBoxShader(NULL)
    , gWorldLightPosition(10.0f, 1000.0f, 0.0, 1.0f)
    , gLightColor(0.7f, 0.7f, 1.0f, 1.0f)
    , gWorldCameraPosition(NULL, NULL, NULL, NULL)
{
}


cHeightMap::~cHeightMap()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMtlTex);
    //SAFE_DELETE(m_pCamera);
}

void cHeightMap::LoadShader()
{
   // gWorldCameraPosition = D3DXVECTOR4(m_pCamera->GetCameraPos().x, m_pCamera->GetCameraPos().y, m_pCamera->GetCameraPos().z, 1.0f);

    g_pShaderManager->AddEffect("1", "UVAnimation.fx");
    m_pUVAnimationShader = g_pShaderManager->GetEffect("1");
    g_pShaderManager->AddEffect("2", "SkyBox.fx");
    m_pSkyBoxShader = g_pShaderManager->GetEffect("2");
    g_pTextureManager->AddTexture("W", "HeightMapData/water.jpg");
    g_pTextureManager->AddTexture("S", "HeightMapData/skybox.dds");

    m_pTexture = g_pTextureManager->GetTexture("W");
    m_pSkyBoxTexture = g_pTextureManager->GetTexture("S");
}


void cHeightMap::Load(IN char* szRawFilePath, IN char* szTexFileKey, IN char* szTexFilePath, IN D3DXMATRIXA16* pMat /* NULL */)
{
    m_pCamera = new cCamera;
   
    LoadShader();
	vector<D3DXVECTOR3> vecTest;
	// resize
	vecTest.resize(10);
	vecTest.push_back(D3DXVECTOR3(1, 1, 1));
	// vecTest�� ũ��� 11�� �ȴ�.
	// reserve
	vecTest.reserve(10);
	vecTest.push_back(D3DXVECTOR3(1, 1, 1));
	// vecTest�� ũ��� 1�̴�.


	
    m_vecPNTVertex.resize(VERTEX_DIM * VERTEX_DIM);
	m_vecVertex.resize(VERTEX_DIM * VERTEX_DIM);

	FILE* fp = NULL;
	fopen_s(&fp, szRawFilePath, "rb"); // rb : �� ����Ʈ�� �д´�. (1byte == 8bit)

	for (int z = 0; z < VERTEX_DIM; ++z)
	{
		for (int x = 0; x < VERTEX_DIM; ++x)
		{
			int nIndex = z * VERTEX_DIM + x;
			float y = (unsigned char)fgetc(fp) / 5.0f;	// 8bit == 2^8 == 0 ~  255
            m_vecPNTVertex[nIndex].p = D3DXVECTOR3(x, y, z);
            m_vecPNTVertex[nIndex].n = D3DXVECTOR3(0, 1, 0);
            m_vecPNTVertex[nIndex].t = D3DXVECTOR2(x / (float)TILE_N, z / (float)TILE_N);

			if (pMat)
				D3DXVec3TransformCoord(&m_vecPNTVertex[nIndex].p, &m_vecPNTVertex[nIndex].p, pMat);

			m_vecVertex[nIndex] = m_vecPNTVertex[nIndex].p;
		}
	}

	if (pMat)
	{
		m_fSizeX = pMat->_11;
		m_fSizeZ = pMat->_33;
	}

	fclose(fp);

	// �ε��� ����
	m_vecIndex.reserve(TILE_N * TILE_N * 3 * 2); // ���� Ÿ�� * ���� Ÿ�� * �ﰢ�� ������ * �ﰢ�� ����

	for (int z = 0; z < TILE_N; ++z)
	{
		for (int x = 0; x < TILE_N; ++x)
		{
			//1--3
			//|\ |
			//| \|
			//0--2
			int _0 = ((z + 0) * VERTEX_DIM) + (x + 0);
			int _1 = ((z + 1) * VERTEX_DIM) + (x + 0);
			int _2 = ((z + 0) * VERTEX_DIM) + (x + 1);
			int _3 = ((z + 1) * VERTEX_DIM) + (x + 1);

			m_vecIndex.push_back(_0);
			m_vecIndex.push_back(_1);
			m_vecIndex.push_back(_2);
			m_vecIndex.push_back(_2);
			m_vecIndex.push_back(_1);
			m_vecIndex.push_back(_3);
		}
	}

	// �븻�� ��� �� ����
	for (int z = 1; z < VERTEX_DIM - 1; ++z)
	{
		for (int x = 1; x < VERTEX_DIM - 1; ++x)
		{
			// ---u---
			// |\ |\ |
			// | \| \|
			// L--n--r
			// |\ |\ |
			// | \| \|
			// ---d---
			int nIndex = z * VERTEX_DIM + x;	// ���� �ε���

			int l = nIndex - 1;
			int r = nIndex + 1;
			int u = nIndex + VERTEX_DIM;
			int d = nIndex - VERTEX_DIM;

			D3DXVECTOR3 du = m_vecVertex[u] - m_vecVertex[d];
			D3DXVECTOR3 lr = m_vecVertex[r] - m_vecVertex[l];
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &du, &lr);
			D3DXVec3Normalize(&n, &n);

            m_vecPNTVertex[nIndex].n = n;
		}
	}

	// �޽� ���� �� ����
	D3DXCreateMeshFVF(m_vecIndex.size() / 3, m_vecPNTVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecPNTVertex[0], m_vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &m_vecIndex[0], m_vecIndex.size() * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, m_pMesh->GetNumFaces());
	m_pMesh->UnlockAttributeBuffer();

	// �޽� ����ȭ
	vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);
	m_pMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf[0]);
	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuf[0], 0, 0, 0);

	// �Ӽ� ����(���͸���, �ؽ���)
	m_pMtlTex = new cMtlTex;
	D3DMATERIAL9 stMtl = WHITE_MTRL;
	m_pMtlTex->SetMtl(stMtl);
	g_pTextureManager->AddTexture(szTexFileKey, szTexFilePath);
	m_pMtlTex->SetTexture(g_pTextureManager->GetTexture(szTexFileKey));

}

//void cHeightMap::WaterUpdate(vector<ST_PNT_VERTEX>& vecVertex, float waveHeight, float Speed, float waveFrequency, float uvSpeed)
//{
//    ST_PNT_VERTEX* pV = NULL;
//    m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
//   
//    m_nTime++;
//    for (int i = 0; i < VertexSize * VertexSize; ++i)
//    {
//        vecVertex[i].t.x += 0.003f;   
//        vecVertex[i].p.y += cos((vecVertex[i].t.x * 2 - 1) * 15 + m_nTime * Speed) * waveHeight;
//    }
//    memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
//    m_pMesh->UnlockVertexBuffer();
//    
//}

bool cHeightMap::GetHeight(IN const float& x, OUT float& y, IN const float& z)
{
	if (x < 0 || x / m_fSizeX > TILE_N || z < 0 || z / m_fSizeZ > TILE_N)
	{
		return false;
	}

	//1--3
	//|\ |
	//| \|
	//0--2

	// 0�� x, z ��
	int nX = (int)(x / m_fSizeX);
	int nZ = (int)(z / m_fSizeZ);
	// ĳ���� ��ġ�� (�ش� ��(0�� ��ǥ) ����)
	float fDeltaX = x / m_fSizeX - nX;
	float fDeltaZ = z / m_fSizeZ - nZ;

	// �ε��� ��ȣ
	int _0 = ((nZ + 0) * VERTEX_DIM) + (nX + 0);
	int _1 = ((nZ + 1) * VERTEX_DIM) + (nX + 0);
	int _2 = ((nZ + 0) * VERTEX_DIM) + (nX + 1);
	int _3 = ((nZ + 1) * VERTEX_DIM) + (nX + 1);

	if (fDeltaX + fDeltaZ < 1.0f) // �Ʒ��� �ﰢ��
	{
		// z�� ���� ����
		float zY = m_vecVertex[_1].y - m_vecVertex[_0].y;
		// x�� ���� ����
		float xY = m_vecVertex[_2].y - m_vecVertex[_0].y;

		y = m_vecVertex[_0].y + zY * fDeltaZ + xY * fDeltaX;
	}
	else // ���� �ﰢ��
	{
		// z�� ���� ����
		float zY = m_vecVertex[_2].y - m_vecVertex[_3].y;
		// x�� ���� ����
		float xY = m_vecVertex[_1].y - m_vecVertex[_3].y;

		y = m_vecVertex[_3].y + zY * (1.0f - fDeltaZ) + xY * (1.0f - fDeltaX);
	}

	return true;
}

vector<D3DXVECTOR3>& cHeightMap::GetVertex()
{
	return m_vecVertex;
}

vector<DWORD>& cHeightMap::GetIndex()
{
	return m_vecIndex;
}

void cHeightMap::Update(cCamera* pCamera)
{
    m_pCamera = pCamera;
   
    //g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);

   

   // gpUVAnimationShader->SetTexture("DiffuseMap_Tex", gpStoneDM);
   // gpUVAnimationShader->SetTexture("SpecularMap_Tex", gpStoneSM);
  
}

void cHeightMap::Render(E_SHADERTYPE type)
{
    if (type == E_NONE)
    {
        D3DXMATRIXA16 matW;
        D3DXMatrixIdentity(&matW);
        g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);

        g_pD3DDevice->SetMaterial(m_pMtlTex->GetMtl());
        g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
        m_pMesh->DrawSubset(0);
    }
    else if ( type == E_UVANIMATION)
    {
        D3DXMATRIXA16 matW, matView, matProjection;
        D3DXMatrixIdentity(&matW);
        matProjection = m_pCamera->GetProjMatrix();
        gWorldCameraPosition = D3DXVECTOR4(m_pCamera->GetEye().x, m_pCamera->GetEye().y, m_pCamera->GetEye().z, 1.0f);

       // D3DXMatrixLookAtLH(&matView, &m_pCamera->GetEye() , &m_pCamera->GetLookat(), &m_pCamera->GetUp());
        g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
        g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
        //g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
        //D3DXMatrixPerspectiveFovLH(&matProjection, FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
        m_pUVAnimationShader->SetMatrix("gWorldMatrix", &matW);
        m_pUVAnimationShader->SetMatrix("gViewMatrix", &matView);
        m_pUVAnimationShader->SetMatrix("gProjectionMatrix", &matProjection);
        m_pUVAnimationShader->SetTexture("DiffuseMap_Tex", m_pTexture);
       
        m_pUVAnimationShader->SetVector("gWorldLightPosition", &gWorldLightPosition);
        m_pUVAnimationShader->SetVector("gWorldCameraPosition", &gWorldCameraPosition);
        m_pUVAnimationShader->SetVector("gLightColor", &gLightColor);
        
        m_pUVAnimationShader->SetFloat("gWaveHeight", 0.4f);
        m_pUVAnimationShader->SetFloat("gSpeed", 2.0f);
        m_pUVAnimationShader->SetFloat("gWaveFrequency", 7);
        m_pUVAnimationShader->SetFloat("gUVSpeed", 0.01f);
        // �ý��� �ð��� ����
        ULONGLONG tick = GetTickCount64();
        m_pUVAnimationShader->SetFloat("gTime", tick / 1000.0f);

        // ���̴��� �����Ѵ�.
        UINT numPasses = 0;
        m_pUVAnimationShader->Begin(&numPasses, NULL);
        {
            for (UINT i = 0; i < numPasses; ++i)
            {
                m_pUVAnimationShader->BeginPass(i);
                {
                    m_pMesh->DrawSubset(0);
                }
                m_pUVAnimationShader->EndPass();
            }
        }
        m_pUVAnimationShader->End();
    }

    else if (type == E_SKYBOX)
    {
        D3DXMATRIXA16 matW, matView, matProjection, matViewProjection;
        D3DXMatrixIdentity(&matW);
        //matProjection = m_pCamera->GetProjMatrix();
        gWorldCameraPosition = D3DXVECTOR4(m_pCamera->GetEye().x, m_pCamera->GetEye().y, m_pCamera->GetEye().z, 1.0f);
        

        // D3DXMatrixLookAtLH(&matView, &m_pCamera->GetEye() , &m_pCamera->GetLookat(), &m_pCamera->GetUp());
        g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
        g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

        matViewProjection = matView * matProjection;
        m_pSkyBoxShader->SetMatrix("ViewProjection", &matViewProjection);
        m_pSkyBoxShader->SetVector("ViewPosition", &gWorldCameraPosition);
        m_pSkyBoxShader->SetTexture("Snow_Tex", m_pCubeTexture);
        UINT numPasses = 0;
        m_pSkyBoxShader->Begin(&numPasses, NULL);
        {
            for (UINT i = 0; i < numPasses; ++i)
            {
                m_pSkyBoxShader->BeginPass(i);
                {
                    m_pMesh->DrawSubset(0);
                }
                m_pSkyBoxShader->EndPass();
            }
        }
        m_pSkyBoxShader->End();
    }
  //  g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

   // g_pD3DDevice->SetMaterial(m_pMtlTex->GetMtl());
   // g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
   // m_pMesh->DrawSubset(0);
	
	//m_pMesh->DrawSubset(0);
}

void cHeightMap::CreateCube(char * szTexFileKey, char * TexFilePath, int nCubeSize)
{
    LoadShader();
    //D3DXCreateBox(DirectX::device, 1.0f, 1.0f, 1.0f, &mesh, NULL);

    //vector<D3DXVECTOR3> vecVertex;
    //vecVertex.push_back(D3DXVECTOR3(-1.0 * nCubeSize, -1.0 * nCubeSize, -1.0 * nCubeSize));	// 0
    //vecVertex.push_back(D3DXVECTOR3(-1.0 * nCubeSize, 1.0 * nCubeSize, -1.0* nCubeSize));	// 1
    //vecVertex.push_back(D3DXVECTOR3(1.0 * nCubeSize, 1.0 * nCubeSize, -1.0 * nCubeSize));	// 2
    //vecVertex.push_back(D3DXVECTOR3(1.0 * nCubeSize, -1.0 * nCubeSize, -1.0 * nCubeSize));	// 3
    //vecVertex.push_back(D3DXVECTOR3(-1.0 * nCubeSize, -1.0 * nCubeSize, 1.0 * nCubeSize));	// 4
    //vecVertex.push_back(D3DXVECTOR3(-1.0 * nCubeSize, 1.0 * nCubeSize, 1.0 * nCubeSize));	// 5
    //vecVertex.push_back(D3DXVECTOR3(1.0 * nCubeSize, 1.0 * nCubeSize, 1.0 * nCubeSize));	// 6
    //vecVertex.push_back(D3DXVECTOR3(1.0 * nCubeSize, -1.0 * nCubeSize, 1.0 * nCubeSize));	// 7
    //
    //
    //// �Ʒ���
    //m_vecIndex.push_back(4);
    //m_vecIndex.push_back(0);
    //m_vecIndex.push_back(3);
    //m_vecIndex.push_back(4);
    //m_vecIndex.push_back(3);
    //m_vecIndex.push_back(7);
    //// ����
    //m_vecIndex.push_back(1);
    //m_vecIndex.push_back(5);
    //m_vecIndex.push_back(6);
    //m_vecIndex.push_back(1);
    //m_vecIndex.push_back(6);
    //m_vecIndex.push_back(2);
    //// ����
    //m_vecIndex.push_back(4);
    //m_vecIndex.push_back(5);
    //m_vecIndex.push_back(1);
    //m_vecIndex.push_back(4);
    //m_vecIndex.push_back(1);
    //m_vecIndex.push_back(0);
    //// �ո�
    //m_vecIndex.push_back(7);
    //m_vecIndex.push_back(6);
    //m_vecIndex.push_back(5);
    //m_vecIndex.push_back(7);
    //m_vecIndex.push_back(5);
    //m_vecIndex.push_back(4);
    //// ������
    //m_vecIndex.push_back(3);
    //m_vecIndex.push_back(2);
    //m_vecIndex.push_back(6);
    //m_vecIndex.push_back(3);
    //m_vecIndex.push_back(6);
    //m_vecIndex.push_back(7);
    //// �޸�
    //m_vecIndex.push_back(0);
    //m_vecIndex.push_back(1);
    //m_vecIndex.push_back(2);
    //m_vecIndex.push_back(0);
    //m_vecIndex.push_back(2);
    //m_vecIndex.push_back(3);
    //
    ////m_vecPNTVertex[nIndex].p = D3DXVECTOR3(x, y, z);
    ////m_vecPNTVertex[nIndex].n = D3DXVECTOR3(0, 1, 0);
    ////m_vecPNTVertex[nIndex].t = D3DXVECTOR2(x / (float)TILE_N, z / (float)TILE_N);
    //m_vecPNTVertex.resize(36);
    //for (int n = 0; n < m_vecIndex.size(); ++n)
    //{
    //    m_vecPNTVertex[n].p = vecVertex.at(m_vecIndex.at(n));
    //    m_vecPNTVertex[n].n = D3DXVECTOR3(0, 1, 0);
    //    m_vecPNTVertex[n].t = D3DXVECTOR2(1,1);
    //}
    DWORD numMaterial;
    D3DXLoadMeshFromX("HeightMapData/Box.x", NULL, g_pD3DDevice, NULL, &m_pMaterial, NULL, &numMaterial, &m_pMesh);
    
    D3DXCreateCubeTextureFromFile(g_pD3DDevice, TexFilePath, &m_pCubeTexture);
    
   // // �޽� ���� �� ����
   // D3DXCreateMeshFVF(m_vecIndex.size() / 3, m_vecPNTVertex.size(),
   //     D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pMesh);
   //
   // ST_PNT_VERTEX* pV = NULL;
   // m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
   // memcpy(pV, &m_vecPNTVertex[0], m_vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));
   // m_pMesh->UnlockVertexBuffer();
   //
   // DWORD* pI = NULL;
   // m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
   // memcpy(pI, &m_vecIndex[0], m_vecIndex.size() * sizeof(DWORD));
   // m_pMesh->UnlockIndexBuffer();
   //
   // DWORD* pA = NULL;
   // m_pMesh->LockAttributeBuffer(0, &pA);
   // ZeroMemory(pA, m_pMesh->GetNumFaces());
   // m_pMesh->UnlockAttributeBuffer();
   //
   // // �޽� ����ȭ
   // vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);
   // m_pMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf[0]);
   // m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
   //     &vecAdjBuf[0], 0, 0, 0);
   //
   // �Ӽ� ����(���͸���, �ؽ���)
   //m_pMtlTex = new cMtlTex;
   //D3DMATERIAL9 stMtl = WHITE_MTRL;
   //m_pMtlTex->SetMtl(stMtl);
   //g_pTextureManager->AddTexture(szTexFileKey, TexFilePath);
   //m_pMtlTex->SetTexture(g_pTextureManager->GetTexture(szTexFileKey));
   
  // m_pTexture = g_pTextureManager->GetTexture("S");
    
    //m_stMaterial = material;

    //SetD3DVertex(vecVertex);
}
