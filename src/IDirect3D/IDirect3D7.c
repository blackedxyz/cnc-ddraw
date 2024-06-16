#include <intrin.h>
#include "IDirect3D.h"
#include "debug.h"

#if defined(__GNUC__) /* wrap msvc intrinsics onto gcc builtins */
#undef  _ReturnAddress
#undef  _AddressOfReturnAddress
#define _ReturnAddress()		__builtin_return_address(0)
#define _AddressOfReturnAddress()	__builtin_frame_address (0)
#else
#pragma intrinsic(_ReturnAddress)
#endif /* __GNUC__ */

HRESULT __stdcall IDirect3D7__QueryInterface(IDirect3D7Impl* This, REFIID riid, void** obj)
{
    TRACE(
        "NOT_IMPLEMENTED -> %s(This=%p, riid=%08X, obj=%p) [%p]\n", 
        __FUNCTION__,
        This, 
        (unsigned int)riid, 
        obj, 
        _ReturnAddress());

    HRESULT ret = E_FAIL;

    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

ULONG __stdcall IDirect3D7__AddRef(IDirect3D7Impl* This)
{
    TRACE("-> %s(This=%p) [%p]\n", __FUNCTION__, This, _ReturnAddress());
    ULONG ret = ++This->ref;
    TRACE("<- %s(This ref=%u)\n", __FUNCTION__, ret);
    return ret;
}

ULONG __stdcall IDirect3D7__Release(IDirect3D7Impl* This)
{
    TRACE("-> %s(This=%p) [%p]\n", __FUNCTION__, This, _ReturnAddress());

    ULONG ret = --This->ref;

    if (This->ref == 0)
    {
        TRACE("     Released (%p)\n", This);

        HeapFree(GetProcessHeap(), 0, This);
    }

    TRACE("<- %s(This ref=%u)\n", __FUNCTION__, ret);
    return ret;
}

HRESULT __stdcall IDirect3D7__EnumDevices(IDirect3D7Impl* This, int a, int b)
{
    TRACE("NOT_IMPLEMENTED -> %s(This=%p) [%p]\n", __FUNCTION__, This, _ReturnAddress());
    HRESULT ret = E_FAIL;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

HRESULT __stdcall IDirect3D7__CreateDevice(IDirect3D7Impl* This, int a, int b, int c)
{
    TRACE("NOT_IMPLEMENTED -> %s(This=%p) [%p]\n", __FUNCTION__, This, _ReturnAddress());
    HRESULT ret = E_FAIL;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

HRESULT __stdcall IDirect3D7__CreateVertexBuffer(IDirect3D7Impl* This, int a, int b, int c)
{
    TRACE("NOT_IMPLEMENTED -> %s(This=%p) [%p]\n", __FUNCTION__, This, _ReturnAddress());
    HRESULT ret = E_FAIL;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

HRESULT __stdcall IDirect3D7__EnumZBufferFormats(IDirect3D7Impl* This, int a, int b, int c)
{
    TRACE("NOT_IMPLEMENTED -> %s(This=%p) [%p]\n", __FUNCTION__, This, _ReturnAddress());
    HRESULT ret = E_FAIL;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

HRESULT __stdcall IDirect3D7__EvictManagedTextures(IDirect3D7Impl* This)
{
    TRACE("NOT_IMPLEMENTED -> %s(This=%p) [%p]\n", __FUNCTION__, This, _ReturnAddress());
    HRESULT ret = E_FAIL;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

struct IDirect3D7ImplVtbl g_d3d7_vtbl =
{
    /* IUnknown */
    IDirect3D7__QueryInterface,
    IDirect3D7__AddRef,
    IDirect3D7__Release,
    /* IDirect3D7Impl */
    IDirect3D7__EnumDevices,
    IDirect3D7__CreateDevice,
    IDirect3D7__CreateVertexBuffer,
    IDirect3D7__EnumZBufferFormats,
    IDirect3D7__EvictManagedTextures,
};
