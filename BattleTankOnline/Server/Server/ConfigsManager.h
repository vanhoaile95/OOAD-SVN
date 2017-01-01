#define CONFIG_MANAGER
#ifdef CONFIG_MANAGER
#pragma once

#define BACK_BUFFER_FORMAT D3DFMT_X8R8G8B8
#define DATA_BUFSIZE 8192
#define KEYBOARD_BUFFER_SIZE 1024
#define FULL_SCREEN false

#define SCREEN_WIDTH  1000	
#define SCREEN_HEIGHT 700

#define GAME_NAME "Battle Tank"

#include "Helper.h"
#include "ConfigEnumDefine.h"

using namespace std;

class ConfigsManager
{
private:
	static ConfigsManager *_instance;
	ConfigsManager();
	~ConfigsManager();
public:
	//MissionManager *MissionManager = NULL;
public:

	int IntConfigs[100];
	float FloatConfigs[100];
	string StringConfigs[100];
	float TankUpgradeConfig[8][10];

	static ConfigsManager* Instance();
	void InitConfigs();
	float GetTankConfig(int tanktype, TankConfigName var_name);
	int GetIntConfig(ConfigName var_name);
	string GetStringConfig(ConfigName var_name);
	char* GetCharConfig(ConfigName var_name);
	float GetFloatConfig(ConfigName var_name);


};
#endif // CONFIG_MANAGER