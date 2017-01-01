#include "Global.h"

Global* Global::_instance = 0;

Global* Global::Instance()
{
	if (0 == _instance)
	{
		_instance = new Global();
	}
	return _instance;
}

Global::Global()
{
}
Mission* Global::GetServer(int sid)
{
	auto search = GameLogic->find(sid);
	if (search != GameLogic->end()) {
		return search->second->CurrentScene;
	}
	return NULL;
}

