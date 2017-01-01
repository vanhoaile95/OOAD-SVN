#define SERVER_TIME_MANAGER
#ifdef SERVER_TIME_MANAGER
#pragma once
#include <Time.h>
#include <Windows.h>
#include "ConfigsManager.h"

class ServerTimeManager
{
private:
	static ServerTimeManager *_instance;
	ServerTimeManager();
	~ServerTimeManager();

public:
	DWORD ServerThreedSleepTime = 0;
	int RecvFrameCount;
	int ExecuteFrameCount;
	static ServerTimeManager* Instance();
	int DeltaTime;

	DWORD Count;
	DWORD TickPerFrame;

	DWORD FrameStart;
	DWORD FrameEnd;

	bool CanCreateNewFrame();
	void SleepToNewFrame();
	void ThreadSleep(DWORD ms);
	void ServerThreadSleep();
	void ResetDeltaTime();

	void Init();
	int GetServerTime();
};

#endif // SERVER_TIME_MANAGER