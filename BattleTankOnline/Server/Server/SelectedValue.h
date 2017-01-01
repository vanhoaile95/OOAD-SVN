#ifndef SELECTED_VALUE_H
#define SELECTED_VALUE_H
#pragma once

enum SelectedValue {
	GameInit,
	GameRun,
	GameEnd,


	None,
	SinglePlayerMode,
	MultiPlayerMode,

	CreateGame,
	JoinGameMode,
	WaitingForClient,

	SelectServer,
	WaitingForStartGame,
	StartGame,
};
#endif