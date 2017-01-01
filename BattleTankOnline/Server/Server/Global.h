#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once
#include "MissionManager.h"

class Global
{
private:
	Global();
	static Global *_instance;
public:
	static Global* Instance();
	map<int, MissionManager*> *GameLogic;
	Mission * GetServer(int sid);
};
#endif