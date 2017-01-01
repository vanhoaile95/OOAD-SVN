#ifndef SPRITE_H
#define SPRITE_H
#pragma once
#include "Camera.h"
#include "TextureRectManager.h"

class CSprite
{
private:
	static CSprite* Atlas1;
	static CSprite* UI;
public:
	LPDIRECT3DTEXTURE9 *_Image;				// The container of all the sprites
public:
	CSprite(MTexture Texture);
	void Draw(P pos);
	void FixedDraw(P pos);
	void Draw(RECT srect,P pos);
	void FixedDraw(RECT srect,P pos);
	static CSprite* GetGlobalSpriteSheet();
	static CSprite* GetUISpriteSheet();
};

#endif
