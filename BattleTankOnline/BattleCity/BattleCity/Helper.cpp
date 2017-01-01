#include "Helper.h"
#include "ClientManager.h"

char* Helper::GetCharFromString(string string)
{
	char *cstr = new char[string.length() + 1];
	strcpy(cstr, string.c_str());
	return cstr;
}
char* Helper::GetCharFromInt(int x)
{
	std::string s = std::to_string(x);
	char* x_char = GetCharFromString(s);
	return x_char;
}
int Helper::GetIntFromString(string x)
{
	return (int)atoi(x.c_str());
}
float Helper::GetFloatFromString(string x)
{
	return (float)atof(x.c_str());
}
unsigned long Helper::GetDWORDFromString(string x)
{
	return  strtoul(x.c_str(), NULL, 0);
}
ULONG Helper::GetULONGFromInt(int x1)
{
	//long x1 = (long)x;
	unsigned long x2 = static_cast<std::make_unsigned<decltype(x1)>::type>(x1);
	return x2;
}
void Helper::Replace(string & source, string const & find, string const & replace)
{
	for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
	{
		source.replace(i, find.length(), replace);
		break;
	}
}
bool Helper::Equals(string a,string b)
{
	return (!a.compare(b));
}
string Helper::GetString(vector<string> decode, int pos, string element)
{
	vector<string> dataarray = StringHelper::split(decode[pos], element);
	if (dataarray.size() > 1) return dataarray[1];
	return "";
}
int Helper::GetInt(vector<string> decode, int pos, string element)
{
	return Helper::GetIntFromString(GetString(decode,pos,element));
}
unsigned long Helper::GetDWORD(vector<string> decode, int pos, string element)
{
	return Helper::GetDWORDFromString(GetString(decode, pos, element));
}
float Helper::GetFloat(vector<string> decode, int pos, string element)
{
	return Helper::GetFloatFromString(GetString(decode, pos, element));
}
int Helper::GetCharLength(char* string)
{
	return  sizeof(string) / sizeof(char);
}
int Helper::Rand(int from, int to)
{
	return from + rand() % (to - from);
}


//Bridge function
int Helper::GetUID()
{
	return ClientManager::Instance()->UID;
}
int Helper::GetSID()
{
	return ClientManager::Instance()->SID;
}
int Helper::GetPing()
{
	return ClientManager::Instance()->Ping;
}
int Helper::GetTankID()
{
	return ClientManager::Instance()->TankIndex;
}
bool Helper::Offline()
{
	return ClientManager::Instance()->Offline;
}

int Helper::MaxTank()
{
	return ClientManager::Instance()->MaxTank;
}

int Helper::MaxClient()
{
	return ClientManager::Instance()->MaxClient;
}
ClientInf* Helper::GetClientInfo(int index)
{
	return ClientManager::Instance()->ClientInfo[index];
}

//Server function
void Helper::SEND_Command(string command)
{
	if (command == "CreateGame")
	{
		ClientManager::Instance()->SEND_CreateGame();
	}
	else if (command == "JoinGameMode")
	{
		ClientManager::Instance()->SEND_JoinGame();
	} 
}

string Helper::RECV_CreateGame(int *uid, int *sid)
{
	return ClientManager::Instance()->RECV_CreateGame(uid, sid);
}
string Helper::RECV_JoinGameMode(list<ServerInf> *listServer, int *sid,int * uid)
{
	return ClientManager::Instance()->RECV_JoinGame(listServer, uid,sid);
}



void Helper::SEND_JoinServer(int sid)
{
	ClientManager::Instance()->SEND_JoinServer(sid);
}
string Helper::RECV_JoinServer(ClientInf * clientInfo [])
{
	return ClientManager::Instance()->RECV_JoinServer(clientInfo);
}


void Helper::SEND_PING_WaitingForClient(int sid)
{
	ClientManager::Instance()->SEND_PING_WaitingForClient(sid);
}
string Helper::RECV_PING_WaitingForClient(ClientInf * clientInfo [],bool *start)
{
	return ClientManager::Instance()->RECV_PING_WaitingForClient(clientInfo, start);
}

void Helper::SEND_StartGame(int sid)
{
	ClientManager::Instance()->SEND_StartGame(sid);
}
string Helper::RECV_StartGame(ClientInf * clientInfo [])
{
	return ClientManager::Instance()->RECV_StartGame(clientInfo);
}

void Helper::SEND_PING_UpdateGameLogic()
{
	ClientManager::Instance()->SEND_PING_UpdateGameLogic();
}

string Helper::RECV_PING_UpdateGameLogic(string * updateinf)
{
	return ClientManager::Instance()->RECV_PING_UpdateGameLogic(updateinf);
}

void Helper::SEND_Controll(string command)
{
	ClientManager::Instance()->SEND_Controll(command);
}

string Helper::RECV_Controll(int * ping,int *tankid)
{
	return ClientManager::Instance()->RECV_Controll(ping, tankid);
}
