#pragma once

#include "cObject.h"

#define GT_MAX_NUM			5														// ���� Ÿ�� ����
#define DEFAULT_BLD			1.0f													// ���� �⺻ ��
#define DEFAULT_OBJ_PROP	E_OBJ_NONE												// ������Ʈ ���� �⺻ ��
#define DEFAULT_BR_SZ		10.0f													// �귯�� �⺻ ������
#define DEFAULT_BRD_SZ		5.0f													// �귯�� �� �⺻ ������
#define DEFAULT_BRD			0.5f													// �귯�� �⺻ �� ��
#define DEFAULT_TXD			1.0f													// �ؽ��� �⺻ �󵵰�
#define WATER_BRUSH_SIZE	8.0f													// �� �귯�� �⺻ ������
#define DEFAULT_FLUID_SPEED 0.5f													// �� �⺻ ����
#define DEFAULT_FOLDER		"*/Map/"												// �⺻ ���� ����
#define DEFAULT_FILE_NAME	"MapData"												// �⺻ ���ϸ�
//

// ���� ��(�ﰢ��)����
struct ST_TERRAIN_FACE_INFO {
    ST_PT_VERTEX*                   pVertexArr[3];                                   // ���� ������ �ִ� �ﰢ��
	E_GROUND_TYPE                   eGroundType[GT_MAX_NUM];
    float                           fBlending[GT_MAX_NUM];
    bool                            isWalkable;                                     // true �� ������ ������
    E_OBJECT_PROPERTY               eObjProp;                                       // ������Ʈ ���� (�ı�����, �浹����)
};

// �귯�� ����
struct ST_BRUSH_INFO {
	float							fBrushSize;										// �귯�� ������
	float							fBrushDensitySize;								// �귯�� �� ������
	float							fBrushDensity;									// �귯�� �� ��
	float							fTextureDensity;								// �ؽ��� �� ��
	float							fWaterSpeed;									// ���� ����
};

// �� ���� ����
struct ST_WATER_INFO {
	Vector2							vPosition;										// ���� �߾� ��ġ
	float							fHeight;										// ���� ����
	float							fSpeed;											// ���� ����
	float							fDensity;										// ���� ��
};

class cMapTerrainTool : public cObject
{
private:
    POINT                           m_ptSize;                                       // �� ũ��

    vector<ST_PT_VERTEX>            m_vecPTVertex;                                  // �ʿ� ����� �� ����
    vector<int>                     m_vecVertexIndex;                               // Height�� ��ǥ �ε��� ����

	vector<ST_WATER_INFO>			m_vecWaterInfo;									// ������(�⺻ 8*8������� ����)

	E_GROUND_TYPE                   m_eCurrTextureType;								// ���� �ؽ��� �ε���
    vector<string>                  m_vecTextureKey;                                // �ؽ��� Ű�� ����

    vector<ST_TERRAIN_FACE_INFO>    m_vecFaceInfo;                                  // ������ (������)

    string                          m_sFileName;                                    // ���� �̸�

	ST_BRUSH_INFO					m_BrushInfo;									// �귯�� ����

private:
    HRESULT CreateNewMap(IN int nSizeX, IN int nSizeZ);										// ũ�� ������ �� ����
	HRESULT SetBrushSize(IN float fSize);													// �귯�� ������ ����
	HRESULT SetBrushDensity(IN float fSize);												// �귯�� �� ������ ����
	HRESULT SetHeight(IN Vector2 vPosition, IN float fHeight);								// ���� ���� ����
	HRESULT SetTextureDensity(IN float& fDensity);											// �ؽ����� �е� ���� (�̴� �귯���� �Ӽ��� ��������)
	HRESULT SetTextureType(IN E_GROUND_TYPE eGroundType);									// �ؽ��� Ÿ�� ����
	HRESULT SetWaterBrushSize(IN float fSize);												// �� �귯�� ������ ����
	HRESULT SetWaterSpeed(IN float fSpeed);													// ���� ���� ���� (���� �е��� ������ ���� ��� �� ����)
	HRESULT SetDrawTexture(IN Vector2 vPosition, IN E_GROUND_TYPE eGroundType);				// ������ �ؽ��� ������
	HRESULT SetDuplicateHeight(IN Vector2 vPosition, IN ST_TERRAIN_FACE_INFO stFaceInfo);	// ���� ���� ����
	// �귯���� ������ ���� ���� -> vector<ST_PT_VERTEX> Get~~~~();

	HRESULT SaveFile(IN string sFolderName, IN string sFileName);							// ������ ���� �����ϱ�
	HRESULT LoadFile(IN string sFolderName, IN string sFileName);							// ������ ���� �ε��ϱ�

public:

    cMapTerrainTool();
    ~cMapTerrainTool();

	HRESULT Setup(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType);
	HRESULT Update();
	HRESULT Render();
};

