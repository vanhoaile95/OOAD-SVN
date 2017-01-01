#include "UISelectButton.h"
#include "ClientTimeManager.h"


UISelectButton::UISelectButton(P pos, BObjectName name,bool visible) :UIObject(pos, name, visible)
{
	InitSprite();
	Value = SelectedValue::None;
}
UISelectButton::UISelectButton(P pos, BObjectName name, SelectedValue value, bool visible) : UIObject(pos, name, visible)
{
	InitSprite();
	Value = value;
}
UISelectButton::UISelectButton() : UIObject()
{
}

void UISelectButton::InitRect()
{
	UIObject::InitRect();
}

void UISelectButton::HandlerKey(ControlKey key)
{
	switch (ObjectName)
	{
	case BObjectName::UI_MAIN_MENU_BTN:
		if (Value == SelectedValue::SinglePlayerMode) {
			Value = SelectedValue::MultiPlayerMode;
			Position.X = 368;
			Position.Y = 514;
		}
		else {
			Value = SelectedValue::SinglePlayerMode;
			Position.X = 368;
			Position.Y = 433;
		}
		break;
	case BObjectName::UI_MULTIPLAYER_BTN:
		if (Value == SelectedValue::CreateGame) {
			Value = SelectedValue::JoinGameMode;
			Position.X = 391;
			Position.Y = 231;
		}
		else {
			Value = SelectedValue::CreateGame;
			Position.X = 391;
			Position.Y = 168;
		}
		break;
	case BObjectName::UI_MULTIPLAYER_START_BTN:
	case BObjectName::UI_BACK_MAIN_MENU_BTN:
		Position.X = 462;
		Position.Y = 636;
		break;
	default:
		break;
	}
	ReverseYAxis();
}

void UISelectButton::UpdateWorld()
{
	switch (ObjectName)
	{
	case BObjectName::UI_MAIN_MENU_BTN:
		RECTTime += ClientTimeManager::Instance()->DeltaTime;
		if (RECTTime > 1000) RECTTime = 0;
		RECTIndex = (RECTTime < 500) ? 0 : 1;
		break;
	default:
		break;
	}
}
