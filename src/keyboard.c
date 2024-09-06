#include <windows.h>
#include "debug.h"
#include "hook.h"
#include "dd.h"
#include "utils.h"
#include "config.h"
#include "keyboard.h"
#include "mouse.h"


HHOOK g_keyboard_hook;

void keyboard_hook_init()
{
    if (g_keyboard_hook && UnhookWindowsHookEx(g_keyboard_hook))
    {
        g_keyboard_hook = NULL;
    }  

    if (!g_ddraw.gui_thread_id)
        return;

    g_keyboard_hook = 
        real_SetWindowsHookExA(
            WH_KEYBOARD, 
            keyboard_hook_proc, 
            NULL, 
            g_ddraw.gui_thread_id);
}

void keyboard_hook_exit()
{
    if (g_keyboard_hook)
    {
        UnhookWindowsHookEx(g_keyboard_hook);
    }
}

LRESULT CALLBACK keyboard_hook_proc(int code, WPARAM wParam, LPARAM lParam)
{
    if (code < 0 || !wParam) // code != HC_ACTION || 
        return CallNextHookEx(g_keyboard_hook, code, wParam, lParam);

    BOOL alt_down = (lParam & (1 << 29));
    BOOL key_down = !(lParam & (1 << 30));
    BOOL key_up = !!(lParam & (1 << 31));

    if (wParam == g_config.hotkeys.toggle_fullscreen && alt_down)
    {
        if (key_down)
            util_toggle_fullscreen();

        return 1;
    }

    if (wParam == g_config.hotkeys.toggle_maximize &&
        g_config.resizable &&
        g_config.windowed &&
        !g_config.fullscreen &&
        alt_down)
    {
        if (key_down)
            util_toggle_maximize();

        return 1;
    }

    if (g_config.homm_hack && wParam == VK_F4) /* Heroes of Might and Magic 3 and 4 */
    {
        if (key_down)
            util_toggle_fullscreen();

        return 1;
    }

    if (wParam == VK_CONTROL || wParam == g_config.hotkeys.unlock_cursor1)
    {
        if ((real_GetAsyncKeyState(VK_CONTROL) & 0x8000) && 
            (real_GetAsyncKeyState(g_config.hotkeys.unlock_cursor1) & 0x8000))
        {
            mouse_unlock();
            return 1;
        }
    }

    if (wParam == g_config.hotkeys.unlock_cursor2 || wParam == VK_MENU || wParam == VK_CONTROL)
    {
        if ((real_GetAsyncKeyState(VK_RMENU) & 0x8000) && 
            (real_GetAsyncKeyState(g_config.hotkeys.unlock_cursor2) & 0x8000))
        {
            mouse_unlock();
            return 1;
        }
    }

    if (key_up && wParam == g_config.hotkeys.screenshot)
    {
        ss_take_screenshot(g_ddraw.primary);
    }

    return CallNextHookEx(g_keyboard_hook, code, wParam, lParam);
}
