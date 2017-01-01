#include "Collision.h"

CollisionDirection Collision::getOppositeDirection(CollisionDirection direction)
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