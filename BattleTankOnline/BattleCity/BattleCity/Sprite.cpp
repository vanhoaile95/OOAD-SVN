#include "Sprite.h"

CSprite* CSprite::Atlas1 = NULL;
CSprite* CSprite::UI = NULL;

CSprite::CSprite(MTexture Texture)
{
	_Image = TextureManager::GetInstance()->Get(Texture);
	if (_Image == NULL) {
		int i = 0;
		i++;
	}
}

void CSprite::Draw(P pos)
{
	if (_Image != NULL)
	{
		RECT srect;
		srect.left = 0;
		srect.top = 0;
		srect.right = (LONG)(srect.left + pos.X);
		srect.bottom = (LONG)(srect.top + pos.Y);
		Camera::GetInstance()->Draw(*_Image, srect,pos);
	}
}

void CSprite::FixedDraw(P pos)
{
	if (_Image != NULL)
	{
		RECT srect;
		srect.left = 0;
		srect.top = 0;
		srect.right = (LONG)(srect.left + pos.X);
		srect.bottom = (LONG)(srect.top + pos.Y);
		Camera::GetInstance()->FixedDraw(*_Image, srect,pos);
	}
}

void CSprite::Draw(RECT srect, P pos)
{
	Camera::GetInstance()->Draw(*_Image, srect, pos);
}

void CSprite::FixedDraw(RECT srect,P pos)
{
	Camera::GetInstance()->FixedDraw(*_Image, srect, pos);
}
CSprite* CSprite::GetGlobalSpriteSheet()
{
	if (Atlas1 == NULL)
	{
		Atlas1 = new CSprite(MTexture::TEXTURE_ATLAS_1);
	}
	else {
	}
	return Atlas1;
}
CSprite* CSprite::GetUISpriteSheet()
{
	if (UI == NULL)
	{
		UI = new CSprite(MTexture::UI_TEXTURE);
	}
	return UI;
}