#include "Box.h"

Box::Box(P pos, P size, P v)
{
	this->Position = pos;
	this->Size = size;
	this->FrameVelocity = v;
	this->enableCollision = false;
	this->Type = NoCollision;
}
Box::Box(P pos)
{
	this->Position = pos;
	this->Size = P(0, 0);
	this->FrameVelocity = P(0, 0);
	this->enableCollision = false;
	Type = NoCollision;
}
Box::Box()
{
	this->Position = P(0, 0);
	this->Size = P(0, 0);
	this->FrameVelocity = P(0, 0);
	this->enableCollision = false;
	Type = NoCollision;
}