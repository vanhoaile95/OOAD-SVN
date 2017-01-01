#ifndef MISSION_STATE_H
#define MISSION_STATE_H
#pragma once
#include "ConfigsManager.h"



class MissionState
{
protected:
	bool _IsReset;
	int _IsWin;
	bool _IsLose;
public:
	int FullTime;
	MissionState();
	bool IsReset();
	bool IsWin();
	bool IsWining();
	bool IsLose();
	void WinMission();
};

#endif