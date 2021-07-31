#include "config.h"

void screenshot()
{
    int height = GetSystemMetrics(SM_CYVIRTUALSCREEN) - GetSystemMetrics(SM_YVIRTUALSCREEN);
    int width  = GetSystemMetrics(SM_CXVIRTUALSCREEN) - GetSystemMetrics(SM_XVIRTUALSCREEN);

    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    int bRet = BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

    createBMPFile(L"C:\\Users\\Franco\\Desktop\\xxx.bmp", createBitmapInfo(hBitmap), hBitmap, hDC);

    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);
}

PBITMAPINFO createBitmapInfo(HBITMAP hBmp)
{
    PBITMAPINFO mapInfo;
    BITMAP bitmap;
    WORD colorBits;

    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bitmap);
    colorBits = (WORD)(bitmap.bmPlanes * bitmap.bmBitsPixel);
    mapInfo = (PBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER));

    mapInfo->bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);
    mapInfo->bmiHeader.biWidth        = bitmap.bmWidth;
    mapInfo->bmiHeader.biHeight       = bitmap.bmHeight;
    mapInfo->bmiHeader.biPlanes       = bitmap.bmPlanes;
    mapInfo->bmiHeader.biBitCount     = bitmap.bmBitsPixel;
    mapInfo->bmiHeader.biCompression  = BI_RGB;
    mapInfo->bmiHeader.biClrImportant = 0;
    mapInfo->bmiHeader.biSizeImage    = ((mapInfo->bmiHeader.biWidth* colorBits+31)&~31)
                                        /8*mapInfo->bmiHeader.biHeight;
    return mapInfo;
}

void createBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC)
{
    PBITMAPINFOHEADER infoHeader;
    BITMAPFILEHEADER header;        
    HANDLE handle;                 
    LPBYTE bytes;
    DWORD temp;

    infoHeader = (PBITMAPINFOHEADER)pbi;
    bytes = (LPBYTE)malloc(infoHeader->biSizeImage);

    GetDIBits(hDC, hBMP, 0, (WORD)infoHeader->biHeight, bytes, pbi, DIB_RGB_COLORS);

    handle = CreateFile(pszFile, GENERIC_WRITE, (DWORD)0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
    header.bfType = 0x4d42;
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)  + infoHeader->biSize + infoHeader->biClrUsed * sizeof(RGBQUAD);
    header.bfSize    = (DWORD)(sizeof(BITMAPFILEHEADER) + infoHeader->biSize + infoHeader->biClrUsed * sizeof(RGBQUAD)
                       + infoHeader->biSizeImage);

    WriteFile(handle, (LPVOID)&header, sizeof(BITMAPFILEHEADER), (LPDWORD)&temp, NULL);
    WriteFile(handle, (LPVOID)infoHeader, sizeof(BITMAPINFOHEADER) + infoHeader->biClrUsed *
                sizeof(RGBQUAD), (LPDWORD)&temp, (NULL));
    WriteFile(handle, (LPSTR)bytes, (int)infoHeader->biSizeImage, (LPDWORD)&temp, NULL);

    CloseHandle(handle);
    free(bytes);
}