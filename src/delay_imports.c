#include <windows.h>
#include "versionhelpers.h"
#include "delay_imports.h"

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
