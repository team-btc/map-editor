
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#define W_WIDTH 1600
#define W_HEIGHT 900
#define PI 3.14

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

#define SAFE_DELETE(p) { if (p) delete (p); (p) = NULL; }
#define SAFE_DELETE_ARRAY(p) { if (p) delete[] (p); (p) = NULL; }
#define SAFE_RELEASE(p) { if (p) (p)->Release(); }
#define SAFE_ADDREF(p) { if (p) (p)->AddRef(); }

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


using namespace std;

#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <iostream>
#include <fstream>

#include <d3d9.h>
#include <d3dx9.h>

#include "Enum.h"
#include "DefineMacro.h"
#include "DataStructure.h"

#include "D3DUtility.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace D3DUTILITY;
extern HWND		g_hWnd;
extern POINT    g_ptMouse;
extern int      g_nWheelDelta;
extern Vector3  g_vCameraPos;


#include "cKeyManager.h"
#include "cLogManager.h"
#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cFontManager.h"
#include "cTimerManager.h"
#include "cObjectManager.h"
#include "cAutoReleasePool.h"
#include "cMeshManager.h"
#include "cShaderManager.h"
#include "cMapDataManager.h"
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>