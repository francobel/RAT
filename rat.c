#include "config.h"

int _tmain()
{
	while (1)
	{
		_tprintf(_T("MENU:\n 1. Intel\n 2. Keylogger\n 3. List\n 4. Clipboard\n 5. Screenshot\n 6. Quit\n\n"));

		TCHAR input[2];

		_tprintf(_T("User input: "));
		_getts_s(input, 2);
		_tprintf(_T("\n"));

		if (!strcmp(input, "1"))
		{
			getIntel();
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
		else if (!strcmp(input, "5"))
		{
			screenshot();
		}
		else
		{
			exit(0);
		}
	}
}