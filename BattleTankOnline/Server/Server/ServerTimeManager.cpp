#include "ServerTimeManager.h"

ServerTimeManager* ServerTimeManager::_instance = 0;

ServerTimeManager* ServerTimeManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new ServerTimeManager();
	}
	return _instance;
}
ServerTimeManager::ServerTimeManager()
{
	srand(time(0));
}
ServerTimeManager::~ServerTimeManager()
{

}
void ServerTimeManager::Init()
{
	TickPerFrame = (DWORD) (1000 / ConfigsManager::Instance()->GetIntConfig(ConfigName::FRAME_PER_SECOND));
	DeltaTime = 0;
	Count = 0;
	FrameStart = timeGetTime();
	FrameEnd = FrameStart;
	RecvFrameCount = 0;
	ExecuteFrameCount = 0;
	ServerThreedSleepTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::SLEEP_PERSTEP_TIME);
}
int ServerTimeManager::GetServerTime()
{
	return timeGetTime();
}

bool ServerTimeManager::CanCreateNewFrame()
{
	//if (_IsEndGame != NULL && *_IsEndGame) return false;

	FrameStart = FrameEnd;
	FrameEnd = timeGetTime();
	Count += (FrameEnd - FrameStart);

	if (Count >= TickPerFrame)
	{
		DeltaTime = (int) Count;
		Count = 0;
		ExecuteFrameCount += 1;
		RecvFrameCount += 1;
		return true;
	}
	else
	{
		return false;
	}
}
void ServerTimeManager::SleepToNewFrame()
{
	Sleep(TickPerFrame - Count);
}
void ServerTimeManager::ThreadSleep(DWORD ms)
{
	Sleep(ms);
}
void ServerTimeManager::ServerThreadSleep()
{
	Sleep(ServerThreedSleepTime);
}
void ServerTimeManager::ResetDeltaTime()
{
	FrameStart = timeGetTime();
}
