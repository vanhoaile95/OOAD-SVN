//#include "GameStatusBar.h"
//
//
//
//GameStatusBar::GameStatusBar()
//{
//	_MainBar = NULL;
//	_Digits = NULL;
//	_Items = NULL;
//	_Enegy = NULL;
//	_Pause = NULL;
//	//_Item = NULL;
//}
//GameStatusBar::~GameStatusBar()
//{
//	_MainBar = NULL;
//	_Digits = NULL;
//	_Items = NULL;
//	_Enegy = NULL;
//	//_Item = NULL;
//	_Pause = NULL;
//}
//
//void GameStatusBar::Init()
//{
//	_MainBar = new CSprite(GAME_STATUS_BAR_TEXTURE,1024,128);
//	_Digits = new CSprite(DIGITS_TEXTURE,412,28);
//	_Items = new CSprite(ITEMS_TEXTURE,384,112);
//	_Enegy = new CSprite(ENEGY_TEXTURE,92,56);
//	_Pause = new CSprite(PAUSE_TEXTURE,784,64);
//
//	_TimeLeft = GameInfor::GetInstance()->TimeLeftPointer();
//	_MarioSpeed = GameInfor::GetInstance()->MarioSpeedPointer();
//	_MarioLife = GameInfor::GetInstance()->MarioLifePointer();
//	_CurrentWorld = GameInfor::GetInstance()->CurrentWorldPointer();
//	_IsPause = GameInfor::GetInstance()->PauseGamePointer();
//	_Score = GameScore::GetInstance()->GetScorePointer();
//	_Coin = GameScore::GetInstance()->GetCoinPointer();
//	for (int i = 0; i < MARIO_MAX_ITEM; i++)
//	{
//		_Item[i] = GameInfor::GetInstance()->ItemPointer(i);
//	}
//
//	_X = 0;
//	_Y = float(SCREEN_HEIGHT - _MainBar->_Height);
//
//}
//
//void GameStatusBar::Update()
//{
//
//}
//
//
//void GameStatusBar::Draw()
//{
//	if (*_IsPause)
//	{
//		PauseDraw();
//	}
//	_MainBar->FixedDraw(_X,_Y);
//	TimeDraw();
//	EnegyDraw();
//	WorldDraw();
//	LifeDraw();
//	ScoreAndCoinDraw();
//	ItemDraw();
//}
//void GameStatusBar::ItemDraw()
//{
//	float elementX = _X + ITEM_X;
//	float elementY = _Y + ITEM_Y;
//	RECT srect;
//	for (int i = 0; i < MARIO_MAX_ITEM; i++)
//	{
//		srect = GetItemRect(*_Item[i]);
//		_Items->FixedDraw(srect, elementX, elementY);
//		elementX += ITEM_WIDTH;
//	}
//}
//void GameStatusBar::WorldDraw()
//{
//	DigitDraw(*_CurrentWorld, NUMBER_OF_WORLD, _X + WORLD_X, _Y + WORLD_Y);
//}
//void GameStatusBar::PauseDraw()
//{
//	_Pause->FixedDraw(SCREEN_WIDTH/2 - PAUSE_WIDTH/2,SCREEN_HEIGHT/2);
//}
//void GameStatusBar::LifeDraw()
//{
//	DigitDraw(*_MarioLife, NUMBER_OF_LIFE, _X + LIFE_X, _Y + LIFE_Y);
//}
//void GameStatusBar::TimeDraw()
//{
//	int temptime = (*_TimeLeft >= 0) ? (int) *_TimeLeft / 1000 : 0;
//	DigitDraw(temptime, NUMBER_OF_TIME, _X + TIME_X, _Y + TIME_Y);
//}
//void GameStatusBar::ScoreAndCoinDraw()
//{
//	DigitDraw(*_Score, NUMBER_OF_SCORE, _X + SCORE_X, _Y + SCORE_Y);
//	DigitDraw(*_Coin, NUMBER_OF_COIN, _X + COIN_X, _Y + COIN_Y);
//}
//void GameStatusBar::EnegyDraw()
//{
//	int tempenegy = (*_MarioSpeed > SPEEDUP_INIT_TIME) ? SPEEDUP_NUMBER_STEP : (*_MarioSpeed / SPEEDUP_ASTEP_TIME);
//	int checkfullspeed = (tempenegy == 7) ? 0: 1;
//	RECT srect;
//	float elementX = _X + ENEGY_X;
//	float elementY = _Y + ENEGY_Y;
//
//	for (int i = 0; i < SPEEDUP_NUMBER_STEP - 1; i++)
//	{
//		if (i < tempenegy)
//		{
//			srect = GetEnegyRect(0, 1);
//		}
//		else
//		{
//			srect = GetEnegyRect(0, 0);
//		}
//		_Enegy->FixedDraw(srect,elementX, elementY);
//		elementX += DIGITS_WIDTH;
//	}
//
//	// nút p
//	elementX += 4;
//	if (tempenegy == SPEEDUP_NUMBER_STEP)
//	{
//		int aniIndex = (*_TimeLeft / 150) % 2;
//		srect = GetEnegyRect(1,aniIndex);
//	}
//	else
//	{
//		srect = GetEnegyRect(1, 0);
//	}
//	_Enegy->FixedDraw(srect, elementX, elementY);
//}
//
//void GameStatusBar::DigitDraw(int Digit,int Number,float X,float Y)
//{
//	float elementX = X + DIGITS_WIDTH*(Number-1);
//	float elementY = Y;
//	RECT rect;
//	for (int i = 0; i < Number; i++)
//	{
//		rect = GetDigitRect(Digit % 10);
//		_Digits->FixedDraw(rect, elementX,elementY);
//		elementX -= DIGITS_WIDTH;
//		Digit /= 10;
//	}
//}
//RECT GameStatusBar::GetDigitRect(int Digit)
//{
//	Digit = (Digit >= 0 && Digit < 10) ? Digit : 0;
//	RECT srect = RECT();
//	srect.left = DIGITS_WIDTH * Digit;
//	srect.top = 0;
//	srect.right = srect.left + DIGITS_WIDTH;
//	srect.bottom = srect.top + DIGITS_HEIGHT;
//	return srect;
//}
//
//RECT GameStatusBar::GetEnegyRect(int button,int active)
//{
//	RECT srect = RECT();
//	srect.left = button * DIGITS_WIDTH;
//	srect.top = active * DIGITS_HEIGHT;
//	srect.right = (button) ? srect.left + BUTTON_P_WIDTH : srect.left + DIGITS_WIDTH;
//	srect.bottom = srect.top + DIGITS_HEIGHT;
//	return srect;
//}
//RECT GameStatusBar::GetItemRect(Item item)
//{
//	RECT srect = RECT();
//	srect.left = ITEM_WIDTH * item;
//	srect.top = 0;
//	srect.right = srect.left + ITEM_WIDTH;
//	srect.bottom = srect.top + ITEM_HEIGHT;
//	return srect;
//}