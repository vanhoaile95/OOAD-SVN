#define COLLISION_MANAGER_H
#ifdef COLLISION_MANAGER_H
#pragma once
#include "AITank.h"
#include "TankBullet.h"

class CollisionManager
{
public:

	static Box GetSweptBroadphaseBox(Box b);

	static Collision CollisionCheckWithObjectBox(Box BoxdObject, Box BoxObject);

	static bool AABBCheck(Box b1, Box b2);

	static float MySweptAABB(Box b1, Box b2, CollisionDirection & result);

	static CollisionDirection Orientation(Box boxmain, Box b2, float entryTime);

	static CollisionDirection getOppositeDirection(CollisionDirection direction);

	static void CollisionCheckObject(Object * dObjectA, Object * ObjectB);
	static void CollisionCheckWithBulletObject(Object * dObjectA, TankBullet * ObjectB);
};


#endif // COLLISION_MANAGER_H
