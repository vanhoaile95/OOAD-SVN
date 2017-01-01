#include "ClientTankManager.h"



ClientTankManager* ClientTankManager::_instance = 0;


ClientTankManager* ClientTankManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new ClientTankManager();
	}
	return _instance;
}
ClientTankManager::ClientTankManager()
{
}