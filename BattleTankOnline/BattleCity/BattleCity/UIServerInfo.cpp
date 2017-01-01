#include "UIServerInfo.h"



UIServerInfo::UIServerInfo(P pos, int ServerID,bool visible) : UIObject(pos, BObjectName::UI_SERVER_AVA, visible)
{
	InitSprite();
	SIDInfo = new UIDigit(P(Position.X + 72, Position.Y + 16),2,true);
	SelectBorder = new UIObject(P(Position.X - 4, Position.Y - 4), BObjectName::UI_SERVER_SELECT_BORDER, true);

	UpdateInfo(ServerID);
	Selected = true;
	Value = SelectedValue::SelectServer;
}
void UIServerInfo::ReverseYAxis()
{
	UIObject::ReverseYAxis();
	SIDInfo->ReverseYAxis();
	SelectBorder->ReverseYAxis();
}
void UIServerInfo::Draw()
{
	if (Visible)
	{
		StaticObject::Draw();
		SIDInfo->Draw();
		if (Selected)
			SelectBorder->Draw();
	}
}

void UIServerInfo::UpdateInfo(int sid,int hostid,int mapid)
{
	SIDInfo->UpdateValue(sid);
	SID = sid;

}
int UIServerInfo::GetValue()
{
	return SID;
}
