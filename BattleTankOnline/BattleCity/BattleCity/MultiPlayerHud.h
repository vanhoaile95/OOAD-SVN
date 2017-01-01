#ifndef MULTIPLAYER_HUD_H
#define MULTIPLAYER_HUD_H
#pragma once
#include "UI.h"
#include "UIMutiplayerTankInfo.h"
#include "ClientInfo.h"


class MultiPlayerHud : UI
{
public:
	UIMutiplayerTankInfo* TankInfo[4];

public:
	MultiPlayerHud();
	~MultiPlayerHud();
	virtual void Init();
	void InitOffline();
	void Init(ClientInf * clientinf []);
	void Init(ClientInf * clientinf [], RECT * TankRect);
	void Init(RECT * TankRect);
	void UpdateInfo();
	RECT * GetTankRECT();
	void UpdateTankRECT(RECT * TankRect);
	virtual void RenderFrame();
	virtual void UpdateWorld();
};
#endif