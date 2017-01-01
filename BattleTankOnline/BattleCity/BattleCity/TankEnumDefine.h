#ifndef TANK_ENUM_DEFINE_H
#define TANK_ENUM_DEFINE_H
#pragma once

enum Color
{
	White,
	Yellow,
	Green,
	Red,
};

enum Direction
{
	Up,
	Left,
	Down,
	Right,
};

enum TankType
{
	LightTank1,
	LightTank2,
	DetroyerTank1,
	DetroyerTank2,
	RapidTank1,
	ArmoredVehicle,
	HeavyTank1,
	HeavyTank2,
};

enum TankState
{
	Init,
	Operating,
	Destroy,
};

#endif //TANK_ENUM_DEFINE_H