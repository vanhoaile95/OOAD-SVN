#include "Tank.h"
#include "Global.h"

Tank::Tank(P pos, BObjectName Name, int tankid) :DynamicObject(pos, Name)
{
	Index = to_string((int) Name);
	Size = P(52, 52);
	CurrentTankColor = (Color) (int) ObjectName;
	Type = TypeBoxCollision::TankBox;
	enableCollision = true;
	TankID = tankid;
	Bullet = new TankBullet(pos, CurrentDirection, tankid, 0);
	ChangeType((TankType) 0);
	InitPoint = pos;
}
void Tank::Start()
{
	ShieldTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::INIT_SHIELD_TIME);
}
void Tank::Update()
{
	ServerMsg = "";
	DynamicObject::Update();
	if (Bullet->State != BulletState::Idle)
	{
		Bullet->Update();
	}
	if (ShieldTime > 0)
	{
		ShieldTime -= ServerTimeManager::Instance()->DeltaTime;
	}
}

void Tank::LateUpdate()
{
	DynamicObject::LateUpdate();

	if (CollisionTime.X < 1.0f)
	{
		ObjectVelocity.X = 0;
		FrameVelocity.X = 0;
	}
	if (CollisionTime.Y < 1.0f)
	{
		ObjectVelocity.Y = 0;
		FrameVelocity.Y = 0;
	}


	if (ServerMsg != "")
	{
		Helper::PING_UpdateGameLogic(SID,Controll(ServerMsg));
	}
	if (Bullet->State != BulletState::Idle)
	{
		Bullet->LateUpdate();
	}
}
bool Tank::HandlerCollision(Collision collision, int sid)
{
	SID = sid;
	string command = "";

	if (collision.Collider == TypeBoxCollision::TreeBox
		|| collision.Collider == TypeBoxCollision::NoCollision)
	{

		return true;
	}

	Collide = collision;

	switch (collision.Direction)
	{
	case CollisionDirection::CollideAbove:
		if (FrameVelocity.Y > 0)
			CollisionTime.Y = Collide.CollisionTime;
		command = "0|0";
		break;
	case CollisionDirection::CollideLeft:
		if (FrameVelocity.X < 0)
			CollisionTime.X = Collide.CollisionTime;
		command = "0|1";
		break;
	case CollisionDirection::CollideBelow:
		if (FrameVelocity.Y < 0)
			CollisionTime.Y = Collide.CollisionTime;
		command = "0|2";
		break;
	case CollisionDirection::CollideRight:
		if (FrameVelocity.X > 0)
			CollisionTime.X = Collide.CollisionTime;
		command = "0|3";
		break;
	default:
		break;
	}
	ServerMsg = command;
}
bool Tank::HandlerBulletCollision(Collision collision, int tankid, int tanktype, int sid)
{
	SID = sid;
	if (ShieldTime > 0) return false;

	if ((tankid + TankID) % 2 != 0)
	{
		HP -= ConfigsManager::Instance()->GetTankConfig(tanktype,TankConfigName::BulletDamage);
		
		string command = "5";
		if (HP <= 0)
		{
			Global::Instance()->GetServer(sid)->Tanks[tankid]->Exp += Bounty;
			Global::Instance()->GetServer(sid)->Tanks[tankid]->CheckAndUpgrade();
			ChangeType(CurrentTankType);

			Position = InitPoint;

			command = "6";
			ShieldTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::INIT_SHIELD_TIME);
		}
		else
		{
			ShieldTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::DAMAGE_SHIELD_TIME);
		}
		string updateData = "#tank+#x+#y+#command+#dir+#time";
		Helper::Replace(updateData, "#tank", to_string(TankID + 1));
		Helper::Replace(updateData, "#x", to_string(Position.X));
		Helper::Replace(updateData, "#y", to_string(Position.Y));
		Helper::Replace(updateData, "#command", command);
		Helper::Replace(updateData, "#dir", to_string(tankid + 1));
		Helper::Replace(updateData, "#time", to_string(ServerTimeManager::Instance()->GetServerTime()));
		Helper::PING_UpdateGameLogic(SID, updateData);
	}
	return false;
}
void Tank::Fire()
{
	string msg = "1+#dir+#x+#y";
	Helper::Replace(msg, "#dir", to_string((int)CurrentDirection));
	Helper::Replace(msg, "#dir", to_string(Position.X));
	Helper::Replace(msg, "#dir", to_string(Position.Y));
	Bullet->Controll(msg);
}


string Tank::Controll(string msg)
{
	// msg = 0|0
	Direction dir = Direction::Left;
	vector<string> decode = StringHelper::split(msg,"|");
	if (!decode[0].compare("1")) // Move
	{
		dir = (Direction)atoi(decode[1].c_str());
		switch (dir)
		{
		case Up:
			ObjectVelocity = P(0.0f,MaxSpeed);
			break;
		case Left:
			ObjectVelocity = P(-MaxSpeed, 0.0f);
			break;
		case Down:
			ObjectVelocity = P(0.0f,-MaxSpeed);
			break;
		case Right:
			ObjectVelocity = P(MaxSpeed, 0.0f);
			break;
		default:
			break;
		}
		CurrentDirection = dir;
	}
	else if (!decode[0].compare("0"))  // stop
	{
		dir = (Direction) atoi(decode[1].c_str());
		switch (dir)
		{
		case Up:
			if(ObjectVelocity.Y > 0) ObjectVelocity.Y = 0;
			break;
		case Down:
			if (ObjectVelocity.Y < 0) ObjectVelocity.Y = 0;
			break;
		case Left:
			if (ObjectVelocity.X < 0) ObjectVelocity.X = 0;
			break;
		case Right:
			if (ObjectVelocity.X > 0) ObjectVelocity.X = 0;
			break;
		default:
			ObjectVelocity = 0;
			break;
		}
	}
	else if (!decode[0].compare("3"))  // stop
	{
		P center = P(Position.X + Size.X / 2, Position.Y + Size.Y / 2);
		if (Bullet->State == BulletState::Idle)
		{
			string msg = "#command+#dir+#x+#y";
			Helper::Replace(msg, "#command", "3");
			Helper::Replace(msg, "#dir", to_string((int)CurrentDirection));
			Helper::Replace(msg, "#x", to_string(center.X));
			Helper::Replace(msg, "#y", to_string(center.Y));
			Bullet->Controll(msg);
		}
	}
	string updateData = "#tank+#x+#y+#command+#dir+#time";
	Helper::Replace(updateData, "#tank", to_string(TankID + 1));
	Helper::Replace(updateData, "#x", to_string(Position.X));
	Helper::Replace(updateData, "#y", to_string(Position.Y));
	Helper::Replace(updateData, "#command", decode[0]);
	Helper::Replace(updateData, "#dir", to_string((int)dir));
	Helper::Replace(updateData, "#time", to_string(ServerTimeManager::Instance()->GetServerTime()));
	return updateData;
}

void Tank::CheckAndUpgrade()
{
	if (Exp >= ExpToUpgrade && ExpToUpgrade > 0)
	{
		ChangeType((TankType) ((int) CurrentTankType + 1));
	}
}

void Tank::ChangeType(TankType type)
{
	CurrentTankType = type;
	Exp = 0;
	HP = ConfigsManager::Instance()->GetTankConfig(type, TankConfigName::HP);
	MaxSpeed = ConfigsManager::Instance()->GetTankConfig(type, TankConfigName::MaxSpeed);
	Bounty = ConfigsManager::Instance()->GetTankConfig(type, TankConfigName::Bounty);
	ExpToUpgrade = ConfigsManager::Instance()->GetTankConfig(type, TankConfigName::ExpToUpgrade);
	Bullet->ChangeType(type);
	ShieldTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::DAMAGE_SHIELD_TIME);
}

