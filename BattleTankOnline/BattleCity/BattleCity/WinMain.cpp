#ifndef WIN_MAIN
#define WIN_MAIN
#pragma once
#include "Game.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#define MAX_THREADS 3
bool ClientInit = false;

DWORD WINAPI ClientSENDProgress(__in LPVOID lpParameter)
{
	printf("Client Service Run In New Thread: %d\n", GetCurrentThreadId());
	srand(time((time_t)NULL));
	ClientManager::Instance()->Init();
	ClientInit = true;
	ClientManager::Instance()->SendLoop();
	ClientManager::Instance()->End();
	printf("End Client Service Thread\n");
	return 0;
}
DWORD WINAPI ClientRECVProgress(__in LPVOID lpParameter)
{
	printf("Client Service Run In New Thread: %d\n", GetCurrentThreadId());
	srand(time((time_t)NULL));
	while (!ClientInit)
	{
		Sleep(8);
	}
	ClientManager::Instance()->RecvLoop();
	printf("End Client Service Thread\n");
	return 0;
}
DWORD WINAPI GameProgress(__in LPVOID lpParameter)
{
	printf("GameWord Run In New Thread : %d\n", GetCurrentThreadId());
	srand(time((time_t)NULL));
	(HINSTANCE) lpParameter;

	Game *game = new Game((HINSTANCE) lpParameter);
	game->Init();
	game->Run();
	game->End();
	printf("End Game Word Thread\n");
	return 0;
}

void InitConsole()
{
	int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;
	AllocConsole();
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	InitConsole();

	HANDLE  hThreadArray[MAX_THREADS];
	DWORD SENDProgressThreedID;
	hThreadArray[0] = CreateThread(NULL, 0, ClientSENDProgress, 0, 0, &SENDProgressThreedID);
	if (hThreadArray[0] == NULL)
	{
		printf("SEND Thread Fail:%d !!!\n", SENDProgressThreedID);
		ExitProcess(3);
	}
	DWORD RECVProgressThreedID;
	hThreadArray[1] = CreateThread(NULL, 0, ClientRECVProgress, 0, 0, &RECVProgressThreedID);
	if (hThreadArray[1] == NULL)
	{
		printf("RECV Thread Fail:%d !!!\n", RECVProgressThreedID);
		ExitProcess(3);
	}


	DWORD GameWordProgressThreedID;
	hThreadArray[2] = CreateThread(0, 0, GameProgress, hInstance, 0, &GameWordProgressThreedID);
	if (hThreadArray[2] == NULL)
	{
		printf("GameWord Thread Fail:%d !!!\n", GameWordProgressThreedID);
		ExitProcess(3);
	}


	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
	for (int i = 0; i<MAX_THREADS; i++)
	{
		CloseHandle(hThreadArray[i]);
	}
	return 0;
}


#endif