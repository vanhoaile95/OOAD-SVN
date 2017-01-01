#ifndef MULTIPLAYER_MAIN
#define MULTIPLAYER_MAIN
#pragma once
#include "UI.h"
#include "UIServerInfo.h"
#include "UIClientInfo.h"

class MultiplayerMain : public UI
{
public:
	MultiplayerMain();
	~MultiplayerMain();

	UISelectButton *btnMain = NULL,*btnStart = NULL;
	UIDigit *UID = NULL, *SID = NULL;
	UIServerInfo* ServerInfo[4];
	UIClientInfo* ClientInfo[4];
	list<ServerInf>* CurrentServerInfoData;

	int CurrentIndex = -1;
	int TotalServer = 4;
	int updateTime;
public:
	virtual void Init();
	virtual void RenderFrame();
	virtual void UpdateWorld();

	virtual void ProcessInput() {};
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	virtual void HandlerAction(SelectedValue value);

	void SelectServer(bool up = true);
	void UpdateClientInfo(ClientInf * clientInf []);
};
#endif
