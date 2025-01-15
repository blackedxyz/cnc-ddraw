#include <windows.h>
#include <stdio.h>
#include "directinput.h"
#include "dd.h"
#include "winapi_hooks.h"
#include "hook.h"
#include "debug.h"
#include "dllmain.h"
#include "config.h"
#include "utils.h"
#include "patch.h"
#include "versionhelpers.h"

#ifdef _MSC_VER
#include "detours.h"
#endif

BOOL g_hook_active;

GETCURSORPOSPROC real_GetCursorPos = GetCursorPos;
CLIPCURSORPROC real_ClipCursor = ClipCursor;
SHOWCURSORPROC real_ShowCursor = ShowCursor;
SETCURSORPROC real_SetCursor = SetCursor;
GETWINDOWRECTPROC real_GetWindowRect = GetWindowRect;
GETCLIENTRECTPROC real_GetClientRect = GetClientRect;
CLIENTTOSCREENPROC real_ClientToScreen = ClientToScreen;
SCREENTOCLIENTPROC real_ScreenToClient = ScreenToClient;
SETCURSORPOSPROC real_SetCursorPos = SetCursorPos;
WINDOWFROMPOINTPROC real_WindowFromPoint = WindowFromPoint;
GETCLIPCURSORPROC real_GetClipCursor = GetClipCursor;
GETCURSORINFOPROC real_GetCursorInfo = GetCursorInfo;
GETSYSTEMMETRICSPROC real_GetSystemMetrics = GetSystemMetrics;
SETWINDOWPOSPROC real_SetWindowPos = SetWindowPos;
MOVEWINDOWPROC real_MoveWindow = MoveWindow;
SENDMESSAGEAPROC real_SendMessageA = SendMessageA;
SETWINDOWLONGAPROC real_SetWindowLongA = SetWindowLongA;
GETWINDOWLONGAPROC real_GetWindowLongA = GetWindowLongA;
ENABLEWINDOWPROC real_EnableWindow = EnableWindow;
CREATEWINDOWEXAPROC real_CreateWindowExA = CreateWindowExA;
DESTROYWINDOWPROC real_DestroyWindow = DestroyWindow;
MAPWINDOWPOINTSPROC real_MapWindowPoints = MapWindowPoints;
SHOWWINDOWPROC real_ShowWindow = ShowWindow;
GETTOPWINDOWPROC real_GetTopWindow = GetTopWindow;
GETFOREGROUNDWINDOWPROC real_GetForegroundWindow = GetForegroundWindow;
STRETCHBLTPROC real_StretchBlt = StretchBlt;
BITBLTPROC real_BitBlt = BitBlt;
SETDIBITSTODEVICEPROC real_SetDIBitsToDevice = SetDIBitsToDevice;
STRETCHDIBITSPROC real_StretchDIBits = StretchDIBits;
SETFOREGROUNDWINDOWPROC real_SetForegroundWindow = SetForegroundWindow;
SETWINDOWSHOOKEXAPROC real_SetWindowsHookExA = SetWindowsHookExA;
PEEKMESSAGEAPROC real_PeekMessageA = PeekMessageA;
GETMESSAGEAPROC real_GetMessageA = GetMessageA;
GETWINDOWPLACEMENTPROC real_GetWindowPlacement = GetWindowPlacement;
SETWINDOWPLACEMENTPROC real_SetWindowPlacement = SetWindowPlacement;
ENUMDISPLAYSETTINGSAPROC real_EnumDisplaySettingsA = EnumDisplaySettingsA;
DEFWINDOWPROCAPROC real_DefWindowProcA = DefWindowProcA;
SETPARENTPROC real_SetParent = SetParent;
BEGINPAINTPROC real_BeginPaint = BeginPaint;
GETKEYSTATEPROC real_GetKeyState = GetKeyState;
GETASYNCKEYSTATEPROC real_GetAsyncKeyState = GetAsyncKeyState;
GETDEVICECAPSPROC real_GetDeviceCaps = GetDeviceCaps;
CREATEFONTINDIRECTAPROC real_CreateFontIndirectA = CreateFontIndirectA;
CREATEFONTAPROC real_CreateFontA = CreateFontA;
GETSYSTEMPALETTEENTRIESPROC real_GetSystemPaletteEntries = GetSystemPaletteEntries;
SELECTPALETTEPROC real_SelectPalette = SelectPalette;
REALIZEPALETTEPROC real_RealizePalette = RealizePalette;
LOADLIBRARYAPROC real_LoadLibraryA = LoadLibraryA;
LOADLIBRARYWPROC real_LoadLibraryW = LoadLibraryW;
LOADLIBRARYEXAPROC real_LoadLibraryExA = LoadLibraryExA;
LOADLIBRARYEXWPROC real_LoadLibraryExW = LoadLibraryExW;
GETPROCADDRESSPROC real_GetProcAddress = GetProcAddress;
GETDISKFREESPACEAPROC real_GetDiskFreeSpaceA = GetDiskFreeSpaceA;
GETVERSIONPROC real_GetVersion = GetVersion;
GETVERSIONEXAPROC real_GetVersionExA = GetVersionExA;
COCREATEINSTANCEPROC real_CoCreateInstance = CoCreateInstance;
MCISENDCOMMANDAPROC real_mciSendCommandA = mciSendCommandA;
SETUNHANDLEDEXCEPTIONFILTERPROC real_SetUnhandledExceptionFilter = SetUnhandledExceptionFilter;
AVISTREAMGETFRAMEOPENPROC real_AVIStreamGetFrameOpen = AVIStreamGetFrameOpen;

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
SETWINDOWLONGWPROC real_SetWindowLongW = SetWindowLongW;
#else
SETWINDOWLONGWPROC real_SetWindowLongW;
#endif

HOOKLIST g_hook_hooklist[] =
{
    {
        "user32.dll",
        {
            { "GetCursorPos", (PROC)fake_GetCursorPos, (PROC*)&real_GetCursorPos, 0 },
            { "ClipCursor", (PROC)fake_ClipCursor, (PROC*)&real_ClipCursor, 0 },
            { "ShowCursor", (PROC)fake_ShowCursor, (PROC*)&real_ShowCursor, 0 },
            { "SetCursor", (PROC)fake_SetCursor, (PROC*)&real_SetCursor, 0 },
            { "GetWindowRect", (PROC)fake_GetWindowRect, (PROC*)&real_GetWindowRect, 0 },
            { "GetClientRect", (PROC)fake_GetClientRect, (PROC*)&real_GetClientRect, 0 },
            { "ClientToScreen", (PROC)fake_ClientToScreen, (PROC*)&real_ClientToScreen, 0 },
            { "ScreenToClient", (PROC)fake_ScreenToClient, (PROC*)&real_ScreenToClient, 0 },
            { "SetCursorPos", (PROC)fake_SetCursorPos, (PROC*)&real_SetCursorPos, 0 },
            { "GetClipCursor", (PROC)fake_GetClipCursor, (PROC*)&real_GetClipCursor, 0 },
            { "WindowFromPoint", (PROC)fake_WindowFromPoint, (PROC*)&real_WindowFromPoint, 0 },
            { "GetCursorInfo", (PROC)fake_GetCursorInfo, (PROC*)&real_GetCursorInfo, 0 },
            { "GetSystemMetrics", (PROC)fake_GetSystemMetrics, (PROC*)&real_GetSystemMetrics, 0 },
            { "SetWindowPos", (PROC)fake_SetWindowPos, (PROC*)&real_SetWindowPos, 0 },
            { "MoveWindow", (PROC)fake_MoveWindow, (PROC*)&real_MoveWindow, 0 },
            { "SendMessageA", (PROC)fake_SendMessageA, (PROC*)&real_SendMessageA, 0 },
            { "SetWindowLongA", (PROC)fake_SetWindowLongA, (PROC*)&real_SetWindowLongA, 0 },
            { "GetWindowLongA", (PROC)fake_GetWindowLongA, (PROC*)&real_GetWindowLongA, 0 },
            { "EnableWindow", (PROC)fake_EnableWindow, (PROC*)&real_EnableWindow, 0 },
            { "CreateWindowExA", (PROC)fake_CreateWindowExA, (PROC*)&real_CreateWindowExA, 0 },
            { "DestroyWindow", (PROC)fake_DestroyWindow, (PROC*)&real_DestroyWindow, 0 },
            { "MapWindowPoints", (PROC)fake_MapWindowPoints, (PROC*)&real_MapWindowPoints, 0 },
            { "ShowWindow", (PROC)fake_ShowWindow, (PROC*)&real_ShowWindow, 0 },
            { "GetTopWindow", (PROC)fake_GetTopWindow, (PROC*)&real_GetTopWindow, 0 },
            { "GetForegroundWindow", (PROC)fake_GetForegroundWindow, (PROC*)&real_GetForegroundWindow, 0 },
            { "PeekMessageA", (PROC)fake_PeekMessageA, (PROC*)&real_PeekMessageA, 0 },
            { "GetMessageA", (PROC)fake_GetMessageA, (PROC*)&real_GetMessageA, 0 },
            { "GetWindowPlacement", (PROC)fake_GetWindowPlacement, (PROC*)&real_GetWindowPlacement, 0 },
            { "SetWindowPlacement", (PROC)fake_SetWindowPlacement, (PROC*)&real_SetWindowPlacement, 0 },
            { "EnumDisplaySettingsA", (PROC)fake_EnumDisplaySettingsA, (PROC*)&real_EnumDisplaySettingsA, 0 },
            { "DefWindowProcA", (PROC)fake_DefWindowProcA, (PROC*)&real_DefWindowProcA, 0 },
            { "SetParent", (PROC)fake_SetParent, (PROC*)&real_SetParent, 0 },
            { "BeginPaint", (PROC)fake_BeginPaint, (PROC*)&real_BeginPaint, 0 },
            { "GetKeyState", (PROC)fake_GetKeyState, (PROC*)&real_GetKeyState, 0 },
            { "GetAsyncKeyState", (PROC)fake_GetAsyncKeyState, (PROC*)&real_GetAsyncKeyState, 0 },
            { "SetForegroundWindow", (PROC)fake_SetForegroundWindow, (PROC*)&real_SetForegroundWindow, 0 },
            { "SetWindowsHookExA", (PROC)fake_SetWindowsHookExA, (PROC*)&real_SetWindowsHookExA, 0 },

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
            { "SetWindowLongW", (PROC)fake_SetWindowLongW, (PROC*)&real_SetWindowLongW, 0 },
#endif

            { "", NULL, NULL, 0 }
        }
    },
    {
        "ole32.dll",
        {
            { "CoCreateInstance", (PROC)fake_CoCreateInstance, (PROC*)&real_CoCreateInstance, HOOK_SKIP_2 },
            { "", NULL, NULL, 0 }
        }
    },
    {
        "winmm.dll",
        {
            { "mciSendCommandA", (PROC)fake_mciSendCommandA, (PROC*)&real_mciSendCommandA, HOOK_SKIP_2 },
            { "", NULL, NULL, 0 }
        }
    },
    {
        "Avifil32.dll",
        {
            { "AVIStreamGetFrameOpen", (PROC)fake_AVIStreamGetFrameOpen, (PROC*)&real_AVIStreamGetFrameOpen, 0 },
            { "", NULL, NULL, 0 }
        }
    },
    {
        "dinput.dll",
        {
            { "DirectInputCreateA", (PROC)fake_DirectInputCreateA, (PROC*)&real_DirectInputCreateA, HOOK_SKIP_2 },
            //{ "DirectInputCreateW", (PROC)fake_DirectInputCreateW, (PROC*)&real_DirectInputCreateW, HOOK_SKIP_2 },
            { "DirectInputCreateEx", (PROC)fake_DirectInputCreateEx, (PROC*)&real_DirectInputCreateEx, HOOK_SKIP_2 },
            { "", NULL, NULL, 0 }
        }
    },
    {
        "dinput8.dll",
        {
            { "DirectInput8Create", (PROC)fake_DirectInput8Create, (PROC*)&real_DirectInput8Create, HOOK_SKIP_2 },
            { "", NULL, NULL, 0 }
        }
    },
    {
        "gdi32.dll",
        {
            { "BitBlt", (PROC)fake_BitBlt, (PROC*)&real_BitBlt, HOOK_SKIP_2 },
            { "StretchBlt", (PROC)fake_StretchBlt, (PROC*)&real_StretchBlt, HOOK_SKIP_2 },
            { "SetDIBitsToDevice", (PROC)fake_SetDIBitsToDevice, (PROC*)&real_SetDIBitsToDevice, HOOK_SKIP_2 },
            { "StretchDIBits", (PROC)fake_StretchDIBits, (PROC*)&real_StretchDIBits, HOOK_SKIP_2 },
            { "GetDeviceCaps", (PROC)fake_GetDeviceCaps, (PROC*)&real_GetDeviceCaps, HOOK_LOCAL_ONLY },
            { "GetDeviceCaps", (PROC)fake_GetDeviceCaps_system, NULL, HOOK_SYSTEM_ONLY },
            { "CreateFontA", (PROC)fake_CreateFontA, (PROC*)&real_CreateFontA, 0 },
            { "GetSystemPaletteEntries", (PROC)fake_GetSystemPaletteEntries, (PROC*)&real_GetSystemPaletteEntries, 0 },
            { "SelectPalette", (PROC)fake_SelectPalette, (PROC*)&real_SelectPalette, 0 },
            { "RealizePalette", (PROC)fake_RealizePalette, (PROC*)&real_RealizePalette, 0 },
            { "CreateFontIndirectA", (PROC)fake_CreateFontIndirectA, (PROC*)&real_CreateFontIndirectA, 0 },
            { "", NULL, NULL, 0 }
        }
    },
    {
        "WING32.DLL",
        {
            { "WinGBitBlt", (PROC)fake_WinGBitBlt, NULL, 0 },
            { "WinGStretchBlt", (PROC)fake_WinGStretchBlt, NULL, 0 },
            { "", NULL, NULL, 0 }
        }
    },
    {
        "kernel32.dll",
        {
            { "LoadLibraryA", (PROC)fake_LoadLibraryA, (PROC*)&real_LoadLibraryA, HOOK_SKIP_2 },
            { "LoadLibraryW", (PROC)fake_LoadLibraryW, (PROC*)&real_LoadLibraryW, HOOK_SKIP_2 },
            { "LoadLibraryExA", (PROC)fake_LoadLibraryExA, (PROC*)&real_LoadLibraryExA, HOOK_SKIP_2 },
            { "LoadLibraryExW", (PROC)fake_LoadLibraryExW, (PROC*)&real_LoadLibraryExW, HOOK_SKIP_2 },
            { "GetProcAddress", (PROC)fake_GetProcAddress, (PROC*)&real_GetProcAddress, HOOK_SKIP_2 },
            { "GetDiskFreeSpaceA", (PROC)fake_GetDiskFreeSpaceA, (PROC*)&real_GetDiskFreeSpaceA, 0 },
            { "GetVersion", (PROC)fake_GetVersion, (PROC*)&real_GetVersion, 0 },
            { "GetVersionExA", (PROC)fake_GetVersionExA, (PROC*)&real_GetVersionExA, 0 },
#if defined(_DEBUG) && defined(__GNUC__)
            { "SetUnhandledExceptionFilter", (PROC)fake_SetUnhandledExceptionFilter, (PROC*)&real_SetUnhandledExceptionFilter, 0 },
#endif
            { "", NULL, NULL, 0 }
        }
    },
    {
        "",
        {
            { "", NULL, NULL, 0 }
        }
    }
};

void hook_patch_iat(HMODULE hmod, BOOL unhook, char* module_name, char* function_name, PROC new_function)
{
    HOOKLIST hooks[2];
    memset(&hooks, 0, sizeof(hooks));

    hooks[0].data[0].new_function = new_function;

    strncpy(hooks[0].module_name, module_name, sizeof(hooks[0].module_name) - 1);
    strncpy(hooks[0].data[0].function_name, function_name, sizeof(hooks[0].data[0].function_name) - 1);

    hook_patch_iat_list(hmod, unhook, (HOOKLIST*)&hooks, FALSE);
}

void hook_patch_obfuscated_iat_list(HMODULE hmod, BOOL unhook, HOOKLIST* hooks, BOOL is_local)
{
    if (!hmod || hmod == INVALID_HANDLE_VALUE || !hooks)
        return;

    __try
    {
        PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)hmod;
        if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
            return;

        PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((DWORD)hmod + (DWORD)dos_header->e_lfanew);
        if (nt_headers->Signature != IMAGE_NT_SIGNATURE)
            return;

        DWORD import_desc_rva = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
        if (!import_desc_rva)
            return;

        PIMAGE_IMPORT_DESCRIPTOR import_desc = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)hmod + import_desc_rva);

        while (import_desc->FirstThunk)
        {
            if (!import_desc->Name)
            {
                import_desc++;
                continue;
            }

            for (int i = 0; hooks[i].module_name[0]; i++)
            {
                char* imp_module_name = (char*)((DWORD)hmod + import_desc->Name);

                if (_stricmp(imp_module_name, hooks[i].module_name) == 0)
                {
                    HMODULE cur_mod = GetModuleHandleA(hooks[i].module_name);

                    PIMAGE_THUNK_DATA first_thunk = (void*)((DWORD)hmod + import_desc->FirstThunk);

                    while (first_thunk->u1.Function)
                    {
                        for (int x = 0; hooks[i].data[x].function_name[0]; x++)
                        {
                            /* GetProcAddress is slow, save the pointer and reuse it for better performance */
                            DWORD org_function = (DWORD)InterlockedExchangeAdd((LONG*)&hooks[i].data[x].org_function, 0);

                            if (!org_function || cur_mod != hooks[i].data[x].mod)
                            {
                                hooks[i].data[x].mod = cur_mod;

                                org_function = (DWORD)real_GetProcAddress(cur_mod, hooks[i].data[x].function_name);

                                InterlockedExchange((LONG*)&hooks[i].data[x].org_function, (LONG)org_function);
                            }

                            if (!hooks[i].data[x].new_function || !org_function)
                                continue;

                            if (!is_local && (hooks[i].data[x].flags & HOOK_LOCAL_ONLY))
                                continue;

                            if (is_local && (hooks[i].data[x].flags & HOOK_SYSTEM_ONLY))
                                continue;

                            if (unhook)
                            {
                                if (first_thunk->u1.Function == (DWORD)hooks[i].data[x].new_function)
                                {
                                    DWORD op;

                                    if (VirtualProtect(
                                        &first_thunk->u1.Function, 
                                        sizeof(DWORD), 
                                        PAGE_READWRITE, 
                                        &op))
                                    {
                                        first_thunk->u1.Function = org_function;

                                        VirtualProtect(&first_thunk->u1.Function, sizeof(DWORD), op, &op);
                                    }

                                    break;
                                }
                            }
                            else
                            {
                                if (first_thunk->u1.Function == org_function)
                                {
                                    DWORD op;

                                    if (VirtualProtect(
                                        &first_thunk->u1.Function, 
                                        sizeof(DWORD), 
                                        PAGE_READWRITE, 
                                        &op))
                                    {
                                        first_thunk->u1.Function = (DWORD)hooks[i].data[x].new_function;

                                        VirtualProtect(&first_thunk->u1.Function, sizeof(DWORD), op, &op);
                                    }

                                    break;
                                }
                            }
                        }

                        first_thunk++;
                    }

                    break;
                }
            }

            import_desc++;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

void hook_patch_iat_list(HMODULE hmod, BOOL unhook, HOOKLIST* hooks, BOOL is_local)
{
    hook_patch_obfuscated_iat_list(hmod, unhook, hooks, is_local);

    if (!hmod || hmod == INVALID_HANDLE_VALUE || !hooks)
        return;

    __try
    {
        PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)hmod;
        if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
            return;

        PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((DWORD)hmod + (DWORD)dos_header->e_lfanew);
        if (nt_headers->Signature != IMAGE_NT_SIGNATURE)
            return;

        DWORD import_desc_rva = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
        if (!import_desc_rva)
            return;

        PIMAGE_IMPORT_DESCRIPTOR import_desc = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)hmod + import_desc_rva);

        while (import_desc->FirstThunk)
        {
            if (!import_desc->OriginalFirstThunk || !import_desc->Name)
            {
                import_desc++;
                continue;
            }

            for (int i = 0; hooks[i].module_name[0]; i++)
            {
                char* imp_module_name = (char*)((DWORD)hmod + import_desc->Name);

                if (_stricmp(imp_module_name, hooks[i].module_name) == 0)
                {
                    PIMAGE_THUNK_DATA first_thunk = (void*)((DWORD)hmod + import_desc->FirstThunk);
                    PIMAGE_THUNK_DATA o_first_thunk = (void*)((DWORD)hmod + import_desc->OriginalFirstThunk);

                    while (first_thunk->u1.Function)
                    {
                        if (!o_first_thunk->u1.AddressOfData)
                        {
                            first_thunk++;
                            o_first_thunk++;
                            continue;
                        }

                        PIMAGE_IMPORT_BY_NAME import = (void*)((DWORD)dos_header + o_first_thunk->u1.AddressOfData);

                        if ((o_first_thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG) == 0)
                        {
                            for (int x = 0; hooks[i].data[x].function_name[0]; x++)
                            {
                                if (!unhook && !hooks[i].data[x].new_function)
                                    continue;

                                if (!is_local && (hooks[i].data[x].flags & HOOK_LOCAL_ONLY))
                                    continue;

                                if (is_local && (hooks[i].data[x].flags & HOOK_SYSTEM_ONLY))
                                    continue;

#if defined(__GNUC__)
                                if (util_is_bad_read_ptr((void*)import->Name))
                                    continue;
#endif

                                if (strcmp((const char*)import->Name, hooks[i].data[x].function_name) == 0)
                                {
                                    DWORD op;

                                    if (VirtualProtect(
                                        &first_thunk->u1.Function, 
                                        sizeof(DWORD), 
                                        PAGE_READWRITE, 
                                        &op))
                                    {
                                        if (unhook)
                                        {
                                            DWORD org =
                                                (DWORD)real_GetProcAddress(
                                                    GetModuleHandleA(hooks[i].module_name),
                                                    hooks[i].data[x].function_name);

                                            if (org && first_thunk->u1.Function != org)
                                            {
                                                first_thunk->u1.Function = org;
                                            }
                                        }
                                        else
                                        {
                                            if (first_thunk->u1.Function != (DWORD)hooks[i].data[x].new_function)
                                                first_thunk->u1.Function = (DWORD)hooks[i].data[x].new_function;
                                        }

                                        VirtualProtect(&first_thunk->u1.Function, sizeof(DWORD), op, &op);
                                    }

                                    break;
                                }
                            }
                        }

                        first_thunk++;
                        o_first_thunk++;
                    }

                    break;
                }
            }

            import_desc++;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

BOOL hook_got_ddraw_import(HMODULE mod, BOOL check_imported_dlls)
{
    if (!mod)
        return FALSE;

    __try
    {
        PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)mod;
        if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
            return FALSE;

        PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((DWORD)mod + (DWORD)dos_header->e_lfanew);
        if (nt_headers->Signature != IMAGE_NT_SIGNATURE)
            return FALSE;

        DWORD import_desc_rva = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
        if (!import_desc_rva)
            return FALSE;

        PIMAGE_IMPORT_DESCRIPTOR import_desc = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)mod + import_desc_rva);

        while (import_desc->FirstThunk)
        {
            if (import_desc->Name)
            {
                char* imp_module_name = (char*)((DWORD)mod + import_desc->Name);

                if (_stricmp(imp_module_name, "ddraw.dll") == 0)
                {
                    PIMAGE_THUNK_DATA first_thunk = (void*)((DWORD)mod + import_desc->FirstThunk);

                    if (first_thunk->u1.Function)
                        return TRUE;
                }
                else if (check_imported_dlls)
                {
                    if (hook_got_ddraw_import(GetModuleHandleA(imp_module_name), FALSE))
                        return TRUE;
                }
            }

            import_desc++;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }

    return FALSE;
}

void hook_create(HOOKLIST* hooks, BOOL initial_hook)
{
#ifdef _MSC_VER
    if ((g_config.hook == 2) && initial_hook)
    {
        for (int i = 0; hooks[i].module_name[0]; i++)
        {
            for (int x = 0; hooks[i].data[x].function_name[0]; x++)
            {
                if ((hooks[i].data[x].flags & HOOK_SKIP_2))
                    continue;

                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                DetourAttach((PVOID*)hooks[i].data[x].function, (PVOID)hooks[i].data[x].new_function);
                DetourTransactionCommit();
            }
        }
    }
#endif

    if (g_config.hook == 3 || g_config.hook == 4)
    {
        char game_exe_path[MAX_PATH] = { 0 };
        char game_dir[MAX_PATH] = { 0 };

        if (GetModuleFileNameA(NULL, game_exe_path, MAX_PATH))
        {
            _splitpath(game_exe_path, NULL, game_dir, NULL, NULL);

            char mod_path[MAX_PATH] = { 0 };
            char mod_dir[MAX_PATH] = { 0 };
            char mod_filename[MAX_PATH] = { 0 };
            HMODULE hmod = NULL;

            while ((hmod = util_enumerate_modules(hmod)))
            {
                if (hmod == g_ddraw_module)
                    continue;

                if (GetModuleFileNameA(hmod, mod_path, MAX_PATH))
                {
                    if (initial_hook)
                    {
                        TRACE("Module %s = %p\n", mod_path, hmod);
                    }

                    _splitpath(mod_path, NULL, mod_dir, mod_filename, NULL);

                    /* Don't hook reshade/swiftshader/mesa3d */
                    if (_strcmpi(mod_filename, "opengl32") == 0 ||
                        _strcmpi(mod_filename, "libgallium_wgl") == 0 ||
                        _strcmpi(mod_filename, "libglapi") == 0 ||
                        _strcmpi(mod_filename, "d3d9") == 0 ||
                        _strcmpi(mod_filename, "mdraw") == 0 ||
                        _strcmpi(mod_filename, "SH33W32") == 0 ||
                        _strcmpi(mod_filename, "Shw32") == 0)
                        continue;

                    BOOL is_local = _strnicmp(game_dir, mod_dir, strlen(game_dir)) == 0;
                    BOOL wine_hook = IsWine() && _strcmpi(mod_filename, "mciavi32") == 0;

                    if (is_local ||
                        wine_hook ||
                        _strcmpi(mod_filename, "QuickTime") == 0 ||
                        _strcmpi(mod_filename, "MSVFW32") == 0 ||
                        _strcmpi(mod_filename, "quartz") == 0 ||
                        _strcmpi(mod_filename, "winmm") == 0)
                    {
                        hook_patch_iat_list(hmod, FALSE, hooks, is_local);
                    }
                }
            }
        }
    }

    if (g_config.hook == 1)
    {
        hook_patch_iat_list(GetModuleHandle(NULL), FALSE, hooks, TRUE);
    }
}

void hook_revert(HOOKLIST* hooks)
{
#ifdef _MSC_VER
    if (g_config.hook == 2)
    {
        for (int i = 0; hooks[i].module_name[0]; i++)
        {
            for (int x = 0; hooks[i].data[x].function_name[0]; x++)
            {
                if ((hooks[i].data[x].flags & HOOK_SKIP_2))
                    continue;

                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                DetourDetach((PVOID*)hooks[i].data[x].function, (PVOID)hooks[i].data[x].new_function);
                DetourTransactionCommit();
            }
        }
    }
#endif

    if (g_config.hook == 3 || g_config.hook == 4)
    {
        char game_exe_path[MAX_PATH] = { 0 };
        char game_dir[MAX_PATH] = { 0 };

        if (GetModuleFileNameA(NULL, game_exe_path, MAX_PATH))
        {
            _splitpath(game_exe_path, NULL, game_dir, NULL, NULL);

            char mod_path[MAX_PATH] = { 0 };
            char mod_dir[MAX_PATH] = { 0 };
            char mod_filename[MAX_PATH] = { 0 };
            HMODULE hmod = NULL;

            while ((hmod = util_enumerate_modules(hmod)))
            {
                if (hmod == g_ddraw_module)
                    continue;

                if (GetModuleFileNameA(hmod, mod_path, MAX_PATH))
                {
                    _splitpath(mod_path, NULL, mod_dir, mod_filename, NULL);

                    BOOL is_local = _strnicmp(game_dir, mod_dir, strlen(game_dir)) == 0;
                    BOOL wine_hook = IsWine() && _strcmpi(mod_filename, "mciavi32") == 0;

                    if (is_local ||
                        wine_hook ||
                        _strcmpi(mod_filename, "QuickTime") == 0 ||
                        _strcmpi(mod_filename, "MSVFW32") == 0 ||
                        _strcmpi(mod_filename, "quartz") == 0 ||
                        _strcmpi(mod_filename, "winmm") == 0)
                    {
                        hook_patch_iat_list(hmod, TRUE, hooks, is_local);
                    }
                }
            }
        }
    }

    if (g_config.hook == 1)
    {
        hook_patch_iat_list(GetModuleHandle(NULL), TRUE, hooks, TRUE);
    }
}

void hook_init()
{
    if (!g_hook_active)
    {
        if (g_config.hook == 4 && hook_got_ddraw_import(GetModuleHandleA(NULL), TRUE))
        {
            /* Switch to 3 if we can be sure that ddraw.dll will not be unloaded from the process */
            g_config.hook = 3;

            TRACE("Switched to hook 3\n");
        }
    }

    if (!g_hook_active || g_config.hook == 3 || g_config.hook == 4)
    {
#if defined(_DEBUG) && defined(_MSC_VER)
        if (!g_hook_active)
        {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach((PVOID*)&real_SetUnhandledExceptionFilter, (PVOID)fake_SetUnhandledExceptionFilter);
            DetourTransactionCommit();

            if (!IsDebuggerPresent())
            {
                patch_ljmp((void*)_invoke_watson, (void*)dbg_invoke_watson);
            }
        }
#endif

        if (!g_hook_active)
        {
            hook_patch_iat(GetModuleHandle("AcGenral"), FALSE, "user32.dll", "SetWindowsHookExA", (PROC)fake_SetWindowsHookExA);
        }

        hook_create((HOOKLIST*)&g_hook_hooklist, !g_hook_active);

        g_hook_active = TRUE;
    }
}

void hook_exit()
{
    if (g_hook_active)
    {
        g_hook_active = FALSE;

        hook_revert((HOOKLIST*)&g_hook_hooklist);

#if defined(_DEBUG)
#if defined(_MSC_VER)
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach((PVOID*)&real_SetUnhandledExceptionFilter, (PVOID)fake_SetUnhandledExceptionFilter);
        DetourTransactionCommit();
#endif
        real_SetUnhandledExceptionFilter(g_dbg_exception_filter);
#endif

        hook_patch_iat(GetModuleHandle("AcGenral"), TRUE, "user32.dll", "SetWindowsHookExA", (PROC)fake_SetWindowsHookExA);
    }
}
