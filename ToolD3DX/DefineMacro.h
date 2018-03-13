#pragma once
#pragma region DEFINE_MACRO
#define SAFE_DELETE(p) { if (p) delete (p); (p) = NULL; }
#define SAFE_DELETE_ARRAY(p) { if (p) delete[] (p); (p) = NULL; }
#define SAFE_RELEASE(p) { if (p) (p)->Release(); }
#define SAFE_ADDREF(p) { if (p) (p)->AddRef(); }

#define SAFE_UPDATE(instance) { if (instance) { (instance)->Update(); } }
#define SAFE_UPDATE2(instance, argument) { if (instance) { (instance)->Update(argument); } }
#define SAFE_RENDER(instance) { if (instance) { (instance)->Render(); } }
#define SAFE_RENDER2(instance, argument) { if (instance) { (instance)->Render(argument); } }

#define SYNTHESIZE(varType, varName, funName)\
protected:\
    varType varName;\
public:\
    inline varType Get##funName() const { return varName; }\
    inline void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
private:\
    varType varName;\
public:\
    inline varType& Get##funName() { return varName; }\
    inline void Set##funName(varType& var) { varName = var; }

#define SYNTHESIZE_PASS_BY_REF_NO_SET(varType, varName, funName)\
private:\
    varType varName;\
public:\
    inline varType& Get##funName() { return varName; }

#define SYNTHESIZE_PASS_BY_PT(varType, varName, funName)\
private:\
    varType varName;\
public:\
    inline varType* Get##funName() { return &varName; }\
    inline void Set##funName(varType& var) { varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)\
private:\
    varType varName;\
public:\
    inline varType Get##funName() const { return varName; }\
    inline void Set##funName(varType var)\
    {\
        if (varName != var)\
        {\
            SAFE_RELEASE(varName);\
            SAFE_ADDREF(var);\
            varName = var;\
        }\
    }

#define SINGLETON(class_name)\
private:\
    class_name();\
    ~class_name();\
public:\
    static class_name* GetInstance()\
    {\
        static class_name instance;\
        return &instance;\
    }
#pragma endregion

#pragma region REDEFINE_DATASTRUCTURE
using LPDEVICE9         = LPDIRECT3DDEVICE9;
using BASETEXTURE9      = IDirect3DBaseTexture9;
using LPTEXTURE9        = LPDIRECT3DTEXTURE9;
using LPCUBETEXTURE9    = LPDIRECT3DCUBETEXTURE9;
using LPVTXBUFFER9      = LPDIRECT3DVERTEXBUFFER9;
using LPIDXBUFFER9      = LPDIRECT3DINDEXBUFFER9;
using LIGHT9            = D3DLIGHT9;
using MATERIAL9         = D3DMATERIAL9;
using VIEWPORT9         = D3DVIEWPORT9;
using VTXELEMENT9       = D3DVERTEXELEMENT9;
using CAPS9             = D3DCAPS9;

using LPEFFECT          = LPD3DXEFFECT;
using MATERIAL          = D3DXMATERIAL;
using LPMATERIAL        = LPD3DXMATERIAL;
using LPSPRITE          = LPD3DXSPRITE;
using IMAGE_INFO        = D3DXIMAGE_INFO;
using MACRO             = D3DXMACRO;

using Vector4           = D3DXVECTOR4;
using Vector3           = D3DXVECTOR3;
using Vector2           = D3DXVECTOR2;
using Matrix4           = D3DXMATRIXA16;
using Quaternion        = D3DXQUATERNION;
using Color             = D3DCOLOR;
using XColor            = D3DXCOLOR;
using ColorVal          = D3DCOLORVALUE;

using FRAME             = D3DXFRAME;
using LPFRAME           = LPD3DXFRAME;

//using LPFONT            = LPD3DXFONT;     //  conflict
using FONT_DESC         = D3DXFONT_DESC;

using LPANIMCONTROLLER  = LPD3DXANIMATIONCONTROLLER;
using LPANIMATIONSET    = LPD3DXANIMATIONSET;
using LPTRACK_DESC      = LPD3DXTRACK_DESC;
using TRACK_DESC        = D3DXTRACK_DESC;

using MESHCONTAINER     = D3DXMESHCONTAINER;
using LPMESHCONTAINER   = LPD3DXMESHCONTAINER;
using LPMESH            = LPD3DXMESH;
using MESHDATA          = D3DXMESHDATA;
using LPMESHDATA        = LPD3DXMESHDATA;
using LPBONECOMBINATION = LPD3DXBONECOMBINATION;
using LPSKININFO        = LPD3DXSKININFO;
#pragma endregion


#define MAP_PATH "Asset/Maps/"

inline Vector3 ColorToNormal(Color c)
{
    Vector3 result;

    int r = c >> 16 & 255;
    int g = c >> 8 & 255;
    int b = c >> 0 & 255;

    r -= 128;
    g -= 128;
    b -= 128;

    result.x = r;
    result.y = g;
    result.z = b;

    D3DXVec3Normalize(&result, &result);

    return result;
}

inline Color NormalToColor(Vector3 v)
{
    Color c;

    int r = (int)(v.x * 128.0f);
    int g = (int)(v.y * 128.0f);
    int b = (int)(v.z * 128.0f);

    r += 128;
    g += 128;
    b += 128;

    c = D3DCOLOR_XRGB(r, g, b);

    return c;
}

inline int AvgColor(Color c)
{
    int avg = 0;

    int r = c >> 16 & 255;
    int g = c >> 8 & 255;
    int b = c >> 0 & 255;

    avg = r + g + b;
    avg = (int)((float)avg / 3);

    return avg;
}