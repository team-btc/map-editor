#pragma once

#include "cObject.h"

class cRay;


class cMapTerrainTool;
class cMapObjectTool;

#define DEFAULT_MAP_SIZE		E_SIZE_256											// �⺻ �� ũ��
#define DEFAULT_G_TYPE			E_SOIL_GROUND										// �⺻ ���� Ÿ��
#define DEFAULT_HEIGHT          128.0f                                              // �⺻ �� ����

class cMapTool : public cObject
{
private:
    E_TAB_TYPE & m_eCurrTabType;                                     // �� ����                

    cRay*                       m_pRay;
    Vector3                     m_vPickPos;                                                  // ���콺 ��ŷ ��ǥ

    cMapTerrainTool*			m_pTerrainTool;
    cMapObjectTool*				m_pObjectTool;

    E_MAP_SIZE&					m_eMapSize;											// �� ������
    float&						m_fDefaultHeight;									// �� �⺻ ���� ��
    bool&                       m_isTex1Load;                                       // �⺻ �ؽ���1 �ε� ����
    bool&                       m_isTex2Load;                                       // �⺻ �ؽ���2 �ε� ����
    bool&                       m_isTex3Load;                                       // �⺻ �ؽ���3 �ε� ����

    string&                     m_strTex1FilePath;                                  // �⺻ �ؽ���1 ���
    string&                     m_strTex1FileName;                                  // �⺻ �ؽ���1 �̸�
    string&                     m_strTex2FilePath;                                  // �⺻ �ؽ���2 ���
    string&                     m_strTex2FileName;                                  // �⺻ �ؽ���2 �̸�
    string&                     m_strTex3FilePath;                                  // �⺻ �ؽ���3 ���
    string&                     m_strTex3FileName;                                  // �⺻ �ؽ���3 �̸�
    bool&                       m_isCreateMap;                                      // ���� ���� ����

private:

public:
    cMapTool();
    ~cMapTool();

    HRESULT Setup();
    HRESULT Update();
    HRESULT Render();

    HRESULT CreateMap();						                                    // Create��ư�� ������ �� �ߵ�
    json SaveByJson(string strFilePath, string strFileTitle);
    void LoadByJson(string sFilePath, string sFileTitle);
    HRESULT GetPtMouse();                                                           // ���콺 ��ġ ��������
    void RendPtMouse();                                                             // ���콺 ��ġ ���
    bool IsPickMap();                                                               // ���콺�� Ŭ���̾�Ʈ ���� �ȿ��� ���� Ŭ�� �ߴ��� üũ
};

