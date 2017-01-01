#define POINT_STRUCT
#ifdef POINT_STRUCT
#pragma once

class P
{
public:
	float X;
	float Y;
	P(float x = 0, float y = 0);
	P(long x, long y);
	P(int x, int y);

	P operator+(const P& obj);
	P operator-(const P & obj);
	P operator*(const P& obj);
	P operator*(const int& obj);
	P operator*(const float& obj);
	void operator=(const P& obj);
	void operator=(const int& obj);
	void operator=(const float& obj);
	void operator+=(const P& obj);
	void operator-=(const P & obj);
	float GetMagnitude();

};
#endif //POINT_STRUCT