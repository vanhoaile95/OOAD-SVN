#include <cstdlib> 
#include <ctime> 
#include "Helper.h"
#include "ClientManager.h"
#include "ServerManager.h"
#include "ServerGameLogic.h"

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
	return (int) atoi(x.c_str());
}
float Helper::GetFloatFromString(string x)
{
	return (float) atof(x.c_str());
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
bool Helper::Equals(string a, string b)
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
	return Helper::GetIntFromString(GetString(decode, pos, element));
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
	return from + rand() %(to-from);
}

void Helper::OffServerGameLogic(int sid)
{
	ServerGameLogic::Instance()->OffServer(sid);
}

//Server function
void Helper::PING_UpdateGameLogic(int sid,string command)
{
	if (sid == -1) return;
	Server* server = ServerManager::Instance()->GetServer(sid);
	for (int i = 0; i < server->MaxClient; i++)
	{
		if(server->listUID[i] != -1)
			server->Clients[i]->PING_UpdateGameLogic(command);
	}
}

