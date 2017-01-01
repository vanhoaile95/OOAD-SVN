#ifndef SCENE_H
#define SCENE_H
#pragma once
#include "SelectedValue.h"

class Scene
{
public:
	bool WaitingForResponse;
	Scene();
	~Scene();
	virtual SelectedValue GetValue();
	SelectedValue Value;

	virtual void Init() {};
	virtual void UpdateWorld() {};
	virtual void RenderFrame() {};
	virtual void Reset() {};

	virtual void ProcessInput() {};
	virtual void OnKeyDown(int KeyCode) {};
	virtual void OnKeyUp(int KeyCode) {};

	virtual void HandlerAction(SelectedValue value) {};
};
#endif
