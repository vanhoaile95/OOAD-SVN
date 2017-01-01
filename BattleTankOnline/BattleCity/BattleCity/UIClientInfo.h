#ifndef UI_CLIENT_INFO_H
#define UI_CLIENT_INFO_H
#pragma once
#include "UIDigit.h"
#include "ClientInfo.h"

class UIClientInfo :public UIObject
{
public:
	int UID;
	int TankIndex;
public:
	bool Ready;
	UIDigit* UIDInfo;
	UIClientInfo(P pos, int uid,int tid, bool visible = true);

	virtual void ReverseYAxis();

	virtual void Draw();

	void UpdateInfo(int UID,int tid);


};
#endif //UI_CLIENT_INFO_H