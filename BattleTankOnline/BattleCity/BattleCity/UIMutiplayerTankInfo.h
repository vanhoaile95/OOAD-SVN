#ifndef UI_MULTIPLATER_TANK_INFO_H
#define UI_MULTIPLATER_TANK_INFO_H
#pragma once
#include "UIDigit.h"

class UIMutiplayerTankInfo :public UIObject
{
public:
	int UID;
	int TankIndex;
public:
	bool Ready;
	UIDigit* UIDInfo;
	UIDigit* Kill, *Death;
	UIDigit* Bar;

	CSprite *GameSprite;
	RECT TankRect;
	UIMutiplayerTankInfo(P pos, int uid, int tid, bool visible = true);

	virtual void ReverseYAxis();

	virtual void Draw();

	void UpdateInfo(int uid, int tid);
	void UpdateKillDeath(int kill, int death);
	void UpdateTankRECT(RECT tankrect);


};
#endif //UI_MULTIPLATER_TANK_INFO_H