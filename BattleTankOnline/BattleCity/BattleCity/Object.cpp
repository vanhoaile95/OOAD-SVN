#include "Object.h"


Object::Object(P pos) :Box(pos)
{
	this->ObjectVelocity = P(0, 0);
	this->ObjectName = BObjectName::NONE;
	IsDisappear = false;
	DrawLayer = 0;
}
Object::Object(P pos, BObjectName name) :Box(pos)
{
	this->ObjectVelocity = P(0, 0);
	this->ObjectName = name;
	IsDisappear = false;
	DrawLayer = 0;
	RECTTimeInterval = 300;
	

	switch (name)
	{
	case BASE1:
	case BASE2:
		Size = P(64, 64);
		break;
	case BRICK:
		Size = P(64, 64);
		break;
	case SMALL_BRICK:
		Size = P(32, 32);
		break;
	case LARGE_BRICK:
		Size = P(128, 128);
		break;
	case BLOCK:
		Size = P(64, 64);
		break;
	case SMALL_BLOCK:
		Size = P(32, 32);
		break;
	case LARGE_BLOCK:
		Size = P(128, 128);
		break;
	case IRONBLOCK:
		Size = P(64, 64);
		break;
	case SMALL_IRONBLOCK:
		Size = P(32, 32);
		break;
	case LARGE_IRONBLOCK:
		Size = P(128, 128);
		break;
	case TREE:
		Size = P(64, 64);
		break;
	case SMALL_TREE:
		Size = P(32, 32);
		break;
	case LARGE_TREE:
		Size = P(128, 128);
		break;
	case WATER:
		Size = P(64, 64);
		break;
	case SMALL_WATER:
		Size = P(32, 32);
		break;
	case LARGE_WATER:
		Size = P(128, 128);
		break;
	case BULLET:
		Size = P(12, 16);
		break;
	default:
		Size = P(64, 64);
		break;
	}
	switch (name)
	{
	case BASE1:
	case BASE2:
		Type = TypeBoxCollision::BlockBox;
		HP = ConfigsManager::Instance()->GetIntConfig(ConfigName::TANK_HP);
		enableCollision = true;
		break;
	case BRICK:
	case SMALL_BRICK:
	case LARGE_BRICK:
		Type = TypeBoxCollision::BlockBox;
		enableCollision = true;
		HP = ConfigsManager::Instance()->GetIntConfig(ConfigName::BRICK_HP);
		break;
	case BLOCK:
	case SMALL_BLOCK:
	case LARGE_BLOCK:
	case IRONBLOCK:
	case SMALL_IRONBLOCK:
	case LARGE_IRONBLOCK:
	case BORDER_ABOVE:
	case BORDER_BELOW:
	case BORDER_LEFT:
	case BORDER_RIGHT:
		Type = TypeBoxCollision::BlockBox;
		enableCollision = true;
		HP = ConfigsManager::Instance()->GetIntConfig(ConfigName::UNBREAK_HP);
		break;
	case TREE:
	case SMALL_TREE:
	case LARGE_TREE:
		Type = TypeBoxCollision::TreeBox;
		enableCollision = false;
		HP = ConfigsManager::Instance()->GetIntConfig(ConfigName::UNBREAK_HP);
		break;
	case WATER:
	case SMALL_WATER:
	case LARGE_WATER:
		Type = TypeBoxCollision::WaterBox;
		enableCollision = true;
		HP = ConfigsManager::Instance()->GetIntConfig(ConfigName::UNBREAK_HP);
		break;
		break;
	case BULLET:
		Type = TypeBoxCollision::BulletBox;
		enableCollision = true;
		HP = ConfigsManager::Instance()->GetIntConfig(ConfigName::UNBREAK_HP);
		break;
	default:
		Type = TypeBoxCollision::NoCollision;
		enableCollision = false;
		HP = ConfigsManager::Instance()->GetIntConfig(ConfigName::UNBREAK_HP);
		break;
	}


}
Box Object::GetBox()
{ 
	return *this; 
}
void Object::ReverseYAxis()
{
	Position.Y = SCREEN_HEIGHT - Position.Y + Size.Y;
}
bool Object::IsUpdateObject()
{
	switch (this->ObjectName)
	{
	case BObjectName::PLAYER0:
	case BObjectName::PLAYER1:
	case BObjectName::PLAYER2:
	case BObjectName::PLAYER3:
		return true;
	default:
		return false;
	}
}
int Object::InitDrawLayer()
{
	switch (this->ObjectName)
	{
	case BObjectName::PLAYER0:
	case BObjectName::PLAYER1:
	case BObjectName::PLAYER2:
	case BObjectName::PLAYER3:
		return 10;
	case BObjectName::BASE1:
	case BObjectName::BRICK:
	case BObjectName::BLOCK:
	case BObjectName::IRONBLOCK:
	case BObjectName::TREE:
	case BObjectName::WATER:
		return 3;
	case BObjectName::BULLET:
		return 9;
	case BObjectName::BACKGROUND:
		return 0;
	default:
		return 30;
	}
}
int Object::Controll(P pos, string msg,int ping)
{
	return 1;
}