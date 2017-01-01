#define CLIENT_TANK_MANAGER
#ifdef CLIENT_TANK_MANAGER
#pragma once

class ClientTankManager
{
private:
	static ClientTankManager *_instance;
	ClientTankManager();

public:
	static ClientTankManager* Instance();
};

#endif