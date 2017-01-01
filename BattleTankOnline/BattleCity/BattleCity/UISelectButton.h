#ifndef UI_SELECT_BUTTON_H
#define UI_SELECT_BUTTON_H
#pragma once
#include "UIObject.h"

class UISelectButton :public UIObject
{
public:

	UISelectButton(P pos, BObjectName name,bool visible = true);
	UISelectButton(P pos, BObjectName name, SelectedValue value = SelectedValue::None, bool visible = true);
	UISelectButton();

	void InitRect();
	virtual void HandlerKey(ControlKey key);
	virtual void UpdateWorld();

};
#endif