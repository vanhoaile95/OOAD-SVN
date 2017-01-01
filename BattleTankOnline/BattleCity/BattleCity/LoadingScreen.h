#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H
#pragma once
#include "UI.h"

class LoadingScreen : UI
{
public:
	LoadingScreen();
	~LoadingScreen();
public:
	virtual void Init();
	virtual void RenderFrame();
	virtual void UpdateWorld();

};
#endif
