#include "ClientManager.h"
#include "UIClientInfo.h"

UIClientInfo::UIClientInfo(P pos, int uid, int tid, bool visible) : UIObject(pos, BObjectName::UI_TANK_WHITE, visible)
{
	InitSprite();
	UIDInfo = new UIDigit(P(Position.X + 72, Position.Y + 16), 2, true);
	UpdateInfo(uid, tid);
	Ready = true;
	Value = SelectedValue::SelectServer;
}
void UIClientInfo::ReverseYAxis()
{
	UIObject::ReverseYAxis();
	UIDInfo->ReverseYAxis();
}
void UIClientInfo::Draw()
{
	if (Visible)
	{
		StaticObject::Draw();
		UIDInfo->Draw();
	}
}

void UIClientInfo::UpdateInfo(int uid,int tid)
{
	if (uid == ClientManager::Instance()->UID)
	{
		UIDInfo->CurrentColor = Color::Yellow;
	}
	else
	{
		UIDInfo->CurrentColor = Color::White;
	}

	if(uid > 0)
		UIDInfo->UpdateValue(uid);
	else
		UIDInfo->UpdateValue(0);
	UID = uid;
	TankIndex = tid;
	if (UID == -1)
	{
		ObjectName = BObjectName::UI_TANK_BOT;
	}
	else
	{
		switch (TankIndex)
		{
		case 0:
			ObjectName = BObjectName::UI_TANK_WHITE;
			break;
		case 1:
			ObjectName = BObjectName::UI_TANK_YELLOW;
			break;
		case 2:
			ObjectName = BObjectName::UI_TANK_GREEN;
			break;
		case 3:
			ObjectName = BObjectName::UI_TANK_RED;
			break;
		default:
			ObjectName = BObjectName::UI_TANK_BOT;
			break;
		}
	}
	InitRect();
}