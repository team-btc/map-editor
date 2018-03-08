#pragma once

#include "cObject.h"
class cRay;


class cMapTerrainTool;
class cMapObjectTool;

#define DEFAULT_MAP_SIZE		E_SIZE_256						// �⺻ �� ũ��
#define DEFAULT_G_TYPE			E_SOIL_GROUND					// �⺻ ���� Ÿ��
#define DEFAULT_HEIGHT          128.0f                          // �⺻ �� ����

class cMapTool : public cObject
{
private:
    E_TAB_TYPE&                 m_eCurrTabType;                 // �� ����                

    cRay*                       m_pRay;
    Vector3                     m_vPickPos;                     // ���콺 ��ŷ ��ǥ

	cMapTerrainTool*			m_pTerrainTool;
	cMapObjectTool*				m_pObjectTool;


	E_MAP_SIZE&					m_eMapSize;						// �� ������
	E_GROUND_TYPE&				m_eDefaultGroundType;			// �⺻ ���� Ÿ��
	float&						m_fDefaultHeight;				// �� �⺻ ���� ��
	bool&						m_isDefaultWalkable;			// ���� �� �ִ��� ���� �⺻ ��

    bool&                       m_isCreateMap;                  // ���� ���� ����


private:

public:
    cMapTool();
    ~cMapTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

	HRESULT CreateMap();		// Create��ư�� ������ �� �ߵ�
                                               
    HRESULT GetPtMouse();       // ���콺 ��ġ ��������
    void RendPtMouse();         // ���콺 ��ġ ���
    bool IsPickMap();           // ���콺�� Ŭ���̾�Ʈ ���� �ȿ��� ���� Ŭ�� �ߴ��� üũ
};

