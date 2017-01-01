#ifndef COLLISION_H
#define COLLISION_H

enum TypeBoxCollision
{
	NoCollision = 0, // Không xử lý khi có va chạm
	TankBox,
	BulletBox,
	BlockBox,
	WaterBox,
	TreeBox,
	EnemyBox,
};
enum CollisionDirection
{
	CollideAbove,
	CollideBelow,
	CollideLeft,
	CollideRight,
	CollideNone,
};
struct Collision
{
	float CollisionTime = 1.0f; // cho biết khi nào xảy ra va chạm
	TypeBoxCollision Collider = TypeBoxCollision::NoCollision; // Cho biết object đang va chạm với loại đối tượng nào
	CollisionDirection Direction = CollisionDirection::CollideNone; // Hướng va chạm
	void Reset()
	{
		CollisionTime = 1.0f;
		Collider = TypeBoxCollision::NoCollision;
		Direction = CollisionDirection::CollideNone;
	}
	bool isBlockObject()
	{
		switch (Collider)
		{
		case BlockBox:
			return true;
		default:
			return false;
		}
	}
	static CollisionDirection getOppositeDirection(CollisionDirection direction);
};

#endif



