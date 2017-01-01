 #ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include "Algorithm.h"
#include "GameInfor.h"
#include "Factory.h"
#include "ServerTimeManager.h"

class Object: public Box
{

public: // object controller
	P ObjectVelocity;
	BObjectName ObjectName; 

	int HP;
	int ID;
	int RECTIndex = 0;
public: 
	bool IsDisappear; 

	Object(P pos);
	Object(P pos, BObjectName name);

	virtual void Update(){}
	virtual bool HandlerCollision(Collision collision, int sid){ return false; }
	virtual bool HandlerBulletCollision(Collision collision, int tankid, int tanktype,int sid) { return false; }
	virtual void UpdateAfterCollision(){}
	virtual Box GetBox();
	virtual void ReverseYAxis();
	virtual string Controll(string msg);

	bool IsUpdateObject();

};
#endif

