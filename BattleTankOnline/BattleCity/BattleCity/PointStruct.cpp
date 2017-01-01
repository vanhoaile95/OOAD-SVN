#include "PointStruct.h"
#include <math.h>
P::P(float x, float y)
{
	X = x; Y = y;
}
P::P(long x, long y)
{
	X = (float)x; Y = (float)y;
}
P::P(int x, int y)
{
	X = (float) x; Y = (float)y;
}

P P::operator+(const P & obj)
{
	P tmp_obj = *this;
	tmp_obj.X += obj.X;
	tmp_obj.Y += obj.Y;
	return tmp_obj;
}
P P::operator-(const P & obj)
{
	P tmp_obj = *this;
	tmp_obj.X -= obj.X;
	tmp_obj.Y -= obj.Y;
	return tmp_obj;
}

P P::operator*(const P & obj)
{
	P tmp_obj = *this;
	tmp_obj.X *= obj.X;
	tmp_obj.Y *= obj.Y;
	return tmp_obj;
}

P P::operator*(const int & obj)
{
	P tmp_obj = *this;
	tmp_obj.X *= (float)obj;
	tmp_obj.Y *= (float)obj;
	return tmp_obj;
}

P P::operator*(const float & obj)
{
	P tmp_obj = *this;
	tmp_obj.X *= obj;
	tmp_obj.Y *= obj;
	return tmp_obj;
}

void P::operator=(const P & obj)
{
	(*this).X = obj.X;
	(*this).Y = obj.Y;
}

void P::operator=(const int & obj)
{
	(*this).X = (float)obj;
	(*this).Y = (float)obj;
}

void P::operator=(const float & obj)
{
	(*this).X = obj;
	(*this).Y = obj;
}

void P::operator+=(const P & obj)
{
	(*this).X += obj.X;
	(*this).Y += obj.Y;
}
void P::operator-=(const P & obj)
{
	(*this).X -= obj.X;
	(*this).Y -= obj.Y;
}

float P::GetMagnitude()
{
	return (float)sqrt(X*X+Y*Y);
}
