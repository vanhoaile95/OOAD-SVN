#include "GameController.h"

GameController* GameController::_instance = 0;

GameController* GameController::Instance()
{
	if (0 == _instance)
	{
		_instance = new GameController();
	}
	return _instance;
}
GameController::GameController()
{
}


GameController::~GameController()
{
}
