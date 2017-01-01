#ifndef MISSION_MANAGER_H
#define MISSION_MANAGER_H

#include <map>
#include <dinput.h>
#include "Mission.h"
#include "GameState.h"

class MissionManager
{

public:
	int SID;
	
	GameState CurrentState;
	Mission* CurrentScene;

	bool IsPause;

	MissionManager();
	~MissionManager();

	void Init(int sid, Map * map);

	void UpdateWorld();
};

#endif