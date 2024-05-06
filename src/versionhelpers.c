#include <windows.h>
#include "versionhelpers.h"

typedef NTSTATUS(WINAPI* RTLVERIFYVERSIONINFOPROC)(PRTL_OSVERSIONINFOEXW, ULONG, ULONGLONG);
typedef const char* (CDECL* WINE_GET_VERSIONPROC)();
typedef void (CDECL* WINE_GET_HOST_VERSIONPROC)(const char** sysname, const char** release);

static RTLVERIFYVERSIONINFOPROC RtlVerifyVersionInfo;
static WINE_GET_VERSIONPROC wine_get_version;
static WINE_GET_HOST_VERSIONPROC wine_get_host_version;

/* GetProcAddress is rather slow so we use a function to initialize it once on startup */
void verhelp_init()
{
    HMODULE mod = GetModuleHandleA("ntdll.dll");
    if (mod)
    {
        RtlVerifyVersionInfo = (RTLVERIFYVERSIONINFOPROC)GetProcAddress(mod, "RtlVerifyVersionInfo");
        wine_get_version = (WINE_GET_VERSIONPROC)GetProcAddress(mod, "wine_get_version");
        wine_get_host_version = (WINE_GET_HOST_VERSIONPROC)GetProcAddress(mod, "wine_get_host_version");
    }
}

BOOL verhelp_verify_version(PRTL_OSVERSIONINFOEXW versionInfo, ULONG typeMask, ULONGLONG conditionMask)
{
    return RtlVerifyVersionInfo ?
        RtlVerifyVersionInfo(versionInfo, typeMask, conditionMask) == 0 :
        VerifyVersionInfoW(versionInfo, typeMask, conditionMask);
}

const char* verhelp_wine_get_version()
{
    return wine_get_version ? wine_get_version() : NULL;
}

void verhelp_wine_get_host_version(const char** sysname, const char** release)
{
    if (wine_get_host_version)
    {
        wine_get_host_version(sysname, release);
        return;
    }

    if (sysname)
        *sysname = NULL;

    if (release)
        *release = NULL;
}
