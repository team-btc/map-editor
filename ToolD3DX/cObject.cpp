#include "stdafx.h"
#include "cObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


cObject::cObject()
    : m_nRefCount(1)
{
    g_pObjectManager->AddObject(this);
}


cObject::~cObject()
{
    if (m_nRefCount <= 0)
        g_pObjectManager->RemoveObejct(this);
    else
        assert(false && "릴리즈를 사용해서 객체를 해제하세요");
}

HRESULT cObject::QueryInterface(REFIID riid, void** ppvObject)
{
    return E_NOTIMPL;
}

ULONG cObject::AddRef()
{
    return ++m_nRefCount;
}

ULONG cObject::Release()
{
    --m_nRefCount;
    if (m_nRefCount <= 0)
    {
        delete this;
    }

    return m_nRefCount;
}

HRESULT cObject::GetName(string& name)
{
    if (name != "")
    {
        m_szName = name;
        return E_INVALIDARG;
    }
    else
    {
        m_szName = name;
        return S_OK;
    }
}

HRESULT cObject::SetName(const string name)
{
    if (name != "")
    {
        m_szName = name;
        return S_OK;
    }
    else
    {
        return E_INVALIDARG;
    }
}

HRESULT cObject::Destroy()
{
    return E_NOTIMPL;
}
