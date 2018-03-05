#pragma once

#include "cObject.h"

class cMapTerrainTool;
class cMapObjectTool;

#define DEFAULT_MAP_SIZE		E_SIZE_256											// �⺻ �� ũ��
#define DEFAULT_G_TYPE			E_SOIL_GROUND										// �⺻ ���� Ÿ��

class cMapTool : public cObject
{
private:
	cMapTerrainTool*			m_pTerrainTool;
	cMapObjectTool*				m_pObjectTool;

	E_MAP_SIZE					m_eMapSize;											// �� ������
	E_GROUND_TYPE				m_eDefaultGroundType;								// �⺻ ���� Ÿ��
	int							m_nDefaultHeight;									// �� �⺻ ���� ��
	bool						m_isDefaultWalkable;								// ���� �� �ִ��� ���� �⺻ ��

private:

public:
    cMapTool();
    ~cMapTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

	HRESULT SetMapSize(IN E_MAP_SIZE eMapSize);										// �� ������ ����
	HRESULT SetDefaultTextureType(IN E_GROUND_TYPE eGroundType);					// �⺻ ���� �ؽ��� ����

	HRESULT CreateMap();															// Create��ư�� ������ �� �ߵ�
};

