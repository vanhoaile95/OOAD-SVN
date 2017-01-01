#define GAME_CONTROLLER
#ifdef GAME_CONTROLLER
#pragma once



class GameController
{
private:
	static GameController* _instance;
	GameController();
	~GameController();
public:
	static GameController* Instance();


};

#endif