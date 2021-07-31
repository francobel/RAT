//https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-send
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996) 

#define DEFAULT_BUFLEN 1024

void phoneHome(char* x) 
{
    // Declare and initialize variables.
    int result;
    WSADATA wsaData;

    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in clientService;

    int recvbuflen = DEFAULT_BUFLEN;
    char* sendbuf = x;
    char recvbuf[DEFAULT_BUFLEN] = "";

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != NO_ERROR) 
    {
        _tprintf(L"WSAStartup failed with error: %d\n", result);
        return 1;
    }

    // Create a SOCKET for connecting to server
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) 
    {
        _tprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
      
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(500);

    // Connect to server.
    result = connect(sock, (SOCKADDR*)&clientService, sizeof(clientService));
    if (result == SOCKET_ERROR) 
    {
        _tprintf(L"connect failed with error: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    result = send(sock, sendbuf, (int)strlen(sendbuf), 0);
    if (result == SOCKET_ERROR) 
    {
        _tprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    //printf("Bytes Sent: %d\n", result);

    // shutdown the connection since no more data will be sent
    result = shutdown(sock, SD_SEND);
    if (result == SOCKET_ERROR) 
    {
        _tprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
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
            _tprintf(L"Bytes received: %d\n", result);
            printf("%s", recvbuf);
        }
        else if (result == 0)
            _tprintf(L"Connection closed\n");
        else
            _tprintf(L"recv failed with error: %d\n", WSAGetLastError());

    } while (result > 0);

    // close the socket
    result = closesocket(sock);
    if (result == SOCKET_ERROR) {
        _tprintf(L"close failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();
    return 0;
}