#ifndef TANK_H
#define TANK_H
#pragma once
#include "TankBullet.h"
#include "TankEnumDefine.h"

class Tank : public DynamicObject
{
public:
	Direction CurrentDirection;
	Collision Collide;
	float MaxSpeed;
	TankBullet* Bullet;
	int Bounty;
	int ExpToUpgrade;
	int Exp;
	int TankID;
	TankType CurrentTankType;
	Color CurrentTankColor;
	P InitPoint;

	int ShieldTime = -1;
	RECT* ShieldSprite;
public:
	Tank(P pos, BObjectName Name, int tankid);

	void Start();
	void Fire();
	void ChangeType(TankType type);
	void CheckAndUpgrade();
	void UpdateTankRECT();

	virtual void Update();
	virtual void LateUpdate();
	virtual bool HandlerCollision(Collision collision);
	virtual bool HandlerBulletCollision(Collision collision, int tankid, int tanktype);

	virtual int Controll(P pos, string msg, int ping);
	virtual int Controll(string msg);
	virtual void Draw();
	virtual void InitRect();
	RECT TankRECT();
};
#endif //TANK_H