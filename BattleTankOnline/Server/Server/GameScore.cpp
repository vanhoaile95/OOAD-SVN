#include "GameScore.h"
//#include "EffectManager.h"

GameScore* GameScore::Instance = NULL;

GameScore::GameScore()
{
	_Score = 0;
	_Coin = 0;
}

GameScore::~GameScore()
{
	_Score = 0;
	_Coin = 0;
}

GameScore* GameScore::GetInstance()
{
	if (Instance == NULL)
	{
		Instance = new GameScore();
	}
	return Instance;
}
int* GameScore::GetScorePointer()
{
	return &Instance->_Score;
}
int* GameScore::GetCoinPointer()
{
	return &Instance->_Coin;
}
void GameScore::ResetGame()
{
	_Score = 0;
	_Coin = 0;
}
void GameScore::AddScore(ScoreEvent Event,float X,float Y)
{
	int ScoreAdd = 0;

	switch (Event)
	{
	case KILL_SIMPLE_ENEMY:
		ScoreAdd= 100;
		break;
	case FLY_TO_SIMPLE_ENEMY:
		ScoreAdd= 100;
		break;
	case KILL_FLY_ENEMY:
		ScoreAdd= 200;
		break;
	case NORMAL_TO_SHELL_TURTLE:
		ScoreAdd= 100;
		break;
	case FLY_TO_NORMAL_FLYTURTLE:
		ScoreAdd= 100;
		break;
	case NORMAL_TO_SHELL_FLYTURTLE:
		ScoreAdd= 200;
		break;
	case KICK_TURTLE_SHELL:
		ScoreAdd= 400;
		break;
	case GET_COIN:
		ScoreAdd= 100;
		Instance->_Coin += 1;
		break;
	case GET_POWERUP:
		ScoreAdd= 1000;
		break;
		break;
	default:
		return;
	}
	if(ScoreAdd > 0) _Score += ScoreAdd;
	//EffectManager::GetInstance()->StartScoreUpEffect(ScoreAdd, X, Y);
}