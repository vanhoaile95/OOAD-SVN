#include "Server.h"
#include "ConfigsManager.h"


Server::Server()
{
}


Server::~Server()
{

}
int Server::Init(int SID)
{
	MaxClient = ConfigsManager::Instance()->GetIntConfig(ConfigName::MAX_CLIENT_IN_GAME);
	this->SID = SID;
	for (int i = 0; i < MaxClient; i++)
	{
		listUID[i] = -1;
	}
	ClientCount = 0;
	MapIndex = 0;
	State = ServerState::INIT;
	return 0;
}
int Server::Execute()
{
	for (int i = 0; i < MaxClient; i++)
	{
		if (listUID[i] > 0)
		{
			Client* current = ClientManager::Instance()->GetClient(listUID[i]);
			if(current != NULL) current->Execute();
		}
	}
	return 0;
}
int Server::End()
{
	State = ServerState::GAME_END;
	return 0;
}
int Server::Join(int UID)
{

	for (int i = 0; i < MaxClient; i++)
	{
		if (listUID[i] == -1)
		{

			listUID[i] = UID;
			ClientCount += 1;

			if (ClientCount >= MaxClient)
			{
				State = ServerState::FULL;
			}
			else
			{
				if (State == ServerState::INIT)
					State = ServerState::WAITING;
			}
			break;
		}
		else if (listUID[i] == UID)
		{
			break;
		}
	}
	return 1;
}

int Server::Exit(int UID)
{
	if (this == NULL) return 1;
	int count = 0;
	for (int i = 0; i < MaxClient; i++)
	{
		if (listUID[i] == UID)
		{
			listUID[i] = -1;
		}
		else if (listUID[i] == -1)
		{
			count++;
		}
	}
	if (count < MaxClient) return 1;
	return 0;
}


int Server::StartGame()
{
	if (State == ServerState::GAME_RUN)
	{
		return 1;
	}
	State = ServerState::GAME_RUN;

	for (int i = 0; i < MaxClient; i++)
	{
		if(listUID[i] != -1)
			Clients[i] = ClientManager::Instance()->GetClient(listUID[i]);
		else Clients[i] = NULL;
	}
	return 0;
}

