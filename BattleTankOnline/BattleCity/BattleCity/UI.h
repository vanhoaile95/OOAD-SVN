#ifndef UI_H
#define UI_H
#pragma once
#include "Scene.h"
#include "UISelectButton.h"
#include <dinput.h>


using namespace std;
class UI : public Scene
{
public:
	list<UIObject*> Child;
	UIObject* ActiveChild = NULL;

	UI();
	~UI();

	virtual void Init();
	virtual void RenderFrame();
	virtual void UpdateWorld();
	virtual void UpdateData() {};

	virtual void ProcessInput(){};
	virtual void OnKeyDown(int KeyCode){};
	virtual void OnKeyUp(int KeyCode){};

	virtual void HandlerAction(SelectedValue value) {};

	void ReverseYAxis();
	SelectedValue GetValue();

};

#endif