#ifndef MISSION_STATE_H
#define MISSION_STATE_H
#pragma once
#include "MissionState.h"
class GameStateManager
{
public:
	int GameMode; //  1: single, 2 multi
	GameStateManager();
	~GameStateManager();
};

#endif