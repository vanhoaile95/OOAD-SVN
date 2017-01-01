#ifndef MAIN_MENU
#define MAIN_MENU
#pragma once
#include "UI.h"

class MainMenu : public UI
{
public:
	MainMenu();
	~MainMenu();
public:
	virtual void Init();
	virtual void RenderFrame();
	virtual void UpdateWorld();

	virtual void ProcessInput() {};
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
#endif
