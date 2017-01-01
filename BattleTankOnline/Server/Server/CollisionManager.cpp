#include "CollisionManager.h"
#include "Algorithm.h"


Box CollisionManager::GetSweptBroadphaseBox(Box b)
{
	Box broadphasebox;
	broadphasebox.Position.X = (b.FrameVelocity.X > 0) ? b.Position.X : b.Position.X + b.FrameVelocity.X;
	broadphasebox.Position.Y = (b.FrameVelocity.Y > 0) ? b.Position.Y : b.Position.Y + b.FrameVelocity.Y;
	broadphasebox.Size.X = (b.FrameVelocity.X > 0) ? b.FrameVelocity.X + b.Size.X : b.Size.X - b.FrameVelocity.X;
	broadphasebox.Size.Y = (b.FrameVelocity.Y > 0) ? b.FrameVelocity.Y + b.Size.Y : b.Size.Y - b.FrameVelocity.Y;
	return broadphasebox;
}

Collision CollisionManager::CollisionCheckWithObjectBox(Box BoxdObject, Box BoxObject)
{
	BoxdObject.FrameVelocity.X -= BoxObject.FrameVelocity.X;
	BoxdObject.FrameVelocity.Y -= BoxObject.FrameVelocity.Y;
	BoxObject.FrameVelocity.X = 0;
	BoxObject.FrameVelocity.Y = 0;

	//float moveX, moveY;
	Box broadphasebox = GetSweptBroadphaseBox(BoxdObject);
	Collision collision;

	if (AABBCheck(broadphasebox, BoxObject))
	{
		collision.CollisionTime = MySweptAABB(BoxdObject, BoxObject, collision.Direction);

		if (collision.Direction == CollisionDirection::CollideNone)
		{
			Orientation(BoxdObject, BoxObject, collision.CollisionTime);
		}
	}
	else
	{

	}
	return collision;
}
bool CollisionManager::AABBCheck(Box b1, Box b2) {
	return !(b1.Position.X + b1.Size.X < b2.Position.X - 1 || b1.Position.X > b2.Position.X + b2.Size.X || b1.Position.Y + b1.Size.Y < b2.Position.Y - 1 || b1.Position.Y > b2.Position.Y + b2.Size.Y);
}

float CollisionManager::MySweptAABB(Box b1, Box b2, CollisionDirection &result)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	if (b1.FrameVelocity.X > 0.0f)
	{
		xInvEntry = b2.Position.X - (b1.Position.X + b1.Size.X);
		xInvExit = (b2.Position.X + b2.Size.X) - b1.Position.X;
	}
	else
	{
		xInvEntry = (b2.Position.X + b2.Size.X) - b1.Position.X;
		xInvExit = b2.Position.X - (b1.Position.X + b1.Size.X);
	}
	if (b1.FrameVelocity.Y > 0.0f)
	{
		yInvEntry = b2.Position.Y - (b1.Position.Y + b1.Size.Y);
		yInvExit = (b2.Position.Y + b2.Size.Y) - b1.Position.Y;
	}
	else
	{
		yInvEntry = (b2.Position.Y + b2.Size.Y) - b1.Position.Y;
		yInvExit = b2.Position.Y - (b1.Position.Y + b1.Size.Y);
	}
	float xEntry, yEntry;
	float xExit, yExit;
	if (b1.FrameVelocity.X == 0.0f)
	{
		xEntry = -(std::numeric_limits<float>::max)();
		xExit = (std::numeric_limits<float>::max)();
	}
	else
	{
		xEntry = xInvEntry / b1.FrameVelocity.X;
		xExit = xInvExit / b1.FrameVelocity.X;
	}
	if (b1.FrameVelocity.Y == 0.0f)
	{
		yEntry = -(std::numeric_limits<float>::max)();
		yExit = (std::numeric_limits<float>::max)();
	}
	else
	{
		yEntry = yInvEntry / b1.FrameVelocity.Y;
		yExit = yInvExit / b1.FrameVelocity.Y;
	}
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);
	if (entryTime > exitTime || xEntry<0.0f && yEntry<0.0f || xEntry>1.0f || yEntry>1.0f)
	{
		result = CollisionDirection::CollideNone;
		return 1.0f;
	}
	else
	{
		result = Orientation(b1, b2, entryTime);
		return entryTime;
	}
}

CollisionDirection CollisionManager::Orientation(Box boxmain, Box b2, float entryTime)
{
	/*boxmain.X += boxmain.X *entryTime;
	boxmain.Y += boxmain.Y *entryTime;
	b2.X += b2.X *entryTime;
	b2.Y += b2.Y *entryTime;*/
	b2.FrameVelocity -= boxmain.FrameVelocity;
	boxmain.FrameVelocity = 0;



	int a = 4, b = 4;
	if (boxmain.Position.Y + boxmain.Size.Y <= b2.Position.Y)
	{
		a = 0;
	}
	if (boxmain.Position.Y >= b2.Position.Y + b2.Size.Y)
	{
		if (a == 4) a = 1; else b = 1;
	}
	if (boxmain.Position.X >= b2.Position.X + b2.Size.X)
	{
		if (a == 4) a = 2; else b = 2;
	}
	if (boxmain.Position.X + boxmain.Size.X <= b2.Position.X)
	{
		if (a == 4) a = 3; else b = 3;
	}
	if (b == 4)
		return (CollisionDirection) a;
	else
	{
		if (a == 0 || a == 1)
		{
			if (b2.FrameVelocity.Y != 0)
			{
				return (CollisionDirection) b;
			}
			else
			{
				return CollisionDirection::CollideNone;
			}
		}
		else if (a == 2 || a == 3)
		{
			if (b2.FrameVelocity.X != 0)
			{
				return (CollisionDirection) b;
			}
			else
			{
				return CollisionDirection::CollideNone;
			}
		}

	}

	return CollisionDirection::CollideNone;
}
CollisionDirection CollisionManager::getOppositeDirection(CollisionDirection direction)
{
	switch (direction)
	{
	case CollisionDirection::CollideAbove:
		return CollisionDirection::CollideBelow;
	case CollisionDirection::CollideBelow:
		return CollisionDirection::CollideAbove;
	case CollisionDirection::CollideLeft:
		return CollisionDirection::CollideRight;
	case CollisionDirection::CollideRight:
		return CollisionDirection::CollideLeft;
	default:
		return CollisionDirection::CollideNone;
	}
}

void CollisionManager::CollisionCheckObject(Object *dObjectA, Object *ObjectB, int sid)
{

	Box *Abox = &dObjectA->GetBox();
	Box *Bbox = &ObjectB->GetBox();


	if ((!Abox->enableCollision || !Bbox->enableCollision)
		|| (Abox->Type == TypeBoxCollision::NoCollision && Bbox->Type == TypeBoxCollision::NoCollision))
	{
		return;
	}
	Collision collisionA = CollisionCheckWithObjectBox(*Abox, *Bbox);
	Collision collisionB;

	// Va chạm xảy ra bên phải A thì xảy ra bên trái B
	// Nếu va chạm xảy ra bên trái A thì Object A phải xử lí việc quy định khi có va chạm xảy ra bên phải B
	// Tương tự với 3 trường hợp còn lại
	if (collisionA.CollisionTime < 1.0f)
	{
		collisionA.Collider = Bbox->Type;

		collisionB.CollisionTime = collisionA.CollisionTime;
		collisionB.Collider = Abox->Type;
		collisionB.Direction = getOppositeDirection(collisionA.Direction);
		// Xu ly Ngoai Le

		// End Xu ly ngoai le
		dObjectA->HandlerCollision(collisionA, sid);
		ObjectB->HandlerCollision(collisionB, sid);
	}
}

void CollisionManager::CollisionCheckWithBulletObject(Object *dObjectA, TankBullet *ObjectB, int sid)
{
	Box *Abox = &dObjectA->GetBox();
	Box *Bbox = &ObjectB->GetBox();

	if ((!Abox->enableCollision || !Bbox->enableCollision)
		|| (Abox->Type == TypeBoxCollision::NoCollision && Bbox->Type == TypeBoxCollision::NoCollision))
	{
		return;
	}
	Collision collisionA = CollisionCheckWithObjectBox(*Abox, *Bbox);
	Collision collisionB;

	//if (Abox->Type == TankBox && Bbox->Type == BulletBox)
	//{
	//	int i = 13;
	//}

	// Va chạm xảy ra bên phải A thì xảy ra bên trái B
	// Nếu va chạm xảy ra bên trái A thì Object A phải xử lí việc quy định khi có va chạm xảy ra bên phải B
	// Tương tự với 3 trường hợp còn lại
	if (collisionA.CollisionTime < 1.0f)
	{
		collisionA.Collider = Bbox->Type;

		collisionB.CollisionTime = collisionA.CollisionTime;
		collisionB.Collider = Abox->Type;
		collisionB.Direction = getOppositeDirection(collisionA.Direction);
		// Xu ly Ngoai Le

		// End Xu ly ngoai le
		dObjectA->HandlerBulletCollision(collisionA, ObjectB->TankID, ObjectB->TankType,sid);
		ObjectB->HandlerCollision(collisionB,sid);
	}
}


