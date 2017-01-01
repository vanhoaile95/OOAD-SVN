#define CLIENT_TIME_MANAGER
#ifdef CLIENT_TIME_MANAGER
#pragma once
#include <Time.h>
#include <Windows.h>
#include "ConfigsManager.h"

class ClientTimeManager
{
private:
	static ClientTimeManager *_instance;
	ClientTimeManager();
	~ClientTimeManager();

public:
	static ClientTimeManager* Instance();

	DWORD ClientThreedSleepTime = 0;
	bool IsPause;
	int SendFrameCount;
	int RecvFrameCount;

	int DeltaTime;
	int Ping;

	DWORD Count;
	DWORD TickPerFrame = 8;

	DWORD FrameStart;
	DWORD FrameEnd;



	bool CanCreateNewFrame();
	void SleepToNewFrame();
	void ClientSleep(DWORD ms);
	void ClientThreadSleep();
	void ResetDeltaTime();
	void UpdatePing(DWORD serverTime);
	void Init();
	DWORD GetClientCurrentTime();
};

#endif // CLIENT_TIME_MANAGER