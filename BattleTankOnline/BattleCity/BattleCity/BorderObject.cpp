#include "BorderObject.h"


BorderObject::BorderObject(BObjectName name) : StaticObject(P(0,0),name)
{
	//InitSprite();
	//InitRect();
}
void BorderObject::InitSprite()
{
	RECTLength = 0;
	Sprite = CSprite::GetGlobalSpriteSheet();
	InitRect();
}
void BorderObject::InitRect()
{
	SpriteRect = TextureRectManager::GetInstance()->GetRECTWithName(ObjectName, &RECTLength);
	switch (ObjectName)
	{
	case BORDER_BELOW:
		Size = P(28 * 32, 32);
		Position = P(0, -4);
		break;
	case BORDER_ABOVE:
		Size = P(28 * 32, 32);
		Position = P(0,668);
		break;
	case BORDER_LEFT:
		Size = P(32, 32 * 22);
		Position = P(0, -4);
		break;
	case BORDER_RIGHT:
		Size = P(32, 32 * 22);
		Position = P(864, -4);
		break;
	default:
		break;
	}
}
void BorderObject::Draw()
{
	if (Sprite != NULL && !IsDisappear)
	{
		switch (ObjectName)
		{
		case BORDER_BELOW:
		case BORDER_ABOVE:
			for (int i = 0; i < 28; i++)
			{
				Sprite->Draw(SpriteRect[RECTIndex], P(Position.X + i * 32, Position.Y));
			}
			break;
		case BORDER_LEFT:
		case BORDER_RIGHT:
			for (int i = 0; i < 22; i++)
			{
				Sprite->Draw(SpriteRect[RECTIndex], P(Position.X, Position.Y + i * 32));
			}
			break;
		default:
			break;
		}
	}
}
void BorderObject::Draw(P position)
{
	if (Sprite != NULL && !IsDisappear)
	{
		Sprite->Draw(SpriteRect[RECTIndex], position);
	}
}
void BorderObject::FixedDraw()
{
	if (Sprite != NULL && !IsDisappear)
	{
		Sprite->FixedDraw(SpriteRect[RECTIndex], Position);
	}
}
int BorderObject::Controll(P pos, string msg)
{
	return 1;
}
bool BorderObject::HandlerCollision(Collision collision)
{
	if (collision.Collider == TypeBoxCollision::BulletBox
		&& HP < ConfigsManager::Instance()->GetIntConfig(ConfigName::UNBREAK_HP))
	{
		HP -= 1;
		if (HP <= 0)
		{
			IsDisappear = true;
			enableCollision = false;
		}
	}
	return true;
}