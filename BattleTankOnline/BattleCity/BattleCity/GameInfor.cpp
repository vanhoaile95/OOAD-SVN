#include "GameInfor.h"

//GameInfor* GameInfor::Instance = NULL;
//
//GameInfor::GameInfor()
//{
//	_MarioX = _MarioY =  new float(0);
//	_DeltaTime = _MarioLevel = new int(0);
//	current_item = 0;
//	for (int i = 0; i < MARIO_MAX_ITEM; i++)
//	{
//		_Item[i] = new Item();
//		*_Item[i] = NO_ITEM;
//	}
//}
//
//GameInfor::~GameInfor()
//{
//	_MarioX = _MarioY = 0;
//	_DeltaTime = _MarioLevel = 0;
//}
//GameInfor* GameInfor::GetInstance()
//{
//	if (Instance == NULL)
//	{
//		Instance = new GameInfor();
//	}
//	return Instance;
//}
//float GameInfor::MarioX()
//{
//	return *Instance->_MarioX;
//}
//float GameInfor::MarioY()
//{
//	return *Instance->_MarioY;
//}
//float* GameInfor::MarioXPointer()
//{
//	return Instance->_MarioX;
//}
//float* GameInfor::MarioYPointer()
//{
//	return Instance->_MarioY;
//}
//int GameInfor::MarioLevel()
//{
//	return *Instance->_MarioLevel;
//}
//int GameInfor::DeltaTime()
//{
//	return *Instance->_DeltaTime;
//}
//int* GameInfor::DeltaTimePointer()
//{
//	return Instance->_DeltaTime;
//}
//int* GameInfor::TimeLeftPointer()
//{
//	return Instance->_TimeLeft;
//}
//int* GameInfor::MarioSpeedPointer()
//{
//	return Instance->_MarioSpeed;
//}
//int* GameInfor::MarioLevelPointer()
//{
//	return Instance->_MarioLevel;
//}
//int* GameInfor::MarioLifePointer()
//{
//	return Instance->_MarioLife;
//}
//int * GameInfor::CurrentWorldPointer()
//{
//	return _CurrentWorld;
//}
//Item* GameInfor::ItemPointer(int i)
//{
//	return _Item[i];
//}
//bool * GameInfor::PauseGamePointer()
//{
//	return _IsPause;
//}
//bool * GameInfor::EndGamePointer()
//{
//	return _IsEndGame;
//}
//void GameInfor::SetGamePauseInfor(bool * IsPause)
//{
//	_IsPause = IsPause;
//}
//void GameInfor::SetMarioInfor(float *X, float *Y, int *Level, int *MarioSpeed,int *MarioLife)
//{
//	_MarioX = X;
//	_MarioY = Y;
//	_MarioLevel = Level;
//	_MarioSpeed = MarioSpeed;
//	_MarioLife = MarioLife;
//}
//void GameInfor::SetGameTimeInfor(int* DeltaTime, int *TimeLeft)
//{
//	_DeltaTime = DeltaTime;
//	_TimeLeft = TimeLeft;
//}
//
//void GameInfor::SetMissionInfor(int * CurrentWorld, bool * IsEndGame)
//{
//	_CurrentWorld = CurrentWorld;
//	_IsEndGame = IsEndGame;
//}
//
//
//void GameInfor::AddItem(int item)
//{
//	if (item != NO_ITEM)
//	{
//		*_Item[current_item % MARIO_MAX_ITEM] = (Item)item;
//		current_item++;
//	}
//}
