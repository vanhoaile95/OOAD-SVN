#ifndef TANK_H
#define TANK_H
#pragma once
#include "DynamicObject.h"
#include "TankEnumDefine.h"
#include "TankBullet.h"
//#include "Server.h"

class Tank : public DynamicObject
{
public:
	Direction CurrentDirection;
	Collision Collide;
	float MaxSpeed;
	TankBullet* Bullet;

	int Exp;
	int ExpToUpgrade;
	int Bounty;
	int TankID;
	int SID = -1;
	TankType CurrentTankType;
	Color CurrentTankColor;
	P InitPoint;

	int ShieldTime = -1;

	string ServerMsg = "";
public:
	Tank(P pos, BObjectName Name, int tankid);
	void Start();
	void Fire();
	virtual void Update();
	virtual void LateUpdate();
	virtual bool HandlerCollision(Collision collision, int sid);
	virtual bool HandlerBulletCollision(Collision collision, int tankid, int tanktype, int sid);

	string Index;
	virtual string Controll(string msg);

	void CheckAndUpgrade();
	void ChangeType(TankType type);

};
#endif //TANK_H