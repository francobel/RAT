#include <Windows.h>

void screenshot();
PBITMAPINFO createBitmapInfo(HBITMAP hBmp);
void createBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);