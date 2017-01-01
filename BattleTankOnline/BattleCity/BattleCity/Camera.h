#ifndef CAMERA_H
#define CAMERA_H
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "GameInfor.h"
#include "DirectXWindows.h"
#include "Collision.h"
#include "Algorithm.h"

class Camera
{
private:
	Camera();
	~Camera();
	static Camera* _instance;

public:
	float VPX;
	float VPY;

	//RECT getRect();
	LPD3DXSPRITE _SpriteHandler;
	static Camera* GetInstance();
	
	void BeginDraw();
	void EndDraw();
	void Draw(LPDIRECT3DTEXTURE9 Image,RECT srect,P pos);
	void FixedDraw(LPDIRECT3DTEXTURE9 Image,RECT srect,P pos);
};

#endif