#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include "debug.h"
#include "winapi_hooks.h"
#include "dd.h"
#include "hook.h"
#include "utils.h"
#include "config.h"
#include "mouse.h"


BOOL g_mouse_locked;
HHOOK g_mouse_hook;
HOOKPROC g_mouse_proc;
static HHOOK g_mouse_gm_hook;

void mouse_hook_init()
{
    if (g_mouse_gm_hook && UnhookWindowsHookEx(g_mouse_gm_hook))
    {
        g_mouse_gm_hook = NULL;
    }

    if (!g_ddraw.gui_thread_id)
        return;

    g_mouse_gm_hook =
        real_SetWindowsHookExA(
            WH_GETMESSAGE,
            mouse_gm_hook_proc,
            NULL,
            g_ddraw.gui_thread_id);
}

void mouse_hook_exit()
{
    if (g_mouse_gm_hook)
    {
        UnhookWindowsHookEx(g_mouse_gm_hook);
    }
}

void mouse_lock()
{
    if (g_config.devmode || g_ddraw.bnet_active || !g_ddraw.hwnd)
        return;

    if (g_hook_active && !g_mouse_locked && !util_is_minimized(g_ddraw.hwnd))
    {
        int game_count = InterlockedExchangeAdd((LONG*)&g_ddraw.show_cursor_count, 0);
        int cur_count = real_ShowCursor(TRUE) - 1;
        real_ShowCursor(FALSE);

        if (cur_count > game_count)
        {
            while (real_ShowCursor(FALSE) > game_count);
        }
        else if (cur_count < game_count)
        {
            while (real_ShowCursor(TRUE) < game_count);
        }

        real_SetCursor((HCURSOR)InterlockedExchangeAdd((LONG*)&g_ddraw.old_cursor, 0));

        RECT rc = { 0 };
        real_GetClientRect(g_ddraw.hwnd, &rc);
        real_MapWindowPoints(g_ddraw.hwnd, HWND_DESKTOP, (LPPOINT)&rc, 2);
        OffsetRect(&rc, g_ddraw.render.viewport.x, g_ddraw.render.viewport.y);

        int cur_x = InterlockedExchangeAdd((LONG*)&g_ddraw.cursor.x, 0);
        int cur_y = InterlockedExchangeAdd((LONG*)&g_ddraw.cursor.y, 0);

        real_SetCursorPos(
            g_config.adjmouse ? (int)(rc.left + (cur_x * g_ddraw.mouse.scale_x)) : rc.left + cur_x,
            g_config.adjmouse ? (int)(rc.top + (cur_y * g_ddraw.mouse.scale_y)) : rc.top + cur_y);

        CopyRect(&rc, &g_ddraw.mouse.rc);
        real_MapWindowPoints(g_ddraw.hwnd, HWND_DESKTOP, (LPPOINT)&rc, 2);
        real_ClipCursor(&rc);

        g_mouse_locked = TRUE;
    }
}

void mouse_unlock()
{
    if (g_config.devmode || !g_hook_active || !g_ddraw.hwnd)
        return;

    if (g_mouse_locked)
    {
        g_mouse_locked = FALSE;

        real_ClipCursor(NULL);
        ReleaseCapture();

        RECT rc = { 0 };
        real_GetClientRect(g_ddraw.hwnd, &rc);
        real_MapWindowPoints(g_ddraw.hwnd, HWND_DESKTOP, (LPPOINT)&rc, 2);
        OffsetRect(&rc, g_ddraw.render.viewport.x, g_ddraw.render.viewport.y);

        int cur_x = InterlockedExchangeAdd((LONG*)&g_ddraw.cursor.x, 0);
        int cur_y = InterlockedExchangeAdd((LONG*)&g_ddraw.cursor.y, 0);

        real_SetCursorPos(
            (int)(rc.left + (cur_x * g_ddraw.mouse.scale_x)),
            (int)(rc.top + (cur_y * g_ddraw.mouse.scale_y)));

        real_SetCursor(LoadCursor(NULL, IDC_ARROW));

        while (real_ShowCursor(TRUE) < 0);
    }
}

LRESULT CALLBACK mouse_gm_hook_proc(int code, WPARAM wParam, LPARAM lParam)
{
    MSG* msg = (MSG*)lParam;

    if (code < 0 || !g_ddraw.width || !msg || msg->hwnd != g_ddraw.hwnd)
        return CallNextHookEx(g_mouse_gm_hook, code, wParam, lParam);

    switch (LOWORD(msg->message))
    {
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONDBLCLK:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_MOUSEHOVER:
    case WM_LBUTTONDBLCLK:
    case WM_MBUTTONDBLCLK:
    case WM_RBUTTONDBLCLK:
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_MOUSEMOVE:
    {
        if (LOWORD(msg->message) == WM_MOUSEWHEEL)
        {
            POINT pt = { GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam) };
            real_ScreenToClient(g_ddraw.hwnd, &pt);
            msg->lParam = MAKELPARAM(pt.x, pt.y);
        }

        int x = max(GET_X_LPARAM(msg->lParam) - g_ddraw.mouse.x_adjust, 0);
        int y = max(GET_Y_LPARAM(msg->lParam) - g_ddraw.mouse.y_adjust, 0);

        if (g_config.adjmouse)
        {
            if (g_config.vhack && !g_config.devmode)
            {
                POINT pt = { 0, 0 };
                fake_GetCursorPos(&pt);

                x = pt.x;
                y = pt.y;
            }
            else
            {
                x = (DWORD)(roundf(x * g_ddraw.mouse.unscale_x));
                y = (DWORD)(roundf(y * g_ddraw.mouse.unscale_y));
            }
        }

        x = min(x, g_ddraw.width - 1);
        y = min(y, g_ddraw.height - 1);

        msg->lParam = MAKELPARAM(x, y);

        break;
    }
    }

    return CallNextHookEx(g_mouse_gm_hook, code, wParam, lParam);
}

LRESULT CALLBACK mouse_hook_proc(int code, WPARAM wParam, LPARAM lParam)
{
    if (!g_ddraw.ref)
        return g_mouse_proc(code, wParam, lParam);

    if (code < 0 || (!g_config.devmode && !g_mouse_locked))
        return CallNextHookEx(g_mouse_hook, code, wParam, lParam);

    fake_GetCursorPos(&((MOUSEHOOKSTRUCT*)lParam)->pt);

    return g_mouse_proc(code, wParam, lParam);
}
