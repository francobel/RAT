#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996) 

void sendHome(char* sendPtr) 
{
    int result;
    WSADATA wsaData;
    struct sockaddr_in clientService;

    SOCKET sock = INVALID_SOCKET;
    int recvbuflen = 1024;
    char recvbuf[1024] = "";

    const char* victimIP = "127.0.0.1";
    u_short victimPort = 500;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != NO_ERROR) 
    {
        _tprintf(_T("WSAStartup failed with error: %d\n"), result);
        return 1;
    }

    // Create a SOCKET for connecting to server
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) 
    {
        _tprintf(_T("socket failed with error: %ld\n"), WSAGetLastError());
        WSACleanup();
        return 1;
    }
      
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(victimIP);
    clientService.sin_port = htons(victimPort);

    // Connect to server.
    result = connect(sock, (SOCKADDR*)&clientService, sizeof(clientService));
    if (result == SOCKET_ERROR) 
    {
        _tprintf(_T("connect failed with error: %d\n"), WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    result = send(sock, sendPtr, (int)strlen(sendPtr), 0);
    if (result == SOCKET_ERROR) 
    {
        _tprintf(_T("send failed with error: %d\n"), WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // shutdown the connection since no more data will be sent
    result = shutdown(sock, SD_SEND);
    if (result == SOCKET_ERROR) 
    {
        _tprintf(_T("shutdown failed with error: %d\n"), WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do 
    {
        result = recv(sock, recvbuf, recvbuflen, 0);
        if (result > 0)
        {
            _tprintf(_T("Bytes received: %d\n"), result);
            printf("%s", recvbuf);
        }
        else if (result == 0)
            _tprintf(_T("Connection closed\n"));
        else
            _tprintf(_T("recv failed with error: %d\n"), WSAGetLastError());

    } while (result > 0);

    // close the socket
    result = closesocket(sock);
    if (result == SOCKET_ERROR) {
        _tprintf(_T("close failed with error: %d\n"), WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();
    return 0;
}