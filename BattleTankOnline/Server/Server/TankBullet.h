#ifndef TANK_BULLET_H
#define TANK_BULLET_H
#pragma once
#include "DynamicObject.h"
#include "TankEnumDefine.h"

enum BulletState
{
	Idle,
	Firing,
	Exploding,
};

class TankBullet : public DynamicObject
{
public:
	Direction BulletDirection;
	BulletState State;
	float MaxSpeed;
	int Damage;
	int TankID;
	int TankType;
public:
	TankBullet(P pos, Direction dir, int tankid, int tanktype);
	virtual bool HandlerCollision(Collision collision,int sid);
	virtual void Update();
	virtual void LateUpdate();

	virtual string Controll(string msg);
	void ChangeType(int type);
};
#endif //TANK_BULLET_H