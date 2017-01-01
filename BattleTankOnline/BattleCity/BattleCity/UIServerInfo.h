#ifndef UI_SERVER_INFO_H
#define UI_SERVER_INFO_H
#pragma once
#include "UIDigit.h"
#include "ServerInfo.h"

class UIServerInfo :public UIObject
{
public:
	int SID;
	int HostID;
	int MapID;
public:
	bool Selected;
	UIDigit* SIDInfo;
	UIObject* SelectBorder;
	UIServerInfo(P pos, int ServerID, bool visible = true);

	virtual void ReverseYAxis();

	virtual void Draw();

	void UpdateInfo(int sid, int hostid = -1, int mapid = -1);

	int GetValue();

};
#endif //UI_SERVER_INFO_H