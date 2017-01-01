#include "TextureRectManager.h"

TextureRectManager* TextureRectManager::Instance = NULL;

TextureRectManager::TextureRectManager()
{
}
TextureRectManager::~TextureRectManager()
{
}

TextureRectManager* TextureRectManager::GetInstance()
{
	if (Instance == NULL)
	{
		Instance = new TextureRectManager();
	}
	return Instance;
}

RECT TextureRectManager::GetBlockRect()
{
	return GetRect(P(1024,64),P(32,32));
}
RECT* TextureRectManager::GetRECTWithName(BObjectName name, int *RECTLength)
{
	RECT* result;
	switch (name)
	{
	case BASE1:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[2];
		result[0] = GetRect(P(1024,384), P(64,64));
		result[1] = GetRect(P(1088,384), P(64,64));
		return result;
	case BASE2:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[2];
		result[0] = GetRect(P(1024, 448), P(64, 64));
		result[1] = GetRect(P(1088, 448), P(64, 64));
		return result;
	case BULLET:
		if (RECTLength != NULL) *RECTLength = 4;
		result = new RECT[4];
		result[0] = GetRect(P(1412, 0), P(12, 16));
		result[1] = GetRect(P(1424, 4), P(16, 12));
		result[2] = GetRect(P(1440, 4), P(12, 16));
		result[3] = GetRect(P(1452, 4), P(16, 12));
		return result;
	case SMALL_BRICK:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1024, 0), P(32, 32));
		return result;
	case BRICK:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1024,0), P(64,64));
		return result;
	case LARGE_BRICK:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1024, 0), P(128,128));
		return result;
	case SMALL_BLOCK:
	case BORDER_ABOVE:
	case BORDER_BELOW:
	case BORDER_LEFT:
	case BORDER_RIGHT:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1152, 0), P(32, 32));
		return result;
	case BLOCK:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1152, 0), P(64, 64));
		return result;
	case LARGE_BLOCK:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1152, 0), P(128, 128));
		return result;
	case SMALL_TREE:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1280, 0), P(32, 32));
		return result;
	case TREE:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1280, 0), P(64, 64));
		return result;
	case LARGE_TREE:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1280, 0), P(128, 128));
		return result;
	case SMALL_IRONBLOCK:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1024,256), P(32, 32));
		return result;
	case IRONBLOCK:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1024, 256), P(64, 64));
		return result;
	case LARGE_IRONBLOCK:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(1024, 256), P(128, 128));
		return result;
	case SMALL_WATER:
		if (RECTLength != NULL) *RECTLength = 3;
		result = new RECT[3];
		result[0] = GetRect(P(1024,128), P(32, 32));
		result[1] = GetRect(P(1152,128), P(32, 32));
		result[2] = GetRect(P(1280,128), P(32, 32));
		return result;
	case WATER:
		if (RECTLength != NULL) *RECTLength = 3;
		result = new RECT[3];
		result[0] = GetRect(P(1024, 128), P(64, 64));
		result[1] = GetRect(P(1152, 128), P(64, 64));
		result[2] = GetRect(P(1280, 128), P(64, 64));
		return result;
	case LARGE_WATER:
		if (RECTLength != NULL) *RECTLength = 3;
		result = new RECT[3];
		result[0] = GetRect(P(1024, 128), P(128, 128));
		result[1] = GetRect(P(1152, 128), P(128, 128));
		result[2] = GetRect(P(1280, 128), P(128, 128));
		return result;
	case TANK_SHIELD:
		if (RECTLength != NULL) *RECTLength = 2;
		result = new RECT[2];
		result[0] = GetRect(P(1025, 800), P(64, 64));
		result[1] = GetRect(P(1089, 800), P(64, 64));
		return result;

		//UI
	case UI_TITLE_BATTLE_CITY:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 0), P(752, 272));
		return result;
	case UI_TITLE_SMALL_BATTLE_CITY:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(451,354), P(349, 28));
		return result;
	case UI_TEXT_LOADING:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 272), P(520, 50));
		return result;
	case UI_TEXT_CREATE_BY_ROTS:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 322), P(413, 25));
		return result;
	case UI_TEXT_SINGLEPLAYER:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 347), P(354, 25));
		return result;
	case UI_TEXT_MULTIPLAYER:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 372), P(324, 25));
		return result;
	case UI_TEXT_START:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(658, 272), P(142, 25));
		return result;
	case UI_TEXT_CREATE_GAME:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 397), P(320, 26));
		return result;
	case UI_TEXT_JOIN_GAME:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(320, 397), P(262, 26));
		return result;
	case UI_TEXT_WHITE_TEAM_WIN:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 580), P(550, 34));
		return result;
	case UI_TEXT_GREEN_TEAM_WIN:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 614), P(550, 34));
		return result;
	case UI_BACK_MAIN_MENU_BTN:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(0, 648), P(220, 21));
		return result;
	case UI_TEXT_ID:
		if (RECTLength != NULL) *RECTLength = 2;
		result = new RECT[2];
		result[0] = GetRect(P(695, 297), P(105, 26));
		result[1] = GetRect(P(695, 322), P(105, 26));
		return result;
	case UI_DOT_ROW:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(438, 382), P(362, 8));
		return result;
	case UI_SERVER_SELECT_BORDER:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(530, 506), P(146, 72));
		return result;
	case UI_DIGIT:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[22];
		for (int i = 0; i < 10; i++)
		{
			result[i] = GetRect(P(i * 26, 423), P(26, 26));
			result[10+i] = GetRect(P(i * 26, 448), P(26, 26));
		}
		result[20] = GetRect(P(10 * 26, 423), P(26, 26));
		result[21] = GetRect(P(10 * 26, 448), P(26, 26));
		return result;
	case UI_TANK_BOT:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[1];
		result[0] = GetRect(P(616, 454), P(60, 52));
		return result;
	case UI_TANK_WHITE:
		if (RECTLength != NULL) *RECTLength = 2;
		result = new RECT[2];
		result[0] = GetRect(P(676, 390), P(60, 52));
		result[1] = GetRect(P(740, 390), P(60, 52));
		return result;
	case UI_TANK_YELLOW:
	case UI_MAIN_MENU_BTN:
	case UI_MULTIPLAYER_BTN:
	case UI_MULTIPLAYER_START_BTN:
		if (RECTLength != NULL) *RECTLength = 2;
		result = new RECT[2];
		result[0] = GetRect(P(696, 442), P(52, 52));
		result[1] = GetRect(P(748, 442), P(52, 52));
		return result;
	case UI_TANK_GREEN:
		if (RECTLength != NULL) *RECTLength = 2;
		result = new RECT[2];
		result[0] = GetRect(P(676, 494), P(60, 52));
		result[1] = GetRect(P(740, 494), P(60, 52));
		return result;
	case UI_TANK_RED:
		if (RECTLength != NULL) *RECTLength = 2;
		result = new RECT[2];
		result[0] = GetRect(P(680, 546), P(60, 52));
		result[1] = GetRect(P(744, 546), P(60, 52));
		return result;
	case UI_SERVER_AVA:
		if (RECTLength != NULL) *RECTLength = 1;
		result = new RECT[2];
		result[0] = GetRect(P(612, 390), P(64, 64));
		return result;
	}
	if (RECTLength != NULL) *RECTLength = 1;
	result = new RECT[1];
	result[0] = GetRect(P(1152, 0), P(64, 64));
	return result;
}

RECT* TextureRectManager::GetTankRECT(TankType type,Color color)
{
	P position = P(32, 32); // anchor 0.5 0.5
	P colorOffset;
	switch (color)
	{
	case Yellow:
		colorOffset = P(0, 0);
		break;
	case White:
		colorOffset = P(512, 0);
		break;
	case Green:
		colorOffset = P(0,512);
		break;
	case Red:
		colorOffset = P(512, 512);
		break;
	}
	P tankTypeOffset = P(0,(int)type * 64);
	position += (tankTypeOffset + colorOffset);

	P size;
	P* offset;

	switch (type)
	{
	case LightTank1:
		size = P(52,52);
		offset = new P[4]{ P(-2,2),P(2,-2),P(-2,-2),P(-2,-2) };
		break;
	case LightTank2:
		size = P(52, 64);
		offset = new P[4]{ P(-2,0),P(0,-2) ,P(-2,0) ,P(0,-2) };
		break;
	case DetroyerTank1:
		size = P(52, 60);
		offset = new P[4]{ P(-2,-2),P(-2,-2),P(-2,2) ,P(2,-2) };
		break;
	case DetroyerTank2:
		size = P(56, 60);
		offset = new P[4]{ P(0,-2),P(-2,0) ,P(0,-2) ,P(2,0) };
		break;
	case RapidTank1:
		size = P(52, 60);
		offset = new P[4]{ P(-2,-2),P(-2,2),P(-2,2) ,P(2,-2) };
		break;
	case ArmoredVehicle:
		size = P(52, 60);
		offset = new P[4]{ P(-2,-2),P(-2,2),P(-2,2) ,P(2,-2) };
		break;
	case HeavyTank1:
		size = P(52, 60);
		offset = new P[4]{ P(-2,-2),P(-2,2),P(-6,-2) ,P(2,-2) };
		break;
	default: //HeavyTank2
		size = P(52, 60);
		offset = new P[4]{ P(-2,-2),P(-2,-2),P(-2,-2) ,P(-2,-2) };
		break;
	}

	return GetTankRECTWithCondition(position,size,offset);
}

RECT* TextureRectManager::GetTankRECTWithCondition(P pos,P size,P* offset)
{
	RECT* result = new RECT[8];
	for (int i = 0; i < 8; i++)
	{
		P mid = P(pos.X + 64 * i + offset[i/2].X, pos.Y + offset[i/2].Y);
		result[i] = RECT();
		P realsize = ((i / 2) % 2 != 0) ? P(size.Y, size.X) : size;
		result[i].left = (LONG) (mid.X - (int)realsize.X / 2);
		result[i].top = (LONG) (mid.Y - (int)realsize.Y / 2);
		result[i].right = (LONG) (mid.X + (int)realsize.X / 2);
		result[i].bottom = (LONG) (mid.Y + (int)realsize.Y / 2);
	}
	return result;
}

RECT TextureRectManager::GetRect(P pos, P size)
{
	RECT Des;
	Des.left = (LONG)pos.X;
	Des.top = (LONG)pos.Y;
	
	Des.right = (LONG)(pos.X + size.X);
	Des.bottom = (LONG)(pos.Y + size.Y);
	return Des;
}
//RECT TextureRectManager::GetTankRect(int TankType, P size)
//{
//	RECT Des;
//	Des.left = (LONG)pos.X;
//	Des.top = (LONG)pos.Y;
//
//	Des.right = (LONG)(pos.X + size.X);
//	Des.bottom = (LONG)(pos.Y + size.Y);
//	return Des;
//}
