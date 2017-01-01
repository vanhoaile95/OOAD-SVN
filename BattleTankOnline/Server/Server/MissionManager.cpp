#include "MissionManager.h"

MissionManager::MissionManager()
{
	CurrentState = GameState::Loading;
	IsPause = false;
}
MissionManager::~MissionManager()
{

}
void MissionManager::Init(int sid,Map* map)
{
	SID = sid;
	CurrentScene = new Mission();
	CurrentScene->Init(GameState::Map1, map);
	CurrentState = GameState::Running;
}
void MissionManager::UpdateWorld()
{
	CurrentScene->UpdateWorld();
}