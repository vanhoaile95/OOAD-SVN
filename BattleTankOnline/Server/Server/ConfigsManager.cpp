#include "ConfigsManager.h"

ConfigsManager* ConfigsManager::_instance = 0;
ConfigsManager* ConfigsManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new ConfigsManager();
	}
	return _instance;
}

ConfigsManager::ConfigsManager()
{
	InitConfigs();
}
ConfigsManager::~ConfigsManager()
{

}

void ConfigsManager::InitConfigs()
{
	StringConfigs[ConfigName::SERVER_IP] = "127.0.0.1";
	//StringConfigs[ConfigName::GAME_NAME] = "Battle City";

	IntConfigs[ConfigName::SERVER_PORT] = 443;
	IntConfigs[ConfigName::FRAME_PER_SECOND] = 120;
	IntConfigs[ConfigName::CLIENT_STEP] = 1;
	IntConfigs[ConfigName::MAX_TANK_IN_GAME] = 4;
	IntConfigs[ConfigName::MAX_CLIENT_IN_GAME] = 4;
	IntConfigs[ConfigName::MAX_HOLDING_DATA_SIZE] = 20480;
	IntConfigs[ConfigName::UI_SYNC_INTERVAL] = 100;
	IntConfigs[ConfigName::SLEEP_PERSTEP_TIME] = 100;
	IntConfigs[ConfigName::AITANK_CD_TIME] = 2000;

	IntConfigs[ConfigName::TANK_HP] = 3;
	IntConfigs[ConfigName::BRICK_HP] = 1;
	IntConfigs[ConfigName::UNBREAK_HP] = 100;

	IntConfigs[ConfigName::INIT_SHIELD_TIME] = 2000;
	IntConfigs[ConfigName::DAMAGE_SHIELD_TIME] = 1000;

	TankUpgradeConfig[7][TankConfigName::HP] = 6;
	TankUpgradeConfig[7][TankConfigName::MaxSpeed] = .35f;
	TankUpgradeConfig[7][TankConfigName::Bounty] = 8;
	TankUpgradeConfig[7][TankConfigName::ExpToUpgrade] = -1;
	TankUpgradeConfig[7][TankConfigName::BulletMaxSpeed] = .7f;
	TankUpgradeConfig[7][TankConfigName::BulletDamage] = 4;

	TankUpgradeConfig[6][TankConfigName::HP] = 5;
	TankUpgradeConfig[6][TankConfigName::MaxSpeed] = .35f;
	TankUpgradeConfig[6][TankConfigName::Bounty] = 7;
	TankUpgradeConfig[6][TankConfigName::ExpToUpgrade] = 13;
	TankUpgradeConfig[6][TankConfigName::BulletMaxSpeed] = .6f;
	TankUpgradeConfig[6][TankConfigName::BulletDamage] = 4;

	TankUpgradeConfig[5][TankConfigName::HP] = 3;
	TankUpgradeConfig[5][TankConfigName::MaxSpeed] = .35f;
	TankUpgradeConfig[5][TankConfigName::Bounty] = 6;
	TankUpgradeConfig[5][TankConfigName::ExpToUpgrade] = 11;
	TankUpgradeConfig[5][TankConfigName::BulletMaxSpeed] = .8f;
	TankUpgradeConfig[5][TankConfigName::BulletDamage] = 2;

	TankUpgradeConfig[4][TankConfigName::HP] = 2;
	TankUpgradeConfig[4][TankConfigName::MaxSpeed] = .4f;
	TankUpgradeConfig[4][TankConfigName::Bounty] = 5;
	TankUpgradeConfig[4][TankConfigName::ExpToUpgrade] = 9;
	TankUpgradeConfig[4][TankConfigName::BulletMaxSpeed] = .9f;
	TankUpgradeConfig[4][TankConfigName::BulletDamage] = 2;

	TankUpgradeConfig[3][TankConfigName::HP] = 2;
	TankUpgradeConfig[3][TankConfigName::MaxSpeed] = .3f;
	TankUpgradeConfig[3][TankConfigName::Bounty] = 3;
	TankUpgradeConfig[3][TankConfigName::ExpToUpgrade] = 5;
	TankUpgradeConfig[3][TankConfigName::BulletMaxSpeed] = .6f;
	TankUpgradeConfig[3][TankConfigName::BulletDamage] = 2;

	TankUpgradeConfig[2][TankConfigName::HP] = 1;
	TankUpgradeConfig[2][TankConfigName::MaxSpeed] = .3f;
	TankUpgradeConfig[2][TankConfigName::Bounty] = 3;
	TankUpgradeConfig[2][TankConfigName::ExpToUpgrade] = 5;
	TankUpgradeConfig[2][TankConfigName::BulletMaxSpeed] = .6f;
	TankUpgradeConfig[2][TankConfigName::BulletDamage] = 2;

	TankUpgradeConfig[1][TankConfigName::HP] = 2;
	TankUpgradeConfig[1][TankConfigName::MaxSpeed] = .3f;
	TankUpgradeConfig[1][TankConfigName::Bounty] = 2;
	TankUpgradeConfig[1][TankConfigName::ExpToUpgrade] = 3;
	TankUpgradeConfig[1][TankConfigName::BulletMaxSpeed] = .7f;
	TankUpgradeConfig[1][TankConfigName::BulletDamage] = 1;

	TankUpgradeConfig[0][TankConfigName::HP] = 2;
	TankUpgradeConfig[0][TankConfigName::MaxSpeed] = .25f;
	TankUpgradeConfig[0][TankConfigName::Bounty] = 1;
	TankUpgradeConfig[0][TankConfigName::ExpToUpgrade] = 2;
	TankUpgradeConfig[0][TankConfigName::BulletMaxSpeed] = .6f;
	TankUpgradeConfig[0][TankConfigName::BulletDamage] = 1;
}
int ConfigsManager::GetIntConfig(ConfigName var_name)
{
	return IntConfigs[var_name];
}
float ConfigsManager::GetTankConfig(int tanktype, TankConfigName var_name)
{
	return TankUpgradeConfig[tanktype][var_name];
}
string ConfigsManager::GetStringConfig(ConfigName var_name)
{
	return StringConfigs[var_name];
}
char* ConfigsManager::GetCharConfig(ConfigName var_name)
{
	return Helper::GetCharFromString(StringConfigs[var_name]);
}
float ConfigsManager::GetFloatConfig(ConfigName var_name)
{
	return FloatConfigs[var_name];
}