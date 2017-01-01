#define CLIENT_MANAGER
#ifdef CLIENT_MANAGER
#pragma once
#include <string>
#include <map>
#include "Client.h"

typedef char CHAR;
using namespace std;

class ClientManager
{
private:
	static ClientManager *_instance;
	ClientManager();
	~ClientManager();
public:
	static ClientManager* Instance();

	map<int,Client*>* listClients;
	int nextUIDIndex = 1;
	Client* AddNewPlayer(char* data, int sid = -1);
	int PlayerJoin(char * data, int uid);
	void DeleteOldClient(int index);
	CHAR* getUIDChar(int index);
	Client * GetClient(int index);
};
#endif // CLIENT_MANAGER