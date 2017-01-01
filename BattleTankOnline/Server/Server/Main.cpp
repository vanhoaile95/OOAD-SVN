#include "ServerManager.h"
#include "ServerGameLogic.h"
#include <windows.h>

#define MAX_THREADS 3


DWORD WINAPI EncodeDecodeProgress(__in LPVOID lpParameter)
{
	printf("Server Run In New Thread:%d !!!\n", GetCurrentThreadId());
	srand(time((time_t)NULL));
	ServerDataManager::Instance()->Run();

	printf("End Server Thread !!\n");
	return 0;
}
DWORD WINAPI ServerProgress(__in LPVOID lpParameter)
{
	printf("Server Progress Run In New Thread:%d !!!\n", GetCurrentThreadId());
	srand(time((time_t)NULL));
	ServerManager::Instance()->ServerInit();
	ServerManager::Instance()->ServerRun();
	ServerManager::Instance()->ServerEnd();

	printf("End Server Thread !!\n");
	return 0;
}
DWORD WINAPI GameWordProgress(__in LPVOID lpParameter)
{
	printf("GameWord Run In New Thread:%d !!!\n", GetCurrentThreadId());
	srand(time((time_t)NULL));
	ServerGameLogic::Instance()->Init();
	ServerGameLogic::Instance()->Run();
	ServerGameLogic::Instance()->End();
	printf("End Game Word Thread !!\n");
	return 0;
}



int main(int argc, char **argv)
{
	using namespace std;
	HANDLE  hThreadArray[MAX_THREADS];
	DWORD EDProgressThreedID;
	hThreadArray[0] = CreateThread(NULL, 0, EncodeDecodeProgress, 0, 0, &EDProgressThreedID);
	if (hThreadArray[0] == NULL)
	{
		printf("Encode Decode Thread Fail:%d !!!\n", EDProgressThreedID);
		ExitProcess(3);
	}
	DWORD ServerProgressThreedID;
	hThreadArray[1] = CreateThread(NULL, 0, ServerProgress, 0, 0, &ServerProgressThreedID);
	if (hThreadArray[1] == NULL)
	{
		printf("Server Thread Fail:%d !!!\n", ServerProgressThreedID);
		ExitProcess(3);
	}
	DWORD GameWordProgressThreedID;
	hThreadArray[2] = CreateThread(0, 0, GameWordProgress, 0, 0, &GameWordProgressThreedID);
	if (hThreadArray[2] == NULL)
	{
		printf("GameWord Thread Fail:%d !!!\n", ServerProgressThreedID);
		ExitProcess(3);
	}
	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
	for (int i = 0; i<MAX_THREADS; i++)
	{
		CloseHandle(hThreadArray[i]);
	}
	return 0;
}

