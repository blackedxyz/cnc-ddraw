/**
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */

#ifndef _INC_VERSIONHELPERS
#define _INC_VERSIONHELPERS

#ifdef __cplusplus
#define VERSIONHELPERAPI inline bool
#else
#define VERSIONHELPERAPI FORCEINLINE BOOL
#endif

#ifndef _WIN32_WINNT_WIN8
#define _WIN32_WINNT_WIN8                   0x0602
#endif
#ifndef _WIN32_WINNT_WINBLUE
#define _WIN32_WINNT_WINBLUE                0x0603
#endif
#ifndef _WIN32_WINNT_WINTHRESHOLD
#define _WIN32_WINNT_WINTHRESHOLD           0x0A00 /* ABRACADABRA_THRESHOLD*/
#endif
#ifndef _WIN32_WINNT_WIN10
#define _WIN32_WINNT_WIN10                  0x0A00 /* ABRACADABRA_THRESHOLD*/
#endif
#ifndef _WIN32_WINNT_WIN11
#define _WIN32_WINNT_WIN11                  0x0A00
#endif


void verhelp_init();
BOOL verhelp_verify_version(PRTL_OSVERSIONINFOEXW versionInfo, ULONG typeMask, ULONGLONG conditionMask);
const char* verhelp_wine_get_version();
void verhelp_wine_get_host_version(const char** sysname, const char** release);
BOOL verhelp_is_wine();
BOOL verhelp_is_macos();
BOOL verhelp_is_linux();

/* Original MS Functions */

VERSIONHELPERAPI IsWindowsVersionOrGreater(DWORD major, DWORD minor, DWORD build, WORD servpack)
{
    RTL_OSVERSIONINFOEXW vi = {sizeof(vi),major,minor,build,0,{0},servpack};
    return verhelp_verify_version(&vi, VER_MAJORVERSION|VER_MINORVERSION|VER_BUILDNUMBER|VER_SERVICEPACKMAJOR,
        VerSetConditionMask(VerSetConditionMask(VerSetConditionMask(VerSetConditionMask(0,
            VER_MAJORVERSION,VER_GREATER_EQUAL),
            VER_MINORVERSION,VER_GREATER_EQUAL),
            VER_BUILDNUMBER,VER_GREATER_EQUAL),
            VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL));
}

VERSIONHELPERAPI IsWindowsXPOrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0, 0);
}

VERSIONHELPERAPI IsWindowsXPSP1OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0, 1);
}

VERSIONHELPERAPI IsWindowsXPSP2OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0, 2);
}

VERSIONHELPERAPI IsWindowsXPSP3OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0, 3);
}

VERSIONHELPERAPI IsWindowsVistaOrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0, 0);
}

VERSIONHELPERAPI IsWindowsVistaSP1OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0, 1);
}

VERSIONHELPERAPI IsWindowsVistaSP2OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0, 2);
}

VERSIONHELPERAPI IsWindows7OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0, 0);
}

VERSIONHELPERAPI IsWindows7SP1OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0, 1);
}

VERSIONHELPERAPI IsWindows8OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8), 0, 0);
}

VERSIONHELPERAPI IsWindows8Point1OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINBLUE), LOBYTE(_WIN32_WINNT_WINBLUE), 0, 0);
}

VERSIONHELPERAPI IsWindowsThresholdOrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINTHRESHOLD), LOBYTE(_WIN32_WINNT_WINTHRESHOLD), 0, 0);
}

VERSIONHELPERAPI IsWindows10OrGreater(void) {
    return IsWindowsThresholdOrGreater();
}

VERSIONHELPERAPI IsWindows11OrGreater(void) {
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN11), LOBYTE(_WIN32_WINNT_WIN11), 22000, 0);
}

VERSIONHELPERAPI IsWindowsServer(void) {
    OSVERSIONINFOEXW vi = {sizeof(vi),0,0,0,0,{0},0,0,0,VER_NT_WORKSTATION};
    return !verhelp_verify_version(&vi, VER_PRODUCT_TYPE, VerSetConditionMask(0, VER_PRODUCT_TYPE, VER_EQUAL));
}

#endif
