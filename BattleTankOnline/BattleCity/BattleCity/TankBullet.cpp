#include "TankBullet.h"
#include "Global.h"

TankBullet::TankBullet(P pos, Direction dir, int tankid,int tanktype) : DynamicObject(pos, BObjectName::BULLET)
{
	State = BulletState::Idle;
	enableCollision = false;
	ID = -1;
	TankID = tankid;
	TankType = tanktype;
}

int TankBullet::Controll(P pos, string msg, int ping)
{
	enableCollision = true;
	return 0;
}

int TankBullet::Controll(string msg)
{
	State = BulletState::Firing;
	// string msg = "#command+#dir+#x+#y";
	vector<string> decode = StringHelper::split(msg,"+");
	if (decode[0] == "3")
	{
		BulletDirection = (Direction) atoi(decode[1].c_str());
		RECTIndex = (int) BulletDirection;
		Position = P(Helper::GetFloatFromString(decode[2]) - Size.X / 2, Helper::GetFloatFromString(decode[3]) - Size.Y / 2);

		switch (BulletDirection)
		{
		case Up:
			ObjectVelocity = P(0.0f, MaxSpeed);
			Size = P(12, 16);
			break;
		case Left:
			ObjectVelocity = P(-MaxSpeed, 0.0f);
			Size = P(16, 12);
			break;
		case Down:
			ObjectVelocity = P(0.0f, -MaxSpeed);
			Size = P(12, 16);
			break;
		case Right:
			ObjectVelocity = P(MaxSpeed, 0.0f);
			Size = P(16, 12);
			break;
		default:
			break;
		}
		State = BulletState::Firing;
		enableCollision = true;
	}
	else if (decode[0] == "4")
	{
		ObjectVelocity = 0;
		FrameVelocity = 0;
		State = BulletState::Idle;
		enableCollision = false;
	}
	return 1;
}
bool TankBullet::HandlerCollision(Collision collision)
{
	if (collision.Collider == TypeBoxCollision::TreeBox
		|| collision.Collider == TypeBoxCollision::NoCollision
		|| collision.Collider == TypeBoxCollision::WaterBox)
	{
		return true;
	}
	Controll("4");

	return true;
}
void TankBullet::LateUpdate()
{
	DynamicObject::LateUpdate();
	if (Position.X > SCREEN_WIDTH + 4 || Position.X < -4 || Position.Y > SCREEN_HEIGHT + 4 || Position.Y < - 4)
	{
		Controll("4");
	}
}
void TankBullet::Draw()
{
	if(State != BulletState::Idle)
		DynamicObject::Draw();
}
void TankBullet::ChangeType(int type)
{
	TankType = type;
	Damage = ConfigsManager::Instance()->GetTankConfig(type, TankConfigName::BulletDamage);
	MaxSpeed = ConfigsManager::Instance()->GetTankConfig(type, TankConfigName::BulletMaxSpeed);
}