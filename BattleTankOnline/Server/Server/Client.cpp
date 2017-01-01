#include "Client.h"
#include "ClientManager.h"
#include "ServerManager.h"
#include "ServerTimeManager.h"
#include "ServerGameLogic.h"

void Client::InitUser(char* recvdata,int uid, int sid)
{
	UID = uid;
	SID = sid;
	customData = "";
	
	RecvData->push_back(recvdata);
	Ping = 0;
}
Client::Client()
{
	RecvData = new list<string>();
	SendData = new list<string>();
	//SendDataPirority = new list<string>();
	GameLogicUpdate = new list<string>();
	UID = -1;
	SID = -1;
	TankID = -1;
}

Client::~Client()
{

}
void Client::Receive(char* recvdata)
{
	RecvData->push_back(recvdata);
}
void Client::Receive(string recvdata)
{
	RecvData->push_back(recvdata);
}
bool Client::IsRECVDataEmpty()
{
	if (this == NULL) return true;
	return (RecvData->begin() == RecvData->end());

}
bool Client::IsSENDDataEmpty()
{
	if (this == NULL) return true;
	return (SendData->begin() == SendData->end());
}
void Client::Execute()
{

	//string msg = "METHOD:CreateGame,UID:-1,CLIENTTIME:#ctime$";
	//string msg = "METHOD:JoinGameMode,UID:#uid,CLIENTTIME:#ctime$";
	//string msg = "METHOD:JoinServer,UID:#uid,CLIENTTIME:#ctime,SID:#sid$";
	if (IsRECVDataEmpty()) return;
	list<string>::iterator value = RecvData->begin();
	string data = *value;
	printf("RECV_Data:%s", data.c_str());
	vector<string> exData = StringHelper::split(data, ",");
	//Execute

	string functionname = Helper::GetString(exData, 0);
	if (functionname == "CreateGame")
	{
		//Xu ly client time

		string msg = "METHOD:CreateGame,CODE:#code,UID:#uid,SERVERTIME:#server_time,SID:#sid$";
		int code = (UID == -1 || SID == -1) ? -1 : 200;
		Helper::Replace(msg, "#code", to_string(code));
		Helper::Replace(msg, "#uid", to_string(UID));
		DWORD svtime = ServerTimeManager::Instance()->GetServerTime();
		Helper::Replace(msg, "#server_time", to_string(svtime));
		Helper::Replace(msg, "#sid", to_string(SID));
		SendData->push_back(msg);
		ServerGameLogic::Instance()->InitGameLogic(SID,0);

	}
	else if (functionname == "JoinGameMode")
	{
		//Xu ly client time
		//
		string msg = "METHOD:JoinGameMode,CODE:#code,UID:#uid,SERVERTIME:#server_time,SID:#sid,SERVERLIST:#server_list$";
		int code = (UID == -1) ? -1 : 200;
		Helper::Replace(msg, "#code", to_string(code));
		Helper::Replace(msg, "#uid", to_string(UID));
		DWORD svtime = ServerTimeManager::Instance()->GetServerTime();
		Helper::Replace(msg, "#server_time", to_string(svtime));
		string serverlist = "";
		list<Server*>* waitingserver = ServerManager::Instance()->listServer;
		for (list<Server*>::iterator i = waitingserver->begin(); i != waitingserver->end(); i++)
		{
			if ((*i)->State == ServerState::WAITING)
			{
				if (serverlist != "")
				{
					serverlist.append("|");
				}
				serverlist.append(to_string((*i)->SID));
				serverlist.append("|");
				serverlist.append(to_string((*i)->listUID[0]));
				serverlist.append("|");
				serverlist.append(to_string((*i)->MapIndex));
			}
		}
		if (serverlist != "")
		{
			serverlist.append("|-1");
		}
		else
		{
			Server* server = ServerManager::Instance()->AddNewServer();
			SID = server->SID;
			server->Join(UID);
			ServerGameLogic::Instance()->InitGameLogic(SID, 0);
		}
		Helper::Replace(msg, "#sid", to_string(SID));
		Helper::Replace(msg, "#server_list", serverlist);
		SendData->push_back(msg);
	}
	else if (functionname == "JoinServer" || functionname == "PING_WaitingForClient" || functionname == "StartGame")
	{
		//Xu ly client
		Server* currentServer = ServerManager::Instance()->GetServer(SID);
		string msg = "METHOD:#method,CODE:#code,UID:#uid,SERVERTIME:#server_time,CLIENTLIST:#client_list,START:#start$";
		int code = (UID == -1) ? -1 : 200;
		Helper::Replace(msg, "#method", functionname);
		Helper::Replace(msg, "#code", to_string(code));
		Helper::Replace(msg, "#uid", to_string(UID));
		DWORD svtime = ServerTimeManager::Instance()->GetServerTime();
		Helper::Replace(msg, "#server_time", to_string(svtime));
		string clientlist = "";

		for (int i = 0; i < currentServer->MaxClient; i++)
		{
			if (clientlist != "")
			{
				clientlist.append("|");
			}
			clientlist.append(to_string(currentServer->listUID[i]));
		}
		Helper::Replace(msg, "#client_list", clientlist);

		if (functionname == "StartGame")
		{
			currentServer->StartGame();
			int total = 0;
			for (int i = 0; i < currentServer->MaxClient; i++)
			{
				if (currentServer->listUID[i] == UID)
					TankID = i;
				ServerGameLogic::Instance()->GetServer(currentServer->SID)->StartGame(currentServer->listUID,currentServer->SID);
			}
		}
		if (currentServer->State == ServerState::GAME_RUN)
		{
			Helper::Replace(msg, "#start", "true");
			for (int i = 0; i < currentServer->MaxClient; i++)
			{
				if (currentServer->listUID[i] == UID)
					TankID = i;
			}
		}
		else
		{
			Helper::Replace(msg, "#start", "false");
		}
		SendData->push_back(msg);
	}
	else if (functionname == "PING_UpdateGameLogic")
	{
		int check = 0;
		string data = PING_UpdateGameLogic(&check);
		if (check > 0)
		{
			SendData->push_back(data);
		}
		else
		{
			list<string>::iterator i = SendData->begin();
			if (i != SendData->end())
			{
				string before = *i;
				vector<string> decode = StringHelper::split(before, ",");
				if (!Helper::Equals(Helper::GetString(decode, 0), "PING_UpdateGameLogic"))
				{
					SendData->push_back(data);
				}
			}
			else
			{
				SendData->push_back(data);
			}
			
		}
	}
	else if (functionname == "Controll")
	{
		//METHOD:Controll,UID:#uid,CLIENTTIME:#ctime,COMMAND:#command$
		if (SendData->begin() != SendData->end())
		{
			int check = true;
			for (list<string>::iterator i = SendData->begin(); i != SendData->end(); i++)
			{
				string before = *i;
				vector<string> decode = StringHelper::split(before, ",");
				if (Helper::Equals(Helper::GetString(decode, 0), "Controll"))
				{
					check = false;
					break;
				}
			}
			if (check)
			{
				string command = Helper::GetString(exData, 3);
				string command_to_other = ServerGameLogic::Instance()->Controll(SID, TankID, command);
				Helper::PING_UpdateGameLogic(SID, command_to_other);

				string msg = "METHOD:#method,CODE:#code,UID:#uid,SERVERTIME:#server_time$";
				int code = (UID == -1) ? -1 : 200;
				Helper::Replace(msg, "#method", functionname);
				Helper::Replace(msg, "#code", to_string(code));
				Helper::Replace(msg, "#uid", to_string(UID));
				DWORD svtime = ServerTimeManager::Instance()->GetServerTime();
				Helper::Replace(msg, "#server_time", to_string(svtime));

				SendData->push_back(msg);
			}
		}
		else
		{
			string command = Helper::GetString(exData, 3);
			string command_to_other = ServerGameLogic::Instance()->Controll(SID, TankID, command);
			Helper::PING_UpdateGameLogic(SID, command_to_other);

			string msg = "METHOD:#method,CODE:#code,UID:#uid,SERVERTIME:#server_time$";
			int code = (UID == -1) ? -1 : 200;
			Helper::Replace(msg, "#method", functionname);
			Helper::Replace(msg, "#code", to_string(code));
			Helper::Replace(msg, "#uid", to_string(UID));
			DWORD svtime = ServerTimeManager::Instance()->GetServerTime();
			Helper::Replace(msg, "#server_time", to_string(svtime));

			SendData->push_back(msg);
		}
	}
	//End Execute
	RecvData->pop_front();
}
string Client::GetSendData()
{
	if (IsSENDDataEmpty()) return "";
	//list<string>::iterator current = SendData->begin();
	//string data = *current;
	//printf("SEND_Data:%s", data.c_str());
	//SendData->pop_front();
	list<string>::iterator current = SendData->begin();
	string data = "";
	data = *current;
	printf("SEND_Data:%s", data.c_str());
	//SendData->pop_front();

	return data;
}
void Client::PopSendData()
{
	if (IsSENDDataEmpty()) return;
	//list<string>::iterator current = SendData->begin();
	//string data = *current;
	//printf("SEND_Data:%s", data.c_str());
	//SendData->pop_front();

	SendData->pop_front();
}

void Client::PING_UpdateGameLogic(string command)
{
	GameLogicUpdate->push_back(command);
}
string Client::PING_UpdateGameLogic(int *check)
{
	string response = "METHOD:PING_UpdateGameLogic,CODE:200,UID:#uid,DATA:#data$";
	Helper::Replace(response, "#uid", to_string(UID));
	string updateData = "";
	list<string>::iterator i = GameLogicUpdate->begin();
	list<string>::iterator j = GameLogicUpdate->begin();
	int count = 0;
	while (i != GameLogicUpdate->end() && count < 20)
	{
		*check = 1;
		if (updateData != "") updateData.append("|");
		updateData.append(*i);
		count++;
		GameLogicUpdate->pop_front();
		i = GameLogicUpdate->begin();
	}
	Helper::Replace(response, "#data", updateData);
	return response;
}

