#include "ClientManager.h"
#include <WS2tcpip.h>
#include "ClientTimeManager.h"
#include "GameInfor.h"

ClientManager* ClientManager::_instance = 0;


ClientManager* ClientManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new ClientManager();
	}
	return _instance;
}
ClientManager::ClientManager()
{
	State = ClientState::INIT;
	MaxTank = ConfigsManager::Instance()->GetIntConfig(ConfigName::MAX_TANK_IN_GAME);
	MaxClient = ConfigsManager::Instance()->GetIntConfig(ConfigName::MAX_CLIENT_IN_GAME);
	DataSend = new list<string>();
	DataRecv = new list<string>();
	Ping = 0;
	Offline = true;
}
ClientManager::~ClientManager()
{
	
}
int ClientManager::Init()
{
	DataSend->clear();
	DataRecv->clear();

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("Failed to load Winsock library! Error %d\n", WSAGetLastError());
		State = ClientState::ONERROR;
		return 1;
	}
	else printf("Winsock library loaded successfully!\n");

	//strcpy_s(szMessage, sizeof(szMessage),SEND_CreateGame());

	// Create the socket, and attempt to connect to the server
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		printf("socket() failed with error code %d\n", WSAGetLastError());
		State = ClientState::ONERROR;
		return 1;
	}
	else printf("socket() looks fine!\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(iPort);
	inet_pton(AF_INET, ConfigsManager::Instance()->GetStringConfig(ConfigName::SERVER_IP).c_str(), &server.sin_addr);

	// If the supplied server address wasn't in the form
	// "aaa.bbb.ccc.ddd" it's a hostname, so try to resolve it
	if (server.sin_addr.s_addr == INADDR_NONE)
	{
		host = gethostbyname(szServer);
		if (host == NULL)
		{
			printf("Unable to resolve server %s\n", szServer);
			State = ClientState::ONERROR;
			return 1;
		}
		else
			printf("The hostname resolved successfully!\n");

		CopyMemory(&server.sin_addr, host->h_addr_list[0], host->h_length);
	}

	if (connect(sClient, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("connect() failed with error code %d\n", WSAGetLastError());
		State = ClientState::SERVER_NOT_FOUND;
		return 1;
	}
	else
		printf("connect() is pretty damn fine!\n");
	
	return 0;
}
int ClientManager::SendLoop()
{
	_instance->State = ClientState::RUN;
	while (_instance->State != ClientState::SERVER_NOT_FOUND
		&& _instance->State != ClientState::ONERROR
		&& _instance->State != ClientState::END)
	{
		if (ClientTimeManager::Instance()->SendFrameCount > ConfigsManager::Instance()->GetIntConfig(ConfigName::CLIENT_STEP))
		{
			ClientTimeManager::Instance()->SendFrameCount = 0;
			if (CanSend())
			{
				string sendmsg = *DataSend->begin();
				SendData(sendmsg);
				DataSend->pop_front();
			}
		}
		else 
		{
			ClientTimeManager::Instance()->ClientSleep(1);
		}
	}
	return 0;
}
int ClientManager::RecvLoop()
{
	while (_instance->State != ClientState::SERVER_NOT_FOUND
		&& _instance->State != ClientState::ONERROR
		&& _instance->State != ClientState::END)
	{
		if (ClientTimeManager::Instance()->RecvFrameCount > ConfigsManager::Instance()->GetIntConfig(ConfigName::CLIENT_STEP))
		{
			ClientTimeManager::Instance()->RecvFrameCount = 0;
			if (_instance->State == ClientState::RUN)
				RecvData();
			
		}
		else
		{
			ClientTimeManager::Instance()->ClientSleep(1);
		}
	}
	return 0;
}

int ClientManager::SendData(string data)
{
	if (data[0] == '1')
	{
		vector<string> decode = StringHelper::split(data, ",");
		//string msg = "1METHOD:Controll,UID:#uid,CLIENTTIME:#ctime,COMMAND:#command$";
		DWORD time = Helper::GetDWORD(decode,2);
		Ping = (int) (ClientTimeManager::Instance()->GetClientCurrentTime() - time);
		int js = 0;
	}
	int length = data.length();
	ret = send(sClient, data.c_str(), length, 0);
	if (ret == 0)
		return 1;
	else if (ret == SOCKET_ERROR)
	{
		printf("send() failed with error code %d\n", WSAGetLastError());
		return 1;
	}
	printf("SEND: %s\n", data.c_str());
	return 0;
}
int ClientManager::RecvData()
{
	if (_instance->State != ClientState::RUN) return 0;
	ret = recv(_instance->sClient, szBuffer, DEFAULT_BUFFER, 0);
	if (ret == 0)        //Graceful close
	{
		_instance->State = ClientState::RECVFAILDED;
		printf("It is a graceful close!\n");
		return 1;
	}
	else if (ret == SOCKET_ERROR)
	{
		_instance->State = ClientState::ONERROR;
		printf("recv() failed with error code %d\n", WSAGetLastError());
		return 1;
	}
	szBuffer[ret] = '\0';
	string data = szBuffer;
	printf("RECV: %s\n", szBuffer);
	vector<string> listRECV = StringHelper::split(data, "$");
	
	for (int i = 0; i < listRECV.size(); i++)
	{
		DataRecv->push_back(listRECV[i]);
		//if (i > 0)
		//	int jas = 3;
	}

	szBuffer[0] = '\0';
	return 0;
}

int ClientManager::End()
{
	_instance->State = ClientState::END;
	if (closesocket(sClient) == 0)
		printf("closesocket() is OK!\n");
	else
		printf("closesocket() failed with error code %d\n", WSAGetLastError());

	if (WSACleanup() == 0)
		printf("WSACleanup() is fine!\n");
	else
		printf("WSACleanup() failed with error code %d\n", WSAGetLastError());
	return 0;
}
// Encode Decode Function
void ClientManager::SEND_CreateGame()
{
	if (Offline) return;
	string msg = "METHOD:CreateGame,UID:-1,CLIENTTIME:#ctime$";
	Helper::Replace(msg, "#ctime", to_string(ClientTimeManager::Instance()->GetClientCurrentTime()));
	DataSend->push_back(msg);
}
string ClientManager::RECV_CreateGame(int *uid, int *sid)
{
	string response = "Wait";
	if (DataRecv->begin() == DataRecv->end())
		return response;
	string data = *DataRecv->begin();
	vector<string> decode = StringHelper::split(data, ",");
	if (Helper::Equals(Helper::GetString(decode, 0), "CreateGame"))
	{
		int code = Helper::GetInt(decode, 1);
		if (code == 200)
		{
			UID = Helper::GetInt(decode, 2);
			SID = Helper::GetInt(decode, 4);
			if (uid != NULL && sid != NULL)
			{
				*uid = UID;
				*sid = SID;
			}
			response = "CreateGame:OK";
		}
		DataRecv->pop_front();
	}
	return response;
}


void ClientManager::SEND_JoinGame()
{
	if (Offline) return;
	string msg = "METHOD:JoinGameMode,UID:#uid,CLIENTTIME:#ctime$";
	Helper::Replace(msg, "#uid", to_string(UID));
	Helper::Replace(msg, "#ctime", to_string(ClientTimeManager::Instance()->GetClientCurrentTime()));
	DataSend->push_back(msg);
}
string ClientManager::RECV_JoinGame(list<ServerInf>* serverinfo, int * uid,int *sid)
{
	serverinfo->clear();
	string response = "Wait";
	if (DataRecv->begin() == DataRecv->end())
		return response;
	string data = *DataRecv->begin();
	vector<string> decode = StringHelper::split(data, ",");
	if (Helper::Equals(Helper::GetString(decode, 0), "JoinGameMode"))
	{
		//string msg = "METHOD:JoinGameMode,CODE:#code,UID:#uid,SERVERTIME:#server_time,SID:#sid,SERVERLIST:#server_list";
		int code = Helper::GetInt(decode, 1);
		if (code == 200)
		{
			UID = Helper::GetInt(decode, 2);
			SID = Helper::GetInt(decode, 4);
			if (uid != NULL && sid != NULL)
			{
				*uid = UID;
				*sid = SID;
			}
			if (SID == -1)
			{
				vector<string> decodeSVList = StringHelper::split(Helper::GetString(decode, 5), "|");
				int i = 0;
				while (!Helper::Equals(decodeSVList[i], "-1"))
				{
					int sid = Helper::GetIntFromString(decodeSVList[i]);
					int hostid = Helper::GetIntFromString(decodeSVList[i + 1]);
					int mapid = Helper::GetIntFromString(decodeSVList[i + 2]);

					ServerInf inf = ServerInf(sid, hostid, mapid);
					i += 3;
					serverinfo->push_back(inf);
				}
			}
			response = "JoinGameMode:OK";
		}
		DataRecv->pop_front();
	}

	return response;
}


void ClientManager::SEND_JoinServer(int sid)
{
	if (Offline) return;
	string msg = "0METHOD:JoinServer,UID:#uid,CLIENTTIME:#ctime,SID:#sid$";
	Helper::Replace(msg, "#sid", to_string(sid));
	Helper::Replace(msg, "#uid", to_string(UID));
	Helper::Replace(msg, "#ctime", to_string(ClientTimeManager::Instance()->GetClientCurrentTime()));
	DataSend->push_back(msg);
}
string ClientManager::RECV_JoinServer(ClientInf * clientInfo [])
{
	string response = "Wait";
	if (DataRecv->begin() == DataRecv->end())
		return response;
	string data = *DataRecv->begin();
	vector<string> decode = StringHelper::split(data, ",");
	if (Helper::Equals(Helper::GetString(decode, 0), "JoinServer"))
	{
		//string msg = "METHOD:JoinServer,CODE:#code,UID:#uid,SERVERTIME:#server_time,CLIENTLIST:#client_list$";
		vector<string> decodeclientList = StringHelper::split(Helper::GetString(decode, 4), "|");
		for (int i = 0; i < MaxClient; i++)
		{
			clientInfo[i] = new ClientInf(Helper::GetIntFromString(decodeclientList[i]), i);
		}
		response = "JoinServer:OK";
		DataRecv->pop_front();
	}

	return response;
}

void ClientManager::SEND_PING_WaitingForClient(int sid)
{
	if (Offline) return;
	string msg = "0METHOD:PING_WaitingForClient,UID:#uid,CLIENTTIME:#ctime,SID:#sid$";
	Helper::Replace(msg, "#sid", to_string(sid));
	Helper::Replace(msg, "#uid", to_string(UID));
	Helper::Replace(msg, "#ctime", to_string(ClientTimeManager::Instance()->GetClientCurrentTime()));
	DataSend->push_back(msg);
}
string ClientManager::RECV_PING_WaitingForClient(ClientInf * clientInfo [],bool *start)
{
	string response = "Wait";
	if (DataRecv->begin() == DataRecv->end())
		return response;
	string data = *DataRecv->begin();
	vector<string> decode = StringHelper::split(data, ",");
	if (Helper::Equals(Helper::GetString(decode, 0), "PING_WaitingForClient"))
	{
		//string msg = "METHOD:PING_WaitingForClient,CODE:#code,UID:#uid,SERVERTIME:#server_time,CLIENTLIST:#client_list,START:#start$";
		string check = Helper::GetString(decode, 5);
		if (check == "true")
		{
			*start = true;
		}
		else *start = false;
		vector<string> decodeclientList = StringHelper::split(Helper::GetString(decode, 4), "|");
		for (int i = 0; i < MaxClient; i++)
		{
			int uid = Helper::GetIntFromString(decodeclientList[i]);
			clientInfo[i] = new ClientInf(uid, i);

			if (uid == UID) TankIndex = i;
			if (*start == true)
			{
				GameScore::Instance()->MulTiplayerInfo[i]->UID = uid;
				ClientInfo[i] = clientInfo[i];
			}
		}
		response = "PING_WaitingForClient:OK";
		DataRecv->pop_front();
	}
	return response;
}

void ClientManager::SEND_StartGame(int sid)
{
	if (Offline) return;
	string msg = "0METHOD:StartGame,UID:#uid,CLIENTTIME:#ctime,SID:#sid$";
	Helper::Replace(msg, "#sid", to_string(sid));
	Helper::Replace(msg, "#uid", to_string(UID));
	Helper::Replace(msg, "#ctime", to_string(ClientTimeManager::Instance()->GetClientCurrentTime()));
	DataSend->push_back(msg);
}
string ClientManager::RECV_StartGame(ClientInf * clientInfo [])
{
	string response = "Wait";
	if (DataRecv->begin() == DataRecv->end())
		return response;
	string data = *DataRecv->begin();
	vector<string> decode = StringHelper::split(data, ",");
	if (Helper::Equals(Helper::GetString(decode, 0), "StartGame"))
	{


		vector<string> decodeclientList = StringHelper::split(Helper::GetString(decode, 4), "|");
		for (int i = 0; i < MaxClient; i++)
		{
			int uid = Helper::GetIntFromString(decodeclientList[i]);
			clientInfo[i] = new ClientInf(uid, i);
			ClientInfo[i] = clientInfo[i];
			if (uid == UID) TankIndex = i;
		}
		response = "StartGame:OK";
		DataRecv->pop_front();
	}
	else if (Helper::Equals(Helper::GetString(decode, 0), "PING_WaitingForClient"))
	{
		DataRecv->pop_front();
		/*string check = Helper::GetString(decode, 5);
		if (check == "true")
		{
			vector<string> decodeclientList = StringHelper::split(Helper::GetString(decode, 4), "|");
			for (int i = 0; i < MaxTank; i++)
			{
				int uid = Helper::GetIntFromString(decodeclientList[i]);
				clientInfo[i] = new ClientInf(uid, i);
				if (uid == UID) TankIndex = i;
			}
			response = "StartGame:OK";
		}
		else
		{
			DataRecv->pop_front();
		}*/
	}
	//PopFront If not StartGameData

	return response;
}

void ClientManager::SEND_PING_UpdateGameLogic()
{
	if (Offline) return;
	string msg = "0METHOD:PING_UpdateGameLogic,UID:#uid,CLIENTTIME:#ctime,SID:#sid$";
	Helper::Replace(msg, "#uid", to_string(UID));
	Helper::Replace(msg, "#sid", to_string(SID));
	Helper::Replace(msg, "#ctime", to_string(ClientTimeManager::Instance()->GetClientCurrentTime()));
	DataSend->push_back(msg);
}
string ClientManager::RECV_PING_UpdateGameLogic(string* updateinf)
{
	string response = "Wait";
	if (!Received()) return response;
	list<string>::iterator i = DataRecv->begin();
	while (i != DataRecv->end() || DataRecv->size() > 3)
	{
		string recvdata = *i;
		vector<string> decode = StringHelper::split(recvdata, ",");
		//string response = "METHOD:Ping_UpdateGameLogic,CODE:200,UID:#uid,DATA:#data$";
		if (Helper::Equals(Helper::GetString(decode, 0), "PING_UpdateGameLogic"))
		{
			string data = Helper::GetString(decode, 3);
			if (*updateinf != "")
				(*updateinf).append("|");
			(*updateinf).append(data);
		}
		else if (Helper::Equals(Helper::GetString(decode, 0), "Controll"))
		{
			Ping = (int) (ClientTimeManager::Instance()->GetClientCurrentTime() - (DWORD) Helper::GetDWORD(decode, 3));
		}
		DataRecv->pop_front();
		i = DataRecv->begin();
	}
	response = "PING_UpdateGameLogic:OK";
	return response;
}
void ClientManager::SEND_Controll(string command)
{
	if (Offline) return;
	string msg = "1METHOD:Controll,UID:#uid,CLIENTTIME:#ctime,COMMAND:#command$";
	Helper::Replace(msg, "#uid", to_string(UID));
	Helper::Replace(msg, "#sid", to_string(SID));
	Helper::Replace(msg, "#ctime", to_string(ClientTimeManager::Instance()->GetClientCurrentTime()));
	Helper::Replace(msg, "#command",command);
	DataSend->push_back(msg);
}
string ClientManager::RECV_Controll(int* ping,int *tankid)
{
	string response = "Wait";
	if (DataRecv->begin() == DataRecv->end()) 
		return response;
	string data = *DataRecv->begin();
	//string msg = "METHOD:Controll,CODE:#code,UID:#uid,SERVERTIME:#server_time$";
	vector<string> decode = StringHelper::split(data, ",");
	if (Helper::Equals(Helper::GetString(decode, 0), "Controll"))
	{
		Ping = (int)(ClientTimeManager::Instance()->GetClientCurrentTime() - (DWORD)Helper::GetDWORD(decode,3));
		if (ping != NULL)
		{
			*ping = Ping;
			*tankid = UID;
		}
		DataRecv->pop_front();
		response = "Controll:OK";
	}
	return response;
}

bool ClientManager::Received()
{
	return (DataRecv->begin() != DataRecv->end());
}
bool ClientManager::CanSend()
{
	return (DataSend->begin() != DataSend->end());
}