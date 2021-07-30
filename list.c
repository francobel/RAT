#include "list.h"

int list()
{
	TCHAR buff[MAX_PATH];
	TCHAR* input[MAX_PATH], recursive[2], files[2];
	int pathIndex = 0;

	_tprintf(TEXT("List from (Path): "));
	_getts_s(input, MAX_PATH);

	_tprintf(TEXT("Recursive? (Y/N): "));
	_getts_s(recursive, 2);

	_tprintf(TEXT("List files? (Y/N): "));
	_getts_s(files, 2);

	_tprintf(TEXT("\n"));

	ExpandEnvironmentStrings(input, buff, MAX_PATH);

	listDir(buff, files, recursive, -1);

	_tprintf(TEXT("\n"));

	return 0;
}

int listDir(STRSAFE_LPCWSTR path, STRSAFE_LPCWSTR files, STRSAFE_LPCWSTR recursive, int level)
{
	TCHAR pathArr[MAX_PATH];
	TCHAR buff[MAX_PATH];
	WIN32_FIND_DATA findData;
	HANDLE findHandle = INVALID_HANDLE_VALUE;
	level++;

	StringCchCopy(pathArr, MAX_PATH, path);
	StringCchCat(pathArr, MAX_PATH, TEXT("\\*"));

	findHandle = FindFirstFile(pathArr, &findData);

	do {
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (_tcscmp(findData.cFileName, TEXT(".")) && _tcscmp(findData.cFileName, TEXT("..")))
			{
				for (int i = 0; i < level; i++)
					_tprintf(TEXT("\t"));

				_tprintf(TEXT("%s - [Dir]\n"), findData.cFileName);

				StringCchCopy(buff, MAX_PATH, path);
				StringCchCat(buff, MAX_PATH, TEXT("\\"));
				StringCchCat(buff, MAX_PATH, findData.cFileName);

				if (!_tcscmp(recursive, TEXT("Y")) || !_tcscmp(recursive, TEXT("y")))
					listDir(buff, files, recursive, level);
			}
		}
		else if (!_tcscmp(files, TEXT("Y")) || !_tcscmp(files, TEXT("y")))
		{
			for (int i = 0; i < level; i++) _tprintf(TEXT("\t"));
			_tprintf(TEXT("%s \n"), findData.cFileName);
		}

	} while (FindNextFile(findHandle, &findData) != 0);

	FindClose(findHandle);

	return 0;
}