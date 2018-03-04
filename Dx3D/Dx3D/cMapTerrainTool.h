#pragma once

#include "cObject.h"

#define GT_MAX_NUM			5														// ÁöÇü Å¸ÀÔ °³¼ö
#define DEFAULT_BLD			1.0f													// ºí·»µù ±âº» °ª
#define DEFAULT_OBJ_PROP	E_OBJ_NONE												// ¿ÀºêÁ§Æ® ¼ºÁú ±âº» °ª
#define DEFAULT_BR_SZ		10.0f													// ºê·¯½¬ ±âº» »çÀÌÁî
#define DEFAULT_BRD_SZ		5.0f													// ºê·¯½¬ ³óµµ ±âº» »çÀÌÁî
#define DEFAULT_BRD			0.5f													// ºê·¯½¬ ±âº» ³óµµ °ª
#define DEFAULT_TXD			1.0f													// ÅØ½ºÃÄ ±âº» ³óµµ°ª
#define WATER_BRUSH_SIZE	8.0f													// ¹° ºê·¯½¬ ±âº» »çÀÌÁî
#define DEFAULT_FLUID_SPEED 0.5f													// ¹° ±âº» À¯¼Ó
#define DEFAULT_FOLDER		"*/Map/"												// ±âº» ÆÄÀÏ Æú´õ
#define DEFAULT_FILE_NAME	"MapData"												// ±âº» ÆÄÀÏ¸í
//

// ÁöÇü ¸é(»ï°¢Çü)Á¤º¸
struct ST_TERRAIN_FACE_INFO {
	DWORD							dVertexIndedArr[3];								// ¸éÀÌ °¡Áö°í ÀÖ´Â »ï°¢Çü ¹öÅØ½º ÁÂÇ¥ ÀÎµ¦½º
	//ST_PT_VERTEX*					pVertexArr[3];									// ¸éÀÌ °¡Áö°í ÀÖ´Â »ï°¢Çü Á¤º¸
	E_GROUND_TYPE                   eGroundType[GT_MAX_NUM];
    float                           fBlending[GT_MAX_NUM];
    bool                            isWalkable;                                     // true ¸é Áö³ª°¥ ¼öÀÖÀ½
    E_OBJECT_PROPERTY               eObjProp;                                       // ¿ÀºêÁ§Æ® ¼ºÁú (ÆÄ±«¿©ºÎ, Ãæµ¹¿©ºÎ)

	ST_TERRAIN_FACE_INFO() {
		//for (int i = 0; i < 3; ++i)
		//{
		//	pVertexArr[i] = NULL;
		//}
		for (int i = 0; i < GT_MAX_NUM; ++i)
		{
			eGroundType[i] = E_SOIL_GROUND;
		}
		for (int i = 0; i < GT_MAX_NUM; ++i)
		{
			fBlending[i] = 0.0f;
		}
	}
};

// ºê·¯½¬ Á¤º¸
struct ST_BRUSH_INFO {
	float							fBrushSize;										// ºê·¯½¬ »çÀÌÁî
	float							fBrushDensitySize;								// ºê·¯½¬ ³óµµ »çÀÌÁî
	float							fBrushDensity;									// ºê·¯½¬ ³óµµ °ª
	float							fTextureDensity;								// ÅØ½ºÃÄ ³óµµ °ª
	float							fWaterSpeed;									// ¹°ÀÇ À¯¼Ó
};

// ¹° ÁöÇü Á¤º¸
struct ST_WATER_INFO {
	Vector2							vPosition;										// ¹°ÀÇ Áß¾Ó À§Ä¡
	float							fHeight;										// ¹°ÀÇ ³ôÀÌ
	float							fSpeed;											// ¹°ÀÇ À¯¼Ó
	float							fDensity;										// ¹°ÀÇ ³óµµ
};

class cMapTerrainTool : public cObject
{
private:
    POINT                           m_ptSize;                                       // ¸Ê Å©±â

    vector<ST_PT_VERTEX>            m_vecPTVertex;                                  // ¸Ê¿¡ »ç¿ëÇÒ Á¡ º¤ÅÍ
    vector<DWORD>                   m_vecVertexIndex;                               // Height¸Ê ÁÂÇ¥ ÀÎµ¦½º º¤ÅÍ

	vector<ST_WATER_INFO>			m_vecWaterInfo;									// ¹°Á¤º¸(±âº» 8*8»çÀÌÁî·Î ³ª´®)

	E_GROUND_TYPE                   m_eCurrTextureType;								// ÇöÀç ÅØ½ºÃÄ ÀÎµ¦½º
    vector<string>                  m_vecTextureKey;                                // ÅØ½ºÃÄ Å°°ª º¤ÅÍ

    vector<ST_TERRAIN_FACE_INFO>    m_vecFaceInfo;                                  // ¸éÁ¤º¸ (¼øÂ÷Àû)

    string                          m_sFileName;                                    // ÆÄÀÏ ÀÌ¸§

	ST_BRUSH_INFO					m_BrushInfo;									// ºê·¯½¬ Á¤º¸

	LPD3DXMESH						m_pMesh;										// ¸Å½¬

private:
    HRESULT CreateNewMap(IN int nSizeX, IN int nSizeZ, IN E_GROUND_TYPE eGroundType);		// Å©±â ¼³Á¤ÇÑ ¸Ê »ý¼º
	HRESULT SetBrushSize(IN float fSize);													// ºê·¯½¬ »çÀÌÁî ¼³Á¤
	HRESULT SetBrushDensity(IN float fSize);												// ºê·¯½¬ ³óµµ »çÀÌÁî ¼³Á¤
	HRESULT SetHeight(IN Vector2 vPosition, IN float fHeight);								// ÁöÇü ³ôÀÌ ¼³Á¤
	HRESULT SetTextureDensity(IN float& fDensity);											// ÅØ½ºÃÄÀÇ ¹Ðµµ ¼³Á¤ (ÀÌ´Â ºê·¯½¬ÀÇ ¼Ó¼ºÀ» ¼³Á¤ÇØÁÜ)
	HRESULT SetTextureType(IN E_GROUND_TYPE eGroundType);									// ÅØ½ºÃÄ Å¸ÀÔ ¼³Á¤
	HRESULT SetWaterBrushSize(IN float fSize);												// ¹° ºê·¯½¬ »çÀÌÁî ¼³Á¤
	HRESULT SetWaterSpeed(IN float fSpeed);													// ¹°ÀÇ À¯¼Ó ¼³Á¤ (¹°ÀÇ ¹Ðµµ¿Í ¿òÁ÷ÀÓ °ªÀ» °è»ê ¹× ¼³Á¤)
	HRESULT SetDrawTexture(IN Vector2 vPosition, IN E_GROUND_TYPE eGroundType);				// ÁöÇü¿¡ ÅØ½ºÃÄ ÀÔÈ÷±â
	HRESULT SetDuplicateHeight(IN Vector2 vPosition, IN ST_TERRAIN_FACE_INFO stFaceInfo);	// ÁöÇü ³ôÀÌ º¹Á¦
	// ºê·¯½¬°¡ ÁöÁ¤ÇÑ ÁöÇü °ÙÅÍ -> vector<ST_PT_VERTEX> Get~~~~();

	HRESULT SaveFile(IN string sFolderName, IN string sFileName);							// ÁöÇü¸Ê ÆÄÀÏ ÀúÀåÇÏ±â
	HRESULT LoadFile(IN string sFolderName, IN string sFileName);							// ÁöÇü¸Ê ÆÄÀÏ ·ÎµåÇÏ±â

public:

    cMapTerrainTool();
    ~cMapTerrainTool();

	HRESULT Setup(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType);
	HRESULT Update();
	HRESULT Render();
};

