#ifndef GAME_INFOR_H
#define GAME_INFOR_H
#include <stdlib.h>
#include "

class VariablesHandler
{
private:

	static VariablesHandler* _instance;
	VariablesHandler();
	~VariablesHandler();
public:
	static VariablesHandler* Instance();
};

#endif