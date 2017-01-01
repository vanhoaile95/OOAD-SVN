#include "ServerManager.h"
#include "ServerTimeManager.h"
#include "Helper.h"
#include "StringHelper.h"

ServerManager* ServerManager::_instance = 0;

ServerManager* ServerManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new ServerManager();
	}
	return _instance;
}
ServerManager::ServerManager()
{
	State = ServerState::INIT;
}
ServerManager::~ServerManager()
{

}

int ServerManager::ServerInit()
{
	listServer = new list<Server*>();

	State = ServerState::INIT;
	// WSAStartup
	if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		printf("WSAStartup() failed with error %d\n", Ret);
		WSACleanup();
		State = ServerState::INIT_FAILED;
		return 1;
	}
	else
		printf("WSAStartup() is fine!\n");

	// Prepare a socket to listen for connections
	if ((ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("WSASocket() failed with error %d\n", WSAGetLastError());
		State = ServerState::INIT_FAILED;
		return 1;
	}
	else
		printf("WSASocket() is OK!\n");

	InternetAddr.sin_family = AF_INET;
	inet_pton(AF_INET, ConfigsManager::Instance()->GetStringConfig(ConfigName::SERVER_IP).c_str(), &InternetAddr.sin_addr);
	InternetAddr.sin_port = htons(ConfigsManager::Instance()->GetIntConfig(ConfigName::SERVER_PORT));

	if (bind(ListenSocket, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		State = ServerState::INIT_FAILED;
		return 1;
	}
	else
		printf("bind() is OK!\n");

	if (listen(ListenSocket, 5))
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		State = ServerState::INIT_FAILED;
		return 1;
	}
	else
		printf("listen() is OK!\n");

	// Change the socket mode on the listening socket from blocking to
	// non-block so the application will not block waiting for requests
	NonBlock = 1;
	if (ioctlsocket(ListenSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
	{
		printf("ioctlsocket() failed with error %d\n", WSAGetLastError());
		State = ServerState::INIT_FAILED;
		return 1;
	}
	else
		printf("ioctlsocket() is OK!\n");
	return 0;
}
int ServerManager::ServerRun()
{
	if(State >= 0) State = ServerState::RUNNING;
	while (State >= 0)
	{
		//if (ServerTimeManager::Instance()->RecvFrameCount > ConfigsManager::Instance()->GetIntConfig(ConfigName::CLIENT_STEP))
		{
			ServerTimeManager::Instance()->RecvFrameCount = 0;

			SelectClient();
			if (State < 0)
				return 1;
			// Check each socket for Read and Write notification until the number
			// of sockets in Total is satisfied
			for (i = 0; Total > 0 && i < TotalSockets; i++)
			{
				LPSOCKET_INFORMATION SocketInfo = SocketArray[i];

				if (ServerReceive(SocketInfo) < 0)
					continue;
				//if (ServerExecute(SocketInfo) < 0)
				//	continue;
				ServerResponse(SocketInfo);
			}
		}
		//ServerTimeManager::Instance()->ThreadSleep(1);
	}
	return 0;
}
int ServerManager::SelectClient()
{
	// Prepare the Read and Write socket sets for network I/O notification
	FD_ZERO(&ReadSet);
	FD_ZERO(&WriteSet);
	// Always look for connection attempts
	FD_SET(ListenSocket, &ReadSet);
	// Set Read and Write notification for each socket based on the
	// current state the buffer.  If there is data remaining in the
	// buffer then set the Write set otherwise the Read set
	for (i = 0; i < TotalSockets; i++)
	if (SocketArray[i]->BytesRECV > SocketArray[i]->BytesSEND)
		FD_SET(SocketArray[i]->Socket, &WriteSet);
	else
		FD_SET(SocketArray[i]->Socket, &ReadSet);
	DWORD x = ServerTimeManager::Instance()->GetServerTime();
	if ((Total = select(0, &ReadSet, &WriteSet, NULL, NULL)) == SOCKET_ERROR)
	{
		printf("select() returned with error %d\n", WSAGetLastError());
		State = ServerState::ON_ERROR;
		return 1;
	}
	else
		printf("select() is OK! \n");
	DWORD y = ServerTimeManager::Instance()->GetServerTime();
	// Check for arriving connections on the listening socket.
	if (FD_ISSET(ListenSocket, &ReadSet))
	{
		if ((AcceptSocket = accept(ListenSocket, NULL, NULL)) != INVALID_SOCKET)
		{
			// Set the accepted socket to non-blocking mode so the server will
			// not get caught in a blocked condition on WSASends
			NonBlock = 1;
			if (ioctlsocket(AcceptSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
			{
				printf("ioctlsocket(FIONBIO) failed with error %d\n", WSAGetLastError());
				State = ServerState::ON_ERROR;
				return 1;
			}
			else
				printf("ioctlsocket(FIONBIO) is OK!\n");

			if (CreateSocketInformation(AcceptSocket) == FALSE)
			{
				printf("CreateSocketInformation(AcceptSocket) failed!\n");
				State = ServerState::ON_ERROR;
				return 1;
			}
			else
				printf("CreateSocketInformation() is OK!\n");

		}
		else
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("accept() failed with error %d\n", WSAGetLastError());
				State = ServerState::ON_ERROR;
				return 1;
			}
			else
				printf("accept() is fine!\n");
		}
	}
	return 0;
}
ServerExecutingState ServerManager::ServerReceive(LPSOCKET_INFORMATION SocketInfo)
{
	// If the ReadSet is marked for this socket then this means data
	// is available to be read on the socket
	if (FD_ISSET(SocketInfo->Socket, &ReadSet))
	{
		SocketInfo->DataBuf.buf = SocketInfo->Buffer;
		SocketInfo->DataBuf.len = DATA_BUFSIZE;

		Flags = 0;
		if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("WSARecv() failed with error %d\n", WSAGetLastError());
				FreeSocketInformation(i);
			}
			else
			{
				printf("WSARecv() is OK!\n");
			}
			return ServerExecutingState::SOCKET_PROBLEM;
		}
		else
		{
			SocketInfo->BytesRECV = RecvBytes;

			GetRecvInfo(SocketInfo);
		}
	}
	return ServerExecutingState::NORMAL;
}
ServerExecutingState ServerManager::GetRecvInfo(LPSOCKET_INFORMATION SocketInfo)
{
	// If zero bytes are received, this indicates the peer closed the connection.
	try
	{
		if (RecvBytes == 0)
		{
			SocketInfo->SID = -1;
			SocketInfo->UID = -1;
			FreeSocketInformation(i);
			return ServerExecutingState::CLOSE_SOCKET;
		}
		else if (SocketInfo->UID > 0)
		{
			Client* client = ClientManager::Instance()->GetClient(SocketInfo->UID);
			ServerDataManager::Instance()->PushBack(SocketInfo->DataBuf.buf, SocketInfo->BytesRECV);

			return ServerExecutingState::NORMAL;
		}
		else
		{
			vector<string> decode = StringHelper::split(SocketInfo->Buffer, ",");
			if (Helper::Equals(Helper::GetString(decode, 0), "CreateGame"))
			{
				Server* server = AddNewServer();
				Client* client = ClientManager::Instance()->AddNewPlayer(SocketInfo->Buffer, server->SID);
				SocketInfo->UID = client->UID;
				//client->Execute();
				printf("CreateGame:OK; UID:%d SID:%d\n", SocketInfo->UID, server->SID);
			}
			else if (Helper::Equals(Helper::GetString(decode, 0), "JoinGameMode"))
			{
				Client* client = ClientManager::Instance()->AddNewPlayer(SocketInfo->Buffer);
				SocketInfo->UID = client->UID;
				client->Execute();
				printf("JoinGameMode:OK; UID:%d\n", SocketInfo->UID);
			}
		}
		SocketInfo->Buffer[0] = '\0';
		SocketInfo->DataBuf.buf[0] = '\0';
		SocketInfo->DataBuf.len = 0;
		//SocketInfo->Buffer = "";
		return ServerExecutingState::NORMAL;
	}
	catch (const std::exception&)
	{
		printf("Error!!");
	}
	return ServerExecutingState::NORMAL;
}
ServerExecutingState ServerManager::ServerExecute()
{
	for (list<Server*>::iterator i = listServer->begin(); i != listServer->end(); i++)
	{
		(*i)->Execute();
	}
	return ServerExecutingState::NORMAL;
}
ServerExecutingState ServerManager::ServerResponse(LPSOCKET_INFORMATION SocketInfo)
{
	Client* Client = ClientManager::Instance()->GetClient(SocketInfo->UID);
	string dataSend = Client->GetSendData();
	if (!dataSend.compare(""))
		return ServerExecutingState::NORMAL;

	if (FD_ISSET(SocketInfo->Socket, &WriteSet))
	{
		Client->PopSendData();


		CHAR* MSG = Helper::GetCharFromString(dataSend);
		SocketInfo->DataBuf.buf = MSG;
		SocketInfo->DataBuf.len = Helper::GetULONGFromInt(dataSend.length());

		if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("WSASend() failed with error %d\n", WSAGetLastError());
				FreeSocketInformation(i);
			}
			else
				printf("WSASend() is OK!\n");

			return ServerExecutingState::SOCKET_PROBLEM;
		}
		else
		{
			//Cần bổ xung code kiểm tra receive và send
			//SocketInfo->BytesSEND += SendBytes;
			//if (SocketInfo->BytesSEND == SocketInfo->BytesRECV)
			//{
			//	SocketInfo->BytesSEND = 0;
			//	SocketInfo->BytesRECV = 0;
			//}
			SocketInfo->BytesSEND = 0;
			SocketInfo->BytesRECV = 0;
		}
	}
	return ServerExecutingState::NORMAL;
}
int ServerManager::ServerEnd()
{
	State = ServerState::STOP;
	return 0;
}
BOOL ServerManager::CreateSocketInformation(SOCKET s)
{
	LPSOCKET_INFORMATION SI;
	printf("Accepted socket number %d\n", s);
	if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
	{
		printf("GlobalAlloc() failed with error %d\n", GetLastError());
		return FALSE;
	}
	else
		printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");
	// Prepare SocketInfo structure for use
	SI->Socket = s;
	SI->BytesSEND = 0;
	SI->BytesRECV = 0;

	SocketArray[TotalSockets] = SI;
	TotalSockets++;
	return(TRUE);
}
void ServerManager::FreeSocketInformation(DWORD Index)
{
	LPSOCKET_INFORMATION SI = SocketArray[Index];
	DWORD i;

	closesocket(SI->Socket);
	printf("Closing socket number %d\n", SI->Socket);
	GlobalFree(SI);

	// Squash the socket array
	for (i = Index; i < TotalSockets; i++)
	{
		SocketArray[i] = SocketArray[i + 1];
	}
	TotalSockets--;
}

Server* ServerManager::AddNewServer()
{
	Server* server = new Server();
	listServer->push_back(server);
	server->Init(nextSIDIndex);
	nextSIDIndex++;
	return server;
}
Server* ServerManager::GetServer(int sid)
{
	for (list<Server*>::iterator i = listServer->begin(); i != listServer->end(); i++)
	{
		if((*i)->SID == sid)
			return *i;
	}
	return NULL;
}
void ServerManager::OffServer(int sid)
{
	for (list<Server*>::iterator i = listServer->begin(); i != listServer->end(); i++)
	{
		if ((*i)->SID == sid)
		{
			(*i)->End();
			listServer->remove(*i);
		}
	}
}
Server* ServerManager::GetWaitingServer()
{
	for (list<Server*>::iterator i = listServer->begin(); i != listServer->end(); i++)
	{
		if ((*i)->State == ServerState::WAITING)
		{
			return (*i);
		}
	}
	return AddNewServer();
}
