#include "ClientManager.h"
#include "ServerManager.h"

ClientManager* ClientManager::_instance = 0;

ClientManager::ClientManager()
{
	listClients = new map<int, Client*>();
}
ClientManager* ClientManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new ClientManager();
	}
	return _instance;
}
Client* ClientManager::AddNewPlayer(char* data,int sid)
{
	Client* newPlayer = new Client();
	newPlayer->InitUser(data, nextUIDIndex, sid);
	pair<int, Client*> p(nextUIDIndex, newPlayer);
	listClients->insert(p);
	nextUIDIndex++;
	if (sid == -1)
	{

	}
	else
	{
		Server* server = ServerManager::Instance()->GetServer(sid);
		if (server == NULL) return newPlayer;
		server->Join(nextUIDIndex-1);
	}
	return newPlayer;
}
int ClientManager::PlayerJoin(char* data,int uid)
{
	Server* server = ServerManager::Instance()->GetWaitingServer();
	if (server == NULL) return -1;
	Client* newPlayer = new Client();
	newPlayer->InitUser(data, nextUIDIndex, server->SID);

	server->Join(nextUIDIndex);
	pair<int, Client*> p(nextUIDIndex, newPlayer);
	listClients->insert(p);
	nextUIDIndex++;

	return nextUIDIndex - 1;
}

void ClientManager::DeleteOldClient(int index)
{
	listClients->erase(index);
}
CHAR* ClientManager::getUIDChar(int index)
{
	auto search = listClients->find(index);
	if (search != listClients->end()) {
		return Helper::GetCharFromInt(search->second->UID);
	}
	return "-1";
}
Client* ClientManager::GetClient(int index)
{
	auto search = listClients->find(index);
	if (search != listClients->end()) {
		return search->second;
	}
	return NULL;
}
ClientManager::~ClientManager()
{

}