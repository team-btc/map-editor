#pragma once

#include "cObject.h"

class cMapTerrainTool;
class cMapObjectTool;

#define DEFAULT_MAP_SIZE		E_SIZE_256											// �⺻ �� ũ��
#define DEFAULT_G_TYPE			E_SOIL_GROUND										// �⺻ ���� Ÿ��
#define DEFAULT_HEIGHT          128.0f                                              // �⺻ �� ����

class cMapTool : public cObject
{
private:
	cMapTerrainTool*			m_pTerrainTool;
	cMapObjectTool*				m_pObjectTool;

	E_MAP_SIZE&					m_eMapSize;											// �� ������
	E_GROUND_TYPE&				m_eDefaultGroundType;								// �⺻ ���� Ÿ��
	float&						m_fDefaultHeight;									// �� �⺻ ���� ��
	bool&						m_isDefaultWalkable;								// ���� �� �ִ��� ���� �⺻ ��

    bool&                       m_isCreateMap;                                      // ���� ���� ����

private:

public:
    cMapTool();
    ~cMapTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

	HRESULT CreateMap();						                                    // Create��ư�� ������ �� �ߵ�
};

