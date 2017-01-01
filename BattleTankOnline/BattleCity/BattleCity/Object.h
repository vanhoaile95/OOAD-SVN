 #ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include "Sprite.h"
#include "TextureRectManager.h"
#include "Algorithm.h"
#include "GameInfor.h"
#include "Factory.h"
#include "ClientTimeManager.h"

class Object: public Box
{

public: // object controller
	P ObjectVelocity;
	BObjectName ObjectName; 
public: //sprite controller
	CSprite *Sprite;
	RECT* SpriteRect;
	int RECTTime;
	int RECTTimeInterval;
	int DrawLayer;

	int HP;
	int ID;
	int RECTIndex = 0;
public: 
	bool IsDisappear; 
	Object(P pos);
	Object(P pos, BObjectName name);

	virtual void InitSprite() {}
	virtual void Draw(){}
	virtual void Update(){}
	virtual bool HandlerCollision(Collision collision){ return false; }
	virtual bool HandlerBulletCollision(Collision collision,int tankid, int tanktype) { return false; }
	virtual void UpdateAfterCollision(){}
	virtual Box GetBox();
	virtual void ReverseYAxis();
	virtual int Controll(P pos, string msg, int ping);

	bool IsUpdateObject();
	int InitDrawLayer();

};
#endif

