#include "StaticObject.h"
#include "Global.h"

StaticObject::StaticObject(P pos,BObjectName name): Object(pos,name)
{
	//InitSprite();
	//InitRect();
}
StaticObject::StaticObject(P pos) : Object(pos)
{
	//InitSprite();
	//InitRect();
}
void StaticObject::InitSprite()
{
	RECTLength = 0;
	Sprite = CSprite::GetGlobalSpriteSheet();
	InitRect();
}
void StaticObject::InitRect()
{
	SpriteRect = TextureRectManager::GetInstance()->GetRECTWithName(ObjectName,&RECTLength);
	Size = P(SpriteRect[0].right - SpriteRect[0].left, SpriteRect[0].bottom - SpriteRect[0].top);
}
void StaticObject::Update()
{
	if (RECTLength > 0) 
	{
		RECTTime += ClientTimeManager::Instance()->DeltaTime;
		if (RECTTime >= RECTLength * RECTTimeInterval) 
		{
			RECTTime = 0;
		}
		else 
		{
			RECTIndex = (RECTTime / RECTTimeInterval);
		}
	}
}
void StaticObject::Draw()
{
	if (Sprite != NULL && !IsDisappear)
	{
		Sprite->Draw(SpriteRect[RECTIndex],Position);
	}
}
void StaticObject::Draw(P position)
{
	if (Sprite != NULL && !IsDisappear)
	{
		Sprite->Draw(SpriteRect[RECTIndex],position);
	}
}
void StaticObject::FixedDraw()
{
	if (Sprite != NULL && !IsDisappear)
	{
		Sprite->FixedDraw(SpriteRect[RECTIndex], Position);
	}
}
int StaticObject::Controll(P pos, string msg, int ping)
{
	vector<string> decode = StringHelper::split(msg, "|");
	if (decode[0] == "10")
	{
		IsDisappear = true;
		enableCollision = false;
	}

	return 0;
}
bool StaticObject::HandlerCollision(Collision collision)
{

	return true; 
}

bool StaticObject::HandlerBulletCollision(Collision collision, int tankid, int tanktype)
{
	if (Helper::Offline())
	{
		if (HP < ConfigsManager::Instance()->GetIntConfig(ConfigName::UNBREAK_HP))
		{
			HP -= 1;
			if (HP <= 0)
			{
				IsDisappear = true;
				enableCollision = false;

				Mission* Current = (Mission*) Global::Instance()->MissionManager->CurrentScene;
				Current->CheckWinGame(ID);
			}
		}
	}
	return true;
}
