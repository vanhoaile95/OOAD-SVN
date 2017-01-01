#define CLIENT
#ifdef CLIENT
#pragma once
#include "Helper.h"
//#include "Tank.h"

class Client
{
public:
	int UID;
	int SID;
	int TankID;
	int Ping;
	list<string>* RecvData;
	list<string>* SendData;
	//list<string>* SendDataPirority;
	//string CLientPositionUpdate[4];
	list<string>* GameLogicUpdate;
	string customData;
	//Tank* Tank;

	Client();
	~Client();
	bool IsRECVDataEmpty();
	bool IsSENDDataEmpty();
	void PopSendData();

	void InitUser(char* recvdata, int uid, int sid);
	void Receive(char * recvdata);
	void Receive(string recvdata);

	void Execute();
	string GetSendData();



	void PING_UpdateGameLogic(string command);
	string PING_UpdateGameLogic(int *check);
};
#endif // CLIENT