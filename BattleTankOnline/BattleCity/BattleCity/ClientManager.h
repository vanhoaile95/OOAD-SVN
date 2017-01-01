#define CLIENT_MANAGER
#ifdef CLIENT_MANAGER
#pragma once
#include "Helper.h"
#include "ConfigsManager.h"
#include "ServerInfo.h"
#include <winsock2.h>

#define DEFAULT_PORT        443
#define DEFAULT_BUFFER      2048

enum ClientState{
	SERVER_NOT_FOUND = -2,
	ONERROR = -1,
	INIT,
	RUN,
	SENDING,
	SENDFAILDED,
	RECEIVING,
	RECVFAILDED,
	END,
};




using namespace std;
class ClientManager
{
private:
	static ClientManager *_instance;
	ClientManager();
	~ClientManager();


	char  szServer[128],
		szMessage[2048];         
	int   iPort = DEFAULT_PORT;				       


	WSADATA       wsd;
	SOCKET        sClient;
	char          szBuffer[DEFAULT_BUFFER];
	int           ret, i;
	struct sockaddr_in server;
	struct hostent    *host = NULL;


	int State;
public:
	int UID;
	int SID;
	int TankIndex;
	int MaxTank;
	int MaxClient;
	int Ping;
	bool Offline;


	list<string>  *DataSend, *DataRecv;
	ClientInf * ClientInfo[4];
	//list<string> ControllData;
public:


	static ClientManager* Instance();
	int Init();

	int SendLoop();
	int RecvLoop();

	int End();

	string GetSendData();
	bool Received();
	bool CanSend();

	int SendData(string data);
	int RecvData();


	void SEND_CreateGame();
	string RECV_CreateGame(int *uid = NULL, int *sid = NULL);

	void SEND_JoinGame();
	string RECV_JoinGame(list<ServerInf>* serverinfo,int *uid = NULL, int *sid = NULL);

	void SEND_JoinServer(int sid);
	string RECV_JoinServer(ClientInf * clientInfo []);

	void SEND_PING_WaitingForClient(int sid);
	string RECV_PING_WaitingForClient(ClientInf * clientInfo [], bool * start = NULL);

	void SEND_StartGame(int sid);
	string RECV_StartGame(ClientInf * clientInfo []);

	void SEND_PING_UpdateGameLogic();
	string RECV_PING_UpdateGameLogic(string* updateinf);

	void SEND_Controll(string command);
	string RECV_Controll(int * ping = NULL, int * tankid = NULL);
};
#endif // CLIENT_MANAGER


