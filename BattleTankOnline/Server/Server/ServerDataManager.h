#define SERVER_DATA_MANAGER_H
#ifdef SERVER_DATA_MANAGER_H
#pragma once
#include "Helper.h"

class ServerDataManager
{
private:
	static ServerDataManager *_instance;
public:
	int PushIndex[2],PopIndex[2];
	int MaxDataBufferSize;
	int DataCount[2];
	char* DataBuffer[2];
	bool head = true;

	int CurrentBuffer = 0; // 0:0  1:1

	static ServerDataManager* Instance();
	ServerDataManager();
	~ServerDataManager();

	void PushBack(char * buffer, int length);
	char * PopFront();

	void Run();

};
#endif // SERVER_DATA_MANAGER_H