#include "MissionState.h"



MissionState::MissionState()
{
	_IsWin = 0;
	_IsReset = false;
	_IsLose = false;
	//FullTime = MISSION_1_FULL_TIME;
}

bool MissionState::IsReset()
{
	return _IsReset;
}

bool MissionState::IsWin()
{
	//return (_IsWin > WIN_GAME_DELAY) ? true : false;
	return (_IsWin > 0) ? true : false;
}

bool MissionState::IsWining()
{
	//return (_IsWin > 0 && _IsWin <= WIN_GAME_DELAY ) ? true : false;
	return (_IsWin > 0 && _IsWin <= 0) ? true : false;
}

bool MissionState::IsLose()
{
	return _IsLose;
}

void MissionState::WinMission()
{
	_IsWin = 1;
}
