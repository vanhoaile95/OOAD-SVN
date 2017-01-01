#define HELPER
#ifdef HELPER
#pragma once
#include "StringHelper.h"
#include <type_traits>
#include <list>
#include <map>
#include "ServerInfo.h"
#include "ClientInfo.h"

using namespace std;
typedef unsigned long ULONG;
class Helper
{
public:
	static char* GetCharFromString(string string);
	static char* GetCharFromInt(int x);
	static int GetIntFromString(string x);
	static float GetFloatFromString(string x);
	static unsigned long GetDWORDFromString(string x);
	static int GetCharLength(char* string);
	static ULONG GetULONGFromInt(int x);
	static void Replace(string& source, string const& find, string const& replace);
	static bool Equals(string a, string b);
	static string GetString(vector<string> decode,int pos, string element = ":");
	static int GetInt(vector<string> decode, int pos,string element = ":");
	static unsigned long GetDWORD(vector<string> decode, int pos, string element = ":");
	static float GetFloat(vector<string> decode, int pos, string element = ":");
	static int Rand(int from, int to);


	//Bridge function
	static int GetUID();
	static int GetSID();
	static int GetPing();
	static int GetTankID();
	static bool Offline();
	static int MaxTank();
	static int MaxClient();
	static ClientInf * GetClientInfo(int index);

	//Server Function
	static void SEND_Command(string command);
	static string RECV_CreateGame(int * uid = NULL, int * sid = NULL);
	static string RECV_JoinGameMode(list<ServerInf> *listServer, int * uid = NULL, int * sid = NULL);

	static void SEND_JoinServer(int sid);
	static string RECV_JoinServer(ClientInf * clientInfo []);

	static void SEND_PING_WaitingForClient(int sid);
	static string RECV_PING_WaitingForClient(ClientInf * clientInfo [], bool * start);
	
	static void SEND_StartGame(int sid);
	static string RECV_StartGame(ClientInf * clientInfo []);

	static void SEND_PING_UpdateGameLogic();
	static string RECV_PING_UpdateGameLogic(string* updateinf);

	static void SEND_Controll(string command);
	static string RECV_Controll(int * ping = NULL, int * tankid = NULL);
	//GetReceive
};


#endif // HELPER