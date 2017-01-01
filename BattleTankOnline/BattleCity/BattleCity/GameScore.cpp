#include "GameScore.h"
//#include "EffectManager.h"

GameScore* GameScore::_instance = NULL;

GameScore::GameScore()
{
	for (int i = 0; i < 4; i++)
	{
		MulTiplayerInfo[i] = new TankBattleInfo();
	}
	SinglePlayerInfo = new MissionInfo();
	TotalScore = 0;

	ResetGame();
}

GameScore::~GameScore()
{
}

GameScore* GameScore::Instance()
{
	if (_instance == NULL)
	{
		_instance = new GameScore();
	}
	return _instance;
}
void GameScore::ResetGame()
{
	for (int i = 0; i < 4; i++)
	{
		MulTiplayerInfo[i]->Death = 0;
		MulTiplayerInfo[i]->Kill = 0;
		MulTiplayerInfo[i]->UID = -1;
	}
	TotalScore = 0;
	for (int i = 0; i < 7; i++)
	{
		SinglePlayerInfo->Kill[i] = 0;
	}
}