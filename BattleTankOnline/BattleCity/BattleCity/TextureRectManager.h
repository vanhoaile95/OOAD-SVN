#ifndef TEXTURE_RECT_MANAGER_H
#define TEXTURE_RECT_MANAGER_H
#pragma once
#include "TextureManager.h"
#include "PointStruct.h"
#include "Factory.h"
#include "TankEnumDefine.h"

class TextureRectManager
{
private:
	static TextureRectManager* Instance; 
public:
	TextureRectManager();
	~TextureRectManager();

	static TextureRectManager* GetInstance(); 
	RECT GetBlockRect();
	RECT* GetRECTWithName(BObjectName name,int *maxrectIndex = NULL);
	RECT * GetTankRECT(TankType type, Color color);
	RECT* GetTankRECTWithCondition(P pos, P size, P* offset);
	RECT GetRect(P pos,P size);

};
#endif