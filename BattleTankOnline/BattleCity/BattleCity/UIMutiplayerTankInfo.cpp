#include "UIMutiplayerTankInfo.h"
#include "GameScore.h"

UIMutiplayerTankInfo::UIMutiplayerTankInfo(P pos, int uid, int tid, bool visible) : UIObject(pos, BObjectName::UI_TANK_WHITE, visible)
{
	InitSprite();
	GameSprite = CSprite::GetGlobalSpriteSheet();
	UIDInfo = new UIDigit(P(Position.X + 100, Position.Y + 16), 2, true);
	Bar = new UIDigit(P(Position.X+60, Position.Y - 64), 1, true);
	Kill = new UIDigit(P(Position.X, Position.Y - 64), 3, true);
	Death = new UIDigit(P(Position.X + 120, Position.Y - 64), 3, true);
	UpdateInfo(uid, tid);
	UpdateKillDeath(0, 0);
	Ready = true;
	Value = SelectedValue::SelectServer;
}
void UIMutiplayerTankInfo::ReverseYAxis()
{
	UIObject::ReverseYAxis();
	UIDInfo->ReverseYAxis();
	Kill->ReverseYAxis();
	Death->ReverseYAxis();
}
void UIMutiplayerTankInfo::Draw()
{
	if (Visible)
	{
		GameSprite->Draw(TankRect, Position);

		UIDInfo->Draw();
		Kill->Draw();
		Death->Draw();
		Bar->Draw();
	}
}

void UIMutiplayerTankInfo::UpdateInfo(int uid, int tid)
{
	if (uid == Helper::GetUID())
	{
		UIDInfo->CurrentColor = Color::Yellow;
		Kill->CurrentColor = Color::Yellow;
		Death->CurrentColor = Color::Yellow;
		Bar->UpdateValue(-21);
	}
	else
	{
		UIDInfo->CurrentColor = Color::White;
		Kill->CurrentColor = Color::White;
		Death->CurrentColor = Color::White;
		Bar->UpdateValue(-20);
	}

	if (uid > 0)
		UIDInfo->UpdateValue(uid);
	else
		UIDInfo->UpdateValue(0);
	UID = uid;
	TankIndex = tid;
	switch (TankIndex)
	{
	case 0:
	case 2:
		ObjectName = BObjectName::UI_TANK_WHITE;
		break;
	case 1:
	case 3:
		ObjectName = BObjectName::UI_TANK_GREEN;
		break;
	default:
		ObjectName = BObjectName::UI_TANK_BOT;
		break;
	}
	InitRect();
}

void UIMutiplayerTankInfo::UpdateKillDeath(int kill, int death)
{
	if (UID == Helper::GetUID())
	{
		Kill->CurrentColor = Color::Yellow;
		Death->CurrentColor = Color::Yellow;
	}
	else
	{
		Kill->CurrentColor = Color::White;
		Death->CurrentColor = Color::White;
	}
	Kill->UpdateValue(kill);
	Death->UpdateValue(death);
}
void UIMutiplayerTankInfo::UpdateTankRECT(RECT tankrect)
{
	TankRect = tankrect;
}