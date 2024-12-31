#include <windows.h>
#include "versionhelpers.h"

typedef NTSTATUS(WINAPI* RTLVERIFYVERSIONINFOPROC)(PRTL_OSVERSIONINFOEXW, ULONG, ULONGLONG);
typedef ULONGLONG(WINAPI* VERSETCONDITIONMASKPROC)(ULONGLONG, DWORD, BYTE);
typedef const char* (CDECL* WINE_GET_VERSIONPROC)();
typedef void (CDECL* WINE_GET_HOST_VERSIONPROC)(const char** sysname, const char** release);
typedef NTSTATUS(WINAPI* NTQUERYINFORMATIONTHREADPROC)(HANDLE, LONG, PVOID, ULONG, PULONG);

NTQUERYINFORMATIONTHREADPROC NtQueryInformationThread;
RTLVERIFYVERSIONINFOPROC RtlVerifyVersionInfo;
WINE_GET_VERSIONPROC wine_get_version;
WINE_GET_HOST_VERSIONPROC wine_get_host_version;

VERSETCONDITIONMASKPROC VerSetConditionMaskProc;

void imports_init()
{
    HMODULE mod = GetModuleHandleA("ntdll.dll");
    if (mod)
    {
        NtQueryInformationThread = (NTQUERYINFORMATIONTHREADPROC)GetProcAddress(mod, "NtQueryInformationThread");
        RtlVerifyVersionInfo = (RTLVERIFYVERSIONINFOPROC)GetProcAddress(mod, "RtlVerifyVersionInfo");
        wine_get_version = (WINE_GET_VERSIONPROC)GetProcAddress(mod, "wine_get_version");
        wine_get_host_version = (WINE_GET_HOST_VERSIONPROC)GetProcAddress(mod, "wine_get_host_version");
    }

    mod = GetModuleHandleA("Kernel32.dll");
    if (mod)
    {
        VerSetConditionMaskProc = (VERSETCONDITIONMASKPROC)GetProcAddress(mod, "VerSetConditionMask");
    }
}
