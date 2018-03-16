#pragma once

#define g_pMapDataManager cMapDataManager::GetInstance()

class cMapTool;
class cWaterTap;
class cMapDataManager
{
	SINGLETON(cMapDataManager);

    // == ���� �� ���� ==
    SYNTHESIZE_PASS_BY_REF(E_TAB_TYPE, m_eTabType, TabType);                         // �� Ÿ��
    SYNTHESIZE_PASS_BY_REF(int, m_nDlgWidth, DlgWidth);                              // ���̾�α� ���� ������

	// == �⺻ �� ���� �� �ʿ��� ���� ==
	SYNTHESIZE_PASS_BY_REF(E_MAP_SIZE, m_eMapSize, MapSize);							// �ʻ�����
	SYNTHESIZE_PASS_BY_REF(float, m_fDefHeight, DefHeight);							// �� �⺻ ���� ��
    SYNTHESIZE_PASS_BY_REF(bool, m_isCreateMap, CreateMap);                          // �� ���� ����
    SYNTHESIZE_PASS_BY_REF(bool, m_isTex1Load, IsTex1Load);                          // �⺻ �ؽ���1 ���� �ε� ����
    SYNTHESIZE_PASS_BY_REF(string, m_strTex1FilePath, Tex1FilePath);                 // �⺻ �ؽ���1 ���� ���
    SYNTHESIZE_PASS_BY_REF(string, m_strTex1FileName, Tex1FileName);                 // �⺻ �ؽ���1 ���� �̸�
    SYNTHESIZE_PASS_BY_REF(bool, m_isTex2Load, IsTex2Load);                          // �⺻ �ؽ���2 ���� �ε� ����
    SYNTHESIZE_PASS_BY_REF(string, m_strTex2FilePath, Tex2FilePath);                 // �⺻ �ؽ���2 ���� ���
    SYNTHESIZE_PASS_BY_REF(string, m_strTex2FileName, Tex2FileName);                 // �⺻ �ؽ���2 ���� �̸�
    SYNTHESIZE_PASS_BY_REF(bool, m_isTex3Load, IsTex3Load);                          // �⺻ �ؽ���3 ���� �ε� ����
    SYNTHESIZE_PASS_BY_REF(string, m_strTex3FilePath, Tex3FilePath);                 // �⺻ �ؽ���3 ���� ���
    SYNTHESIZE_PASS_BY_REF(string, m_strTex3FileName, Tex3FileName);                 // �⺻ �ؽ���3 ���� �̸�

	// == ���� ���� ==
    SYNTHESIZE_PASS_BY_REF(E_UP_DOWN, m_eUpDown, TerUpDown);                         // ������ ���� ���ٿ� ����
	SYNTHESIZE_PASS_BY_REF(E_TERRAIN_EDIT_TYPE, m_eTerEditType, TerEditType);		// ������ ���� Ÿ��
    SYNTHESIZE_PASS_BY_REF(float, m_fTerEditPower, TerEditPower);                    // ������ ���� ����
    SYNTHESIZE_PASS_BY_REF(float, m_fTerEditHeight, TerEditHeight);                  // ������ ���� ����
    SYNTHESIZE_PASS_BY_REF(E_TER_BRUSH_TYPE, m_eTerBrushType, TerBrushType);         // ������ �귯�� Ÿ��
	SYNTHESIZE_PASS_BY_REF(float, m_fTerBrushSize, TerBrushSize);					// ������ �귯�� ������

	// == �ؽ��� ���� ==
	SYNTHESIZE_PASS_BY_REF(int, m_nCurrTexIndex, CurrTexIndex);				        // ���� ���õ� �ؽ��� �ε���
	SYNTHESIZE_PASS_BY_REF(float, m_fDrawDensity, DrawDensity);						// �ؽ��ĸ� �귯�� �� ��
	SYNTHESIZE_PASS_BY_REF(float, m_fTexBrushSize, TexBrushSize);					// �ؽ��ĸ� �귯�� ������
	SYNTHESIZE_PASS_BY_REF(float, m_fTexBrushDenSize, TexBrushDenSize);				// �ؽ��ĸ� �귯�� �� ������
    SYNTHESIZE_PASS_BY_REF(float, m_fTexBrushDensity, TexBrushDensity);				// �ؽ��ĸ� �귯�� �� ��
    SYNTHESIZE_PASS_BY_REF(E_DRAW_TYPE, m_eDrawType, DrawType);				        // �ؽ��ĸ� �׸��� Ÿ��
    SYNTHESIZE_PASS_BY_REF(float, m_fTex1Density, Tex1Density);
    SYNTHESIZE_PASS_BY_REF(float, m_fTex2Density, Tex2Density);
    SYNTHESIZE_PASS_BY_REF(float, m_fTex3Density, Tex3Density);

	// == �� ���� ==
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterHeight, WaterHeight);						// �� �⺻ ����
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterUVSpeed, WaterUVSpeed);					// �� UV ���ǵ�
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterWaveHeight, WaterWaveHeight)				// �� ����
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterHeightSpeed, WaterHeightSpeed);			// �� ���� ���ǵ�
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterFrequency, WaterFrequency);				// �� ���� ����
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterTransparent, WaterTransparent);			// �� ����
    SYNTHESIZE_PASS_BY_REF(float, m_fWaterDensity, WaterDensity);			// �� �е�
    SYNTHESIZE_PASS_BY_REF(bool, m_isMakeWater, IsMakeWater);                        // �� ������ ����
    SYNTHESIZE_PASS_BY_REF(bool, m_isSetWaterFile, IsSetWaterFile);				    // �� ������ ���� �Ǿ��� ��(Ŭ������)
    SYNTHESIZE_PASS_BY_REF(string, m_strWaterFilePath, WaterFilePath);				// �� ���ϰ��
    SYNTHESIZE_PASS_BY_REF(string, m_strWaterFileName, WaterFileName);				// �� ���� �̸�

    // == �ϴ� ���� ==
    SYNTHESIZE_PASS_BY_REF(bool, m_isSetSkyFile, IsSetSkyFile);				        // �ϴ� ������ ���� �Ǿ��� ��(Ŭ������)
    SYNTHESIZE_PASS_BY_REF(string, m_strSkyFilePath, SkyFilePath);					// �ϴ� ���ϰ��
    SYNTHESIZE_PASS_BY_REF(string, m_strSkyFileName, SkyFileName);					// �ϴ� �����̸�

	// == ������Ʈ ���� ==
	// ������Ʈ ���ϸ���Ʈ
	// ���� ������Ʈ ����Ʈ
	// ���� ������ ������Ʈ ����
	// ���� ������ ������Ʈ ����Ʈ
	// ������Ʈ ����
	// ������Ʈ ����
	SYNTHESIZE_PASS_BY_REF(bool, m_isCollision, ObjCollision);						// ������Ʈ �浹 ����
	SYNTHESIZE_PASS_BY_REF(bool, m_isDestruction, ObjDestruction);					// ������Ʈ �ı� ����
	SYNTHESIZE_PASS_BY_REF(bool, m_isObjEnemy, ObjEnemy);							// ������Ʈ ���ʹ�
	SYNTHESIZE_PASS_BY_REF(float, m_fObjSize, ObjSize);								// ������Ʈ ������
	SYNTHESIZE_PASS_BY_REF(float, m_fObjPosX, ObjPosX);								// ������Ʈ X�� ��ġ
	SYNTHESIZE_PASS_BY_REF(float, m_fObjPosY, ObjPosY);								// ������Ʈ Y�� ��ġ
	SYNTHESIZE_PASS_BY_REF(float, m_fObjPosZ, ObjPosZ);								// ������Ʈ Z�� ��ġ
	SYNTHESIZE_PASS_BY_REF(float, m_fObjRotX, ObjRotX);								// ������Ʈ X�� ȸ��
	SYNTHESIZE_PASS_BY_REF(float, m_fObjRotY, ObjRotY);								// ������Ʈ Y�� ȸ��
	SYNTHESIZE_PASS_BY_REF(float, m_fObjRotZ, ObjRotZ);								// ������Ʈ Z�� ȸ��
    SYNTHESIZE_PASS_BY_REF(E_OBJECT_BUTTON_STATE, m_eObjectButtonState, ObjectButtonState);  // ������Ʈ ����� ��ư Ŭ�� ���� 
    SYNTHESIZE_PASS_BY_REF(E_BLOCK_BUTTON_STATE, m_eBlockButtonState, BlockButtonState);     // ��� �׷� ����� ��ư Ŭ�� ���� 
	SYNTHESIZE_PASS_BY_REF(string, m_SelectBlockGroupName, SelectedBlockGroupName);          // �ֱ� ������ ��� �׷� 
	SYNTHESIZE_PASS_BY_REF(string, m_strFilePath, FilePath);							// x���� ���ϰ��
	SYNTHESIZE_PASS_BY_REF(string, m_strFileName, FileName);							// x���� �̸� .x �� ����
	SYNTHESIZE_PASS_BY_REF(string, m_sFileKey,  FileKey);								// x���� ���ϰ�ο��� �о��� ������ Ű��
    // ����Ʈ ������ 
    SYNTHESIZE_PASS_BY_REF_NO_SET(CListBox*, m_pObjListBox, ObjListBox);                 // ������Ʈ ����Ʈ �ڽ�
    SYNTHESIZE_PASS_BY_REF_NO_SET(CListBox*, m_pBlockGroupListBox, BlockGroupListBox);   // ��ϱ׷� ����Ʈ �ڽ� 
	// ���� ��� (�ҷ�����)
	SYNTHESIZE_PASS_BY_REF(string, m_sFolderPath, FolderPath);
    // ��ϱ׷� ���� ����
    SYNTHESIZE_PASS_BY_REF(int, m_nBlockMakeNum, BlockMakeNum);

	//==================�ؽ��� ��============================================================//
	// �ؽ���1 
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pTex1DensitySliderCtl, Tex1DensitySliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pTex1DensityEditCtl, Tex1DensityEditCtl);
	// �ؽ���2
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pTex2DensitySliderCtl, Tex2DensitySliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pTex2DensityEditCtl, Tex2DensityEditCtl);
	// �ؽ���3
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pTex3DensitySliderCtl, Tex3DensitySliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pTex3DensityEditCtl, Tex3DensityEditCtl);
	//==================���� ��==============================================================//
	// �� ���� üũ
	SYNTHESIZE_PASS_BY_REF_NO_SET(CButton*, m_pWaterMakeCheck, WaterMakeCheck);
	// ������
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pWaterHeightSliderCtl, WaterHeightSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pWaterHeightEditCtl, WaterHeightEditCtl);
	// ��UV ���ǵ�
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pUVSpeedSliderCtl, WaterUVSpeedSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pUVSpeedEditCtl, WaterUVSpeedEditCtl);
	// �� �ĵ� ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pWaveHeightSliderCtl, WaveHeightSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pWaveHeightEditCtl, WaveHeightEditCtl);
	// �� �ĵ� ���ǵ�
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pHeightSpeedSliderCtl, HeightSpeedSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pHeightSpeedEditCtl, HeightSpeedEditCtl);
	// �� ���� ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pFrequencySliderCtl, FrequencySliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pFrequencyEditCtl, FrequencyEditCtl);
	// �� ����
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pTransparentSliderCtl, TransparentSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pTransparentEditCtl, TransparentEditCtl);
    //======================�̺�Ʈ=============================================================//
    SYNTHESIZE_PASS_BY_REF_NO_SET(E_EVENT_BUTTON_STATE, m_eEventButtonState, EventButtonState)
    SYNTHESIZE_PASS_BY_REF_NO_SET(string, m_sEventName, EventName);
    //SYNTHESIZE_PASS_BY_REF_NO_SET(CListBox*, m_pEventListBox, EventListBox);
    //SYNTHESIZE_PASS_BY_REF_NO_SET(string, m_sEventSelectName, EventSelectName);
private:
    cMapTool*       m_pMapTool;
public:
    void SetMapData();	// �⺻ ���ϵ� �ε� �س���
    void SetMapTool(cMapTool* maptool) { m_pMapTool = maptool; }
    json SaveMapData(string strFilePath, string strFileTitle);
    void LoadMapData(string sFilePath, string sFileTitle);
};