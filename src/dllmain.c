#include <windows.h>
#include "ddraw.h"
#include <stdio.h>
#include "dllmain.h"
#include "directinput.h"
#include "IDirectDraw.h"
#include "dd.h"
#include "ddclipper.h"
#include "debug.h"
#include "config.h"
#include "hook.h"
#include "indeo.h"
#include "utils.h"
#include "versionhelpers.h"
#include "delay_imports.h"
#include "keyboard.h"


/* export for cncnet cnc games */
BOOL GameHandlesClose;

/* export for some warcraft II tools */
PVOID FakePrimarySurface;


HMODULE g_ddraw_module;
static BOOL g_screensaver_disabled;

BOOL WINAPI DllMain(HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        g_ddraw_module = hDll;

        delay_imports_init();

        if (GetEnvironmentVariable("cnc_ddraw_config_init", NULL, 0))
        {
            cfg_load();
            return TRUE;
        }

#ifdef _DEBUG 
        dbg_init();
        g_dbg_exception_filter = real_SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)dbg_exception_handler);
#endif

        cfg_load();

        PVOID(WINAPI * add_handler)(ULONG, PVECTORED_EXCEPTION_HANDLER) =
            (void*)real_GetProcAddress(GetModuleHandleA("Kernel32.dll"), "AddVectoredExceptionHandler");

        if (add_handler)
        {
            g_dbg_exception_handle = add_handler(1, (PVECTORED_EXCEPTION_HANDLER)dbg_vectored_exception_handler);
        }

        char buf[1024];

        if (GetEnvironmentVariable("__COMPAT_LAYER", buf, sizeof(buf)))
        {
            TRACE("__COMPAT_LAYER = %s\n", buf);

            char* s = strtok(buf, " ");

            while (s)
            {
                /* Workaround for bug in Windows 11 (Steam RA2 crash) */
                if (_strcmpi(s, "Win7RTM") == 0)
                {
                    g_config.d3d9on12 = TRUE;
                }

                if (_strcmpi(s, "WIN95") == 0 || _strcmpi(s, "WIN98") == 0 || _strcmpi(s, "NT4SP5") == 0)
                {
                    char mes[280] = { 0 };

                    _snprintf(
                        mes,
                        sizeof(mes) - 1,
                        "Warning: Compatibility modes detected. \n\nIf there are issues with the game then try to "
                        "disable the '%s' compatibility mode for all game executables.\n\n"
                        "Note: You can disable this warning via ddraw.ini -> 'no_compat_warning=true'",
                        s);

                    if (!g_config.no_compat_warning)
                        MessageBoxA(NULL, mes, "Compatibility modes detected - cnc-ddraw", MB_OK);

                    break;
                }

                s = strtok(NULL, " ");
            }
        }

        BOOL set_dpi_aware = FALSE;

        HMODULE shcore_dll = GetModuleHandle("shcore.dll");
        HMODULE user32_dll = GetModuleHandle("user32.dll");

        if (user32_dll)
        {
            SETPROCESSDPIAWARENESSCONTEXTPROC set_awareness_context =
                (SETPROCESSDPIAWARENESSCONTEXTPROC)real_GetProcAddress(user32_dll, "SetProcessDpiAwarenessContext");

            if (set_awareness_context)
            {
                set_dpi_aware = set_awareness_context(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
            }
        }

        if (!set_dpi_aware && shcore_dll)
        {
            SETPROCESSDPIAWERENESSPROC set_awareness =
                (SETPROCESSDPIAWERENESSPROC)real_GetProcAddress(shcore_dll, "SetProcessDpiAwareness");

            if (set_awareness)
            {
                HRESULT result = set_awareness(PROCESS_PER_MONITOR_DPI_AWARE);

                set_dpi_aware = result == S_OK || result == E_ACCESSDENIED;
            }
        }

        if (!set_dpi_aware && user32_dll)
        {
            SETPROCESSDPIAWAREPROC set_aware =
                (SETPROCESSDPIAWAREPROC)real_GetProcAddress(user32_dll, "SetProcessDPIAware");

            if (set_aware)
                set_aware();
        }

        /* Make sure screensaver will stay off and monitors will stay on */
        SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);

        /* WINE does not support SetThreadExecutionState so we'll have to use SPI_SETSCREENSAVEACTIVE instead */
        BOOL screensaver_enabled = FALSE;
        SystemParametersInfoA(SPI_GETSCREENSAVEACTIVE, 0, &screensaver_enabled, 0);

        if (screensaver_enabled)
        {
            SystemParametersInfoA(SPI_SETSCREENSAVEACTIVE, FALSE, NULL, 0);
            g_screensaver_disabled = TRUE;
        }

        indeo_enable();
        timeBeginPeriod(1);
        hook_init();
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        if (GetEnvironmentVariable("cnc_ddraw_config_init", NULL, 0))
            return TRUE;

        TRACE("cnc-ddraw DLL_PROCESS_DETACH\n");

        cfg_save();

        indeo_disable();
        timeEndPeriod(1);
        keyboard_hook_exit();
        dinput_hook_exit();
        hook_exit();

        SetThreadExecutionState(ES_CONTINUOUS);

        if (g_screensaver_disabled)
        {
            SystemParametersInfoA(SPI_SETSCREENSAVEACTIVE, TRUE, NULL, 0);
        }

        ULONG(WINAPI* remove_handler)(PVOID) =
            (void*)real_GetProcAddress(GetModuleHandleA("Kernel32.dll"), "RemoveVectoredExceptionHandler");

        if (g_dbg_exception_handle && remove_handler)
            remove_handler(g_dbg_exception_handle);

        if (g_config.terminate_process == 2)
            TerminateProcess(GetCurrentProcess(), 0);

        break;
    }
    case DLL_THREAD_ATTACH:
    {
        if (g_config.singlecpu && !IsWine() && IsWindows11Version24H2OrGreater())
        {
            util_set_thread_affinity(GetCurrentThreadId());
        }
    }
    }

    return TRUE;
}

void DDEnableZoom()
{
    TRACE("%s [%p]\n", __FUNCTION__, _ReturnAddress());

    g_ddraw.zoom.enabled = TRUE;
}

BOOL DDIsWindowed()
{
    TRACE("%s [%p]\n", __FUNCTION__, _ReturnAddress());

    return g_config.windowed && !g_config.fullscreen;
}

FARPROC WINAPI DDGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    TRACE("%s [%p]\n", __FUNCTION__, _ReturnAddress());

    return real_GetProcAddress(hModule, lpProcName);
}

HRESULT WINAPI DirectDrawCreate(GUID FAR* lpGUID, LPDIRECTDRAW FAR* lplpDD, IUnknown FAR* pUnkOuter)
{
    TRACE("-> %s(lpGUID=%p, lplpDD=%p, pUnkOuter=%p) [%p]\n", __FUNCTION__, lpGUID, lplpDD, pUnkOuter, _ReturnAddress());

    HRESULT ret;

    if (util_caller_is_ddraw_wrapper(_ReturnAddress()) || g_config.flightsim98_hack)
    {
        if (lplpDD)
            *lplpDD = NULL;

        ret = DDERR_GENERIC;
    }
    else
    {
        ret = dd_CreateEx(lpGUID, (LPVOID*)lplpDD, &IID_IDirectDraw, pUnkOuter);
    }

    TRACE("<- %s\n", __FUNCTION__);
    return ret;
}

HRESULT WINAPI DirectDrawCreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR* lplpDDClipper, IUnknown FAR* pUnkOuter)
{
    TRACE(
        "-> %s(dwFlags=%08X, DDClipper=%p, unkOuter=%p) [%p]\n", 
        __FUNCTION__,
        (int)dwFlags,
        lplpDDClipper, 
        pUnkOuter, 
        _ReturnAddress());

    HRESULT ret = dd_CreateClipper(dwFlags, (IDirectDrawClipperImpl**)lplpDDClipper, pUnkOuter);

    TRACE("<- %s\n", __FUNCTION__);
    return ret;
}

HRESULT WINAPI DirectDrawCreateEx(GUID* lpGuid, LPVOID* lplpDD, REFIID iid, IUnknown* pUnkOuter)
{
    TRACE(
        "-> %s(lpGUID=%p, lplpDD=%p, riid=%08X, pUnkOuter=%p) [%p]\n",
        __FUNCTION__, 
        lpGuid,
        lplpDD, 
        iid,
        pUnkOuter, 
        _ReturnAddress());

    HRESULT ret;

    if (util_caller_is_ddraw_wrapper(_ReturnAddress()) || g_config.flightsim98_hack)
    {
        if (lplpDD)
            *lplpDD = NULL;

        ret = DDERR_GENERIC;
    }
    else
    {
        ret = dd_CreateEx(lpGuid, lplpDD, &IID_IDirectDraw7, pUnkOuter);
    }

    TRACE("<- %s\n", __FUNCTION__);
    return ret;
}

HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACK lpCallback, LPVOID lpContext)
{
    TRACE("-> %s(lpCallback=%p, lpContext=%p) [%p]\n", __FUNCTION__, lpCallback, lpContext, _ReturnAddress());

    if (lpCallback)
        lpCallback(NULL, "Primary Display Driver", "display", lpContext);

    TRACE("<- %s\n", __FUNCTION__);
    return DD_OK;
}

HRESULT WINAPI DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA lpCallback, LPVOID lpContext, DWORD dwFlags)
{
    TRACE(
        "-> %s(lpCallback=%p, lpContext=%p, dwFlags=%d) [%p]\n", 
        __FUNCTION__, 
        lpCallback, 
        lpContext, 
        dwFlags, 
        _ReturnAddress());

    if (lpCallback)
        lpCallback(NULL, "Primary Display Driver", "display", lpContext, NULL);

    TRACE("<- %s\n", __FUNCTION__);
    return DD_OK;
}

HRESULT WINAPI DirectDrawEnumerateExW(LPDDENUMCALLBACKEXW lpCallback, LPVOID lpContext, DWORD dwFlags)
{
    TRACE(
        "-> %s(lpCallback=%p, lpContext=%p, dwFlags=%d) [%p]\n", __FUNCTION__, 
        lpCallback, 
        lpContext, 
        dwFlags, 
        _ReturnAddress());

    if (lpCallback)
        lpCallback(NULL, L"Primary Display Driver", L"display", lpContext, NULL);

    TRACE("<- %s\n", __FUNCTION__);
    return DD_OK;
}

HRESULT WINAPI DirectDrawEnumerateW(LPDDENUMCALLBACKW lpCallback, LPVOID lpContext)
{
    TRACE("-> %s(lpCallback=%p, lpContext=%p) [%p]\n", __FUNCTION__, lpCallback, lpContext, _ReturnAddress());

    if (lpCallback)
        lpCallback(NULL, L"Primary Display Driver", L"display", lpContext);

    TRACE("<- %s\n", __FUNCTION__);
    return DD_OK;
}

DWORD WINAPI CompleteCreateSysmemSurface(DWORD a)
{
    TRACE("NOT_IMPLEMENTED -> %s() [%p]\n", __FUNCTION__, _ReturnAddress());
    DWORD ret = 0;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

HRESULT WINAPI D3DParseUnknownCommand(LPVOID lpCmd, LPVOID* lpRetCmd)
{
    TRACE("NOT_IMPLEMENTED -> %s(lpCmd=%p, lpRetCmd=%p) [%p]\n", __FUNCTION__, lpCmd, lpRetCmd, _ReturnAddress());
    HRESULT ret = E_FAIL;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

DWORD WINAPI AcquireDDThreadLock()
{
    TRACE("NOT_IMPLEMENTED -> %s() [%p]\n", __FUNCTION__, _ReturnAddress());
    DWORD ret = 0;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

DWORD WINAPI ReleaseDDThreadLock()
{
    TRACE("NOT_IMPLEMENTED -> %s() [%p]\n", __FUNCTION__, _ReturnAddress());
    DWORD ret = 0;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

DWORD WINAPI DDInternalLock(DWORD a, DWORD b)
{
    TRACE("NOT_IMPLEMENTED -> %s() [%p]\n", __FUNCTION__, _ReturnAddress());
    DWORD ret = 0;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}

DWORD WINAPI DDInternalUnlock(DWORD a)
{
    TRACE("NOT_IMPLEMENTED -> %s() [%p]\n", __FUNCTION__, _ReturnAddress());
    DWORD ret = 0;
    TRACE("NOT_IMPLEMENTED <- %s\n", __FUNCTION__);
    return ret;
}
