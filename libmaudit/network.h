#ifndef __MAUDIT_NETWORK_H
#define __MAUDIT_NETWORK_H

// Fixes for supporting broken OS's like MS Windows.

#ifdef _WIN32

#include <winsock2.h>

#define SHUT_RDWR SD_BOTH
#define MSG_NOSIGNAL 0
#define SOL_TCP IPPROTO_TCP

#define RECV_TYPE_CAST (char*)
#define SETSOCKOPT_TYPE_CAST (const char*)

void NETWORK_INIT() {
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
        throw std::runtime_error("Could not WSAStartup()");
}

void NETWORK_STOP() {
    WSACleanup();
}

#define CLOSE closesocket

#else

#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

#define RECV_TYPE_CAST 
#define SETSOCKOPT_TYPE_CAST

void NETWORK_INIT() {}
void NETWORK_STOP() {}

#define CLOSE close

#endif


#endif


