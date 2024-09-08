#ifndef MOUSE_H
#define MOUSE_H

void mouse_hook_init();
void mouse_hook_exit();
void mouse_lock();
void mouse_unlock();
LRESULT CALLBACK mouse_gm_hook_proc(int code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK mouse_hook_proc(int code, WPARAM wParam, LPARAM lParam);

extern BOOL g_mouse_locked;
extern HHOOK g_mouse_hook;
extern HOOKPROC g_mouse_proc;

#endif
