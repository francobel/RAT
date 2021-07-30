#include "intel.h"

#define DIV 10737418

void getUserInfo()
{
	TCHAR tchBuffer[256];
	DWORD dwBufferSize = _tcslen(tchBuffer);

	GetComputerName(tchBuffer, &dwBufferSize);
	_tprintf(_T("Computer name:   %s\n"), tchBuffer);

	GetUserName(tchBuffer, &dwBufferSize);
	_tprintf(_T("Username:        %s\n\n"), tchBuffer);

	return 0;
}

void getMemoryUsage()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	double totalMem  = (statex.ullTotalPhys / DIV);
	double usedMem   = (statex.ullTotalPhys / DIV) - (statex.ullAvailPhys / DIV);
	double totalPage = (statex.ullTotalPageFile / DIV);
	double usedPage  = (statex.ullTotalPageFile / DIV) - (statex.ullAvailPageFile / DIV);
	double totalVMem = (statex.ullTotalVirtual  / DIV);
	double usedVMem  = (statex.ullTotalVirtual  / DIV) - (statex.ullAvailVirtual / DIV);

	_tprintf(_T("Memory Usage:    %*ld%% GB\n"), 1, statex.dwMemoryLoad);
	_tprintf(_T("Physical Memory: %.2f/%.2f GB\n"), usedMem / 100, totalMem / 100);
	_tprintf(_T("Paging File:     %.2f/%.2f GB\n"), usedPage / 100, totalPage / 100);
	_tprintf(_T("Virtual Memory:  %.2f/%.2f GB\n"), usedVMem / 100, totalVMem / 100);
	_tprintf(_T("Extended Memory: %*I64d GB \n\n"), 1, statex.ullAvailExtendedVirtual / DIV);
}

void getSystemInfo()
{
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);

	_tprintf(_T("OEM ID:          %u\n"), siSysInfo.dwOemId);
	_tprintf(_T("# of processors: %u\n"), siSysInfo.dwNumberOfProcessors);
	_tprintf(_T("Page size:       %u\n"), siSysInfo.dwPageSize);
	_tprintf(_T("Processor type:  %u\n"), siSysInfo.dwProcessorType);
	_tprintf(_T("Min app address: %lx\n"), siSysInfo.lpMinimumApplicationAddress);
	_tprintf(_T("Max app address: %lx\n"), siSysInfo.lpMaximumApplicationAddress);
	_tprintf(_T("Active processor mask: %u\n\n"), siSysInfo.dwActiveProcessorMask);
}