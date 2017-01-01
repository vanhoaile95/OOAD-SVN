#define SERVER_MANAGER
#ifdef SERVER_MANAGER
#pragma once

#include <winsock2.h>
#include <stdio.h>
#include <ws2tcpip.h>
#include "ClientManager.h"
#include "ConfigsManager.h"
#include "Server.h"
#include "ServerDataManager.h"


typedef struct _SOCKET_INFORMATION {
	CHAR Buffer[DATA_BUFSIZE];
	int UID = -1;
	int SID = -1;
	WSABUF DataBuf;
	SOCKET Socket;
	OVERLAPPED Overlapped;
	DWORD BytesSEND;
	DWORD BytesRECV;
} SOCKET_INFORMATION, *LPSOCKET_INFORMATION; 


enum ServerExecutingState
{
	NORMAL = 200,
	SOCKET_PROBLEM = -1,
	CLOSE_SOCKET = -10,
};
enum ClientMethod
{
	AUTHENTICATE = 0,

};

using namespace std;
class ServerManager
{
private:
	static ServerManager *_instance;
	ServerManager();
	~ServerManager();

	SOCKET ListenSocket;
	SOCKET AcceptSocket;
	SOCKADDR_IN InternetAddr;
	WSADATA wsaData;
	INT Ret;
	FD_SET WriteSet;
	FD_SET ReadSet;
	DWORD i;
	DWORD Total;
	ULONG NonBlock;
	DWORD Flags;
	DWORD SendBytes;
	DWORD RecvBytes;
	DWORD TotalSockets = 0;
	
public:
	ServerState State;
	list<Server*>* listServer;
	int nextSIDIndex = 1;
	int ClientExecuting;
	static ServerManager* Instance();


	// Global var
	LPSOCKET_INFORMATION SocketArray[FD_SETSIZE];

	// Prototypes
	BOOL CreateSocketInformation(SOCKET s);
	void FreeSocketInformation(DWORD Index);


	int ServerInit();
	int ServerRun();
	int ServerEnd();
	void OffServer(int sid);

	int SelectClient();
	ServerExecutingState ServerReceive(LPSOCKET_INFORMATION SocketInfo);
	ServerExecutingState ServerResponse(LPSOCKET_INFORMATION SocketInfo);

	ServerExecutingState ServerExecute();

	ServerExecutingState GetRecvInfo(LPSOCKET_INFORMATION SocketInfo);
	Server * GetServer(int sid);
	Server * GetWaitingServer();
	Server* AddNewServer();
};

#endif // SERVER_MANAGER