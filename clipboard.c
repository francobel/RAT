#include "clipboard.h"

void clipboard()
{
    HANDLE handle;

    OpenClipboard(NULL);
    handle = GetClipboardData(CF_TEXT);
    GlobalLock(handle);

    printf("%s\n\n", (char*)handle);

    GlobalUnlock(handle);
    CloseClipboard();
    return 0;
}