#pragma once

#define g_pMapDataManager cMapDataManager::GetInstance()

class cMapDataManager
{
	SINGLETON(cMapDataManager);

	// == �⺻ �� ���� �� �ʿ��� ���� ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_MAP_SIZE, m_eMapSize, MapSize);							// �ʻ�����
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_GROUND_TYPE, m_eDefaultGroundType, DefaultGroundType);	// �⺻ ���� Ÿ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(int, m_nDefaultHeight, DefaultHeight);					// �� �⺻ ���� ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isDefaultWalkable, DefaultWalkable);				// ���� �� �ִ��� ���� �⺻ ��

	// == ���� ���� ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_TERRAIN_EDIT_TYPE, m_eTerrainEditType, TerrainEditType);// ������ ���� Ÿ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fIncrementHeight, IncrementHeight);				// ���� ������(������ ���ݸ��� �ö󰡴� ���̰�)
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fGradient, Gradient);							// ��� ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerrainBrushSize, TrrainBrushSize);				// ������ �귯�� ������
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerrainFlatSize, TrrainFlatSize);				// ������ ���� ������

	// == �ؽ��� ���� ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_GROUND_TYPE, m_eCurrTextureType, CurrTextureType);		// ���� ���õ� �ؽ��� Ÿ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isWalkable, Walkable);
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTextureBrushSize, TextureBrushSize);			// �ؽ��ĸ� �귯�� ������
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTextureBrushDenSize, TextureBrushDenSize);		// �ؽ��ĸ� �귯�� �� ������
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTextureDensity, TextureDensity);				// �ؽ��ĸ� �귯�� �� ��

	// == �� ���� ==


	// == ������Ʈ ���� ==


public:
	cMapDataManager();
	~cMapDataManager();
};

