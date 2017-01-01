#include "ClientTimeManager.h"

ClientTimeManager* ClientTimeManager::_instance = 0;

ClientTimeManager* ClientTimeManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new ClientTimeManager();
	}
	return _instance;
}
ClientTimeManager::ClientTimeManager()
{
	
}
ClientTimeManager::~ClientTimeManager()
{

}
void ClientTimeManager::Init()
{
	TickPerFrame = (DWORD)(1000 / ConfigsManager::Instance()->GetIntConfig(ConfigName::FRAME_PER_SECOND));
	DeltaTime = 0;
	Count = 0;
	IsPause = false;
	FrameStart = timeGetTime();
	FrameEnd = FrameStart;
	SendFrameCount = 0;
	RecvFrameCount = 0;
	ClientThreedSleepTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::SLEEP_PERSTEP_TIME);
}
DWORD ClientTimeManager::GetClientCurrentTime()
{
	return timeGetTime();
}

bool ClientTimeManager::CanCreateNewFrame()
{
	//if (_IsEndGame != NULL && *_IsEndGame) return false;

	FrameStart = FrameEnd;
	FrameEnd = timeGetTime();
	Count += (FrameEnd - FrameStart);

	if (!IsPause)
	{

	}

	if (Count >= TickPerFrame)
	{
		DeltaTime = (int)Count;
		Count = 0;
		SendFrameCount += 1;
		RecvFrameCount += 1;
		return true;
	}
	else
	{
		return false;
	}
}
void ClientTimeManager::SleepToNewFrame()
{
	Sleep(TickPerFrame - Count);
}
void ClientTimeManager::ClientSleep(DWORD ms)
{
	Sleep(ms);
}
void ClientTimeManager::ClientThreadSleep()
{
	Sleep(ClientThreedSleepTime);
}
void ClientTimeManager::ResetDeltaTime()
{
	FrameStart = timeGetTime();
}

void ClientTimeManager::UpdatePing(DWORD serverTime)
{
	Ping = (int)(timeGetTime() - serverTime);
}
