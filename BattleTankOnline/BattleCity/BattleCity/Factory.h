#ifndef FACTORY_H
#define FACTORY_H
#pragma once

enum BObjectName
{

	PLAYER0,
	PLAYER1,
	PLAYER2,
	PLAYER3,

	BASE1,
	BASE2,

	BRICK,
	SMALL_BRICK,
	LARGE_BRICK,
	BLOCK,
	SMALL_BLOCK,
	LARGE_BLOCK,
	IRONBLOCK,
	SMALL_IRONBLOCK,
	LARGE_IRONBLOCK,
	TREE,
	SMALL_TREE,
	LARGE_TREE,
	WATER,
	SMALL_WATER,
	LARGE_WATER,

	BORDER_BELOW,
	BORDER_ABOVE,
	BORDER_LEFT,
	BORDER_RIGHT,

	NONE,

	// data not in map

	BULLET,
	BACKGROUND,
	TANK_SHIELD,

	UI_TITLE_BATTLE_CITY,
	UI_TITLE_SMALL_BATTLE_CITY,
	UI_TEXT_LOADING,
	UI_TEXT_CREATE_BY_ROTS,
	UI_TEXT_SINGLEPLAYER,
	UI_TEXT_MULTIPLAYER,
	UI_TEXT_START,
	UI_TEXT_CREATE_GAME,
	UI_TEXT_JOIN_GAME,
	UI_TEXT_ID,
	UI_TEXT_WHITE_TEAM_WIN,
	UI_TEXT_GREEN_TEAM_WIN,
	UI_DIGIT,
	UI_DIGIT_YELLOW,
	UI_DOT_ROW,

	UI_SERVER_SELECT_BORDER,

	UI_TANK_WHITE,
	UI_TANK_YELLOW,
	UI_TANK_GREEN,
	UI_TANK_RED,
	UI_TANK_BOT,

	UI_SERVER_AVA,

	UI_MAIN_MENU_BTN,
	UI_BACK_MAIN_MENU_BTN,
	UI_MULTIPLAYER_BTN,
	UI_SERVER_SELECT_BTN,
	UI_MULTIPLAYER_START_BTN,
};

static bool Intersect(const RECT *rect1, const RECT *rect2)
{
	if (rect1 == NULL || rect2 == NULL)
		return false;
	if (rect1->right < rect2->left) // _rect bên trái so với obj->_rect
		return false;
	if (rect1->left > rect2->right) // _rect bên phải so với obj->_rect
		return false;
	if (rect1->bottom > rect2->top) // _rect bên trên so với obj->_rect
		return false;
	if (rect1->top < rect2->bottom) // _rect bên dưới so với obj->_rect
		return false;
	return true;
}

#endif