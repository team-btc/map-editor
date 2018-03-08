#pragma once

#define g_pMapDataManager cMapDataManager::GetInstance()

class cMapDataManager
{
	SINGLETON(cMapDataManager);

    // == ���� �� ���� ==
    SYNTHESIZE_PASS_BY_REF_NO_SET(E_TAB_TYPE, m_eTabType, TabType);                         // �� Ÿ��
    SYNTHESIZE_PASS_BY_REF_NO_SET(int, m_nDlgWidth, DlgWidth);                              // ���̾�α� ���� ������

	// == �⺻ �� ���� �� �ʿ��� ���� ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_MAP_SIZE, m_eMapSize, MapSize);							// �ʻ�����
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_GROUND_TYPE, m_eDefGroundType, DefGroundType);			// �⺻ ���� Ÿ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fDefHeight, DefHeight);							// �� �⺻ ���� ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isDefWalkable, DefWalkable);						// ���� �� �ִ��� ���� �⺻ ��
    SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isCreateMap, CreateMap);                          // �� ���� ����

	// == ���� ���� ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_TERRAIN_EDIT_TYPE, m_eTerEditType, TerEditType);		// ������ ���� Ÿ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerIncrement, TerIncrement);					// ���� ������(������ ���ݸ��� �ö󰡴� ���̰�)
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerBrushSize, TerBrushSize);					// ������ �귯�� ������
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerFlatSize, TerFlatSize);						// ������ ���� ������

	// == �ؽ��� ���� ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_GROUND_TYPE, m_eCurrTexType, CurrTexType);				// ���� ���õ� �ؽ��� Ÿ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isWalkable, Walkable);							// ���� �� �ִ��� ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTexDensity, TexDensity);						// �ؽ��ĸ� �귯�� �� ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTexBrushSize, TexBrushSize);					// �ؽ��ĸ� �귯�� ������
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTexBrushDenSize, TexBrushDenSize);				// �ؽ��ĸ� �귯�� �� ������
    SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTexBrushDensity, TexBrushDensity);				// �ؽ��ĸ� �귯�� �� ��

	// == �� ���� ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterHeight, WaterHeight);						// �� �⺻ ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterUVSpeed, WaterUVSpeed);					// �� UV ���ǵ�
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterWaveHeight, WaterWaveHeight)				// �� ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterHeightSpeed, WaterHeightSpeed);			// �� ���� ���ǵ�
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterFrequency, WaterFrequency);				// �� ���� ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterTransparent, WaterTransparent);			// �� ����

	// == ������Ʈ ���� ==
	// ������Ʈ ���ϸ���Ʈ
	// ���� ������Ʈ ����Ʈ
	// ���� ������ ������Ʈ ����
	// ���� ������ ������Ʈ ����Ʈ
	// ������Ʈ ����
	// ������Ʈ ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isCollision, ObjCollision);						// ������Ʈ �浹 ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isDestruction, ObjDestruction);					// ������Ʈ �ı� ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjSize, ObjSize);								// ������Ʈ ������
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjPosX, ObjPosX);								// ������Ʈ X�� ��ġ
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjPosY, ObjPosY);								// ������Ʈ Y�� ��ġ
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjPosZ, ObjPosZ);								// ������Ʈ Z�� ��ġ
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjRotX, ObjRotX);								// ������Ʈ X�� ȸ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjRotY, ObjRotY);								// ������Ʈ Y�� ȸ��
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjRotZ, ObjRotZ);								// ������Ʈ Z�� ȸ��

	SYNTHESIZE_PASS_BY_REF(string, m_strMeshKey, MeshKey);									// x���� ���ϰ�ο��� �о��� ������ Ű��
	SYNTHESIZE_PASS_BY_REF(string, m_strFilePath, MeshFilePath);							// x���� ���ϰ��
	SYNTHESIZE_PASS_BY_REF(string, m_strFileName, MeshFileName);							// x���� �̸� .x �� ����
	SYNTHESIZE_PASS_BY_REF(bool, m_isLocation, ObjLocation);								// ������Ʈ ��ġ ��ư�� ���ȴ���

    SYNTHESIZE_PASS_BY_REF_NO_SET(E_OBJECT_TAB_BUTTON_STATE, m_eObjectTabButtonState, ObjectTabButtonState);
private:
};