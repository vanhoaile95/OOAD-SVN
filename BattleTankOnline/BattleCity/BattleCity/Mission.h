#ifndef MISSION_H
#define MISSION_H

#include "Build.h"
#include "CollisionManager.h"
#include "ClientTimeManager.h"
#include "ConfigsManager.h"
#include "Scene.h"
#include "AITank.h"
#include "MultiPlayerHud.h"

class Mission : public Scene
{
protected:
	float *VPX;
	float *VPY;

	//EndMission* _EndMission;
public:
	int UpdateTime;
	int UpdateInteval;
	
	bool CanCheckUpdate = true;

	map<int,Object *> _listObjects;
	map<int, AITank *> Tanks;
	AITank* TankControl;
	list<TankBullet*> _listBullets;
	//MarioPlayer* _Mario;
	Map *_Map;
	MultiPlayerHud *MultiplayerHud;
	DWORD test1, test2;

	Object *Base1, *Base2;

	Mission();
	virtual void Init();
	virtual void InitBorderAndTank();
	virtual void UpdateWorld();
	virtual void RenderFrame();
	virtual void Reset();

	virtual void ProcessInput();
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	virtual void ServerGameLogicUpdate();

	~Mission();
};

#endif