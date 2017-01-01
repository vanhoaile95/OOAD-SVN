#ifndef AI_TANK_H
#define AI_TANK_H
#pragma once
#include "Tank.h"

class AITank : public Tank
{
public:
	int AITimeControl = 0;
	int TimeChangeControl = 0;
	int AIFireControl = 0;
	int FireFullTime = 0;


	bool EnableAI = false;
public:
	AITank(P pos, BObjectName Name,int tankid);
	virtual void Update();

	virtual void EnableAIMode();
	virtual void AIControll();
};
#endif //AI_TANK_H