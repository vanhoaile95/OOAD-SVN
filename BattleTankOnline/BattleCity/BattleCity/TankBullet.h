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
	int TankID;
	int TankType;
	int Damage;
public:
	TankBullet(P pos, Direction dir, int tankid, int tanktype);
	virtual bool HandlerCollision(Collision collision);
	virtual void LateUpdate();



	virtual int Controll(P pos, string msg, int ping);
	virtual int Controll(string msg);
	virtual void Draw();
	void ChangeType(int type);
};
#endif //TANK_BULLET_H