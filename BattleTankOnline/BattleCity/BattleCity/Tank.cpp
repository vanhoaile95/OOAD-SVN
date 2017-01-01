#include "Tank.h"
#include "Global.h"
#include "GameScore.h"

Tank::Tank(P pos, BObjectName Name,int tankid) :DynamicObject(pos,Name)
{
	ShieldSprite = TextureRectManager::GetInstance()->GetRECTWithName(BObjectName::TANK_SHIELD);
	CurrentTankColor = (Color) (int) ObjectName;
	Type = TypeBoxCollision::TankBox;
	enableCollision = true;

	TankID = tankid;
	Bullet = new TankBullet(pos,CurrentDirection,tankid,0);
	ChangeType((TankType) 0);
	InitPoint = pos;
	Bullet->InitSprite();
	Mission* mission = (Mission*) Global::Instance()->MissionManager->CurrentScene;
	mission->_listBullets.push_back(Bullet);
}
void Tank::Start()
{
	ShieldTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::INIT_SHIELD_TIME);
}
void Tank::Fire()
{
	string msg = "1+#dir+#x+#y";
	Helper::Replace(msg, "#dir",to_string((int) CurrentDirection));
	Helper::Replace(msg, "#dir", to_string(Position.X));
	Helper::Replace(msg, "#dir", to_string(Position.Y));
	Bullet->Controll(msg);
}

void Tank::Draw()
{
	Bullet->Draw();
	DynamicObject::Draw();
	if (ShieldTime > 0)
	{
		if ((ShieldTime / 200) % 2 == 0)
		{
			Sprite->Draw(ShieldSprite[0], Position + P(Size.X/2,Size.Y/2) - P(32,32));
		}
		else
		{
			Sprite->Draw(ShieldSprite[1], Position + P(Size.X / 2, Size.Y / 2) - P(32, 32));
		}
	}
}
void Tank::InitRect()
{
	SpriteRect = TextureRectManager::GetInstance()->GetTankRECT(CurrentTankType, CurrentTankColor);
	Size = P(52,52);
}
void Tank::Update()
{
	Collide.Reset();
	DynamicObject::Update();
	if (Bullet->State != BulletState::Idle)
	{
		Bullet->Update();
	}
	if (ShieldTime > 0)
	{
		ShieldTime -= ClientTimeManager::Instance()->DeltaTime;
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


	int timeadd = (Collide.Direction != CollisionDirection::CollideNone)
		? 0 : (int)FrameVelocity.GetMagnitude();

	RECTTime += timeadd;
	if (RECTTime >= 20) RECTTime = 0;
	int index = (RECTTime < 10) ? 0 : 1;
	RECTIndex = (int) CurrentDirection * 2 + index;

	if (Bullet->State != BulletState::Idle)
	{
		Bullet->LateUpdate();
	}
}

bool Tank::HandlerCollision(Collision collision)
{
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
	if (command != "")
	{
		Controll(command);
	}

	return true;
}

bool Tank::HandlerBulletCollision(Collision collision, int tankid, int tanktype)
{
	if (TankID != tankid)
	{
		if (Helper::Offline())
		{
			HP -= 1;
			if (HP <= 0)
			{
				GameScore::Instance()->SinglePlayerInfo->Kill[tanktype] += 1;
				HP = ConfigsManager::Instance()->GetIntConfig(ConfigName::TANK_HP);
				Position = InitPoint;
			}
		}
		else
		{
			//GameScore::Instance()->MulTiplayerInfo[tankid]->Kill += 1;
			//GameScore::Instance()->MulTiplayerInfo[TankID]->Death += 1;
		}



	}

	return true;
}
int Tank::Controll(P pos,string msg, int ping)
{
	Position = pos;
	Direction dir = Direction::Left;
	vector<string> decode = StringHelper::split(msg, "|");
	if (!decode[0].compare("1")) // Move
	{
		dir = (Direction) atoi(decode[1].c_str());
		switch (dir)
		{
		case Up:
			ObjectVelocity = P(0.0f, MaxSpeed);
			break;
		case Left:
			ObjectVelocity = P(-MaxSpeed, 0.0f);
			break;
		case Down:
			ObjectVelocity = P(0.0f, -MaxSpeed);
			break;
		case Right:
			ObjectVelocity = P(MaxSpeed, 0.0f);
			break;
		default:
			break;
		}
		CurrentDirection = dir;
		pos += (ObjectVelocity * ping);
	}
	else if (!decode[0].compare("0"))  // stop
	{
		pos += (ObjectVelocity * ping);
		dir = (Direction) atoi(decode[1].c_str());
		switch (dir)
		{
		case Up:
			if (ObjectVelocity.Y > 0) ObjectVelocity.Y = 0;
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
	else if (!decode[0].compare("3"))  // fire
	{
		pos += (ObjectVelocity * ping);
		P center = P(Position.X + Size.X / 2, Position.Y + Size.Y / 2);

		string command = "#command+#dir+#x+#y";
		Helper::Replace(command, "#command", "3");
		Helper::Replace(command, "#dir", to_string((int) CurrentDirection));
		Helper::Replace(command, "#x", to_string(center.X));
		Helper::Replace(command, "#y", to_string(center.Y));
		Bullet->Controll(command);
	}
	else if (!decode[0].compare("4"))  //getDamage
	{
		Bullet->Controll("4");
	}
	else if (!decode[0].compare("5"))  //getDamage
	{
		int bulletid = Helper::GetIntFromString(decode[1]) - 1;
		Mission* Current = (Mission*) Global::Instance()->MissionManager->CurrentScene;
		Current->Tanks[bulletid]->Bullet->Controll("4");
		HP -= Current->Tanks[bulletid]->Bullet->Damage;
		ShieldTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::DAMAGE_SHIELD_TIME);
	}
	else if (!decode[0].compare("6"))  // Die
	{
		Mission* Current = (Mission*) Global::Instance()->MissionManager->CurrentScene;
		int killerid = Helper::GetIntFromString(decode[1]) - 1;

		Current->Tanks[killerid]->Exp += Bounty;
		Current->Tanks[killerid]->CheckAndUpgrade();
		Current->Tanks[killerid]->Bullet->Controll("4");

		ChangeType(CurrentTankType);

		if (killerid < Helper::MaxClient())
		{
			Current->MultiplayerHud->TankInfo[killerid]->Kill->UpdateValue(GameScore::Instance()->MulTiplayerInfo[killerid]->Kill);
			GameScore::Instance()->MulTiplayerInfo[killerid]->Kill += 1;
		}
		if (TankID < Helper::MaxClient())
		{
			GameScore::Instance()->MulTiplayerInfo[TankID]->Death += 1;
			Current->MultiplayerHud->TankInfo[TankID]->Death->UpdateValue(GameScore::Instance()->MulTiplayerInfo[TankID]->Death);
		}
		ShieldTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::INIT_SHIELD_TIME);
		//Position = InitPoint;
	}
	return 1;
}
void Tank::UpdateTankRECT()
{
	if ( TankID == -1 || TankID >= Helper::MaxClient()) return;

	Mission* Current = (Mission*) Global::Instance()->MissionManager->CurrentScene;
	Current->MultiplayerHud->TankInfo[TankID]->TankRect = SpriteRect[6];
}
int Tank::Controll(string msg)
{
	Direction dir = Direction::Left;
	vector<string> decode = StringHelper::split(msg, "|");
	if (!decode[0].compare("1")) // Move
	{
		if (Helper::GetPing() < 200)
		{
			dir = (Direction) atoi(decode[1].c_str());
			switch (dir)
			{
			case Up:
			ObjectVelocity = P(0.0f, MaxSpeed);
			break;
			case Left:
			ObjectVelocity = P(-MaxSpeed, 0.0f);
			break;
			case Down:
			ObjectVelocity = P(0.0f, -MaxSpeed);
			break;
			case Right:
			ObjectVelocity = P(MaxSpeed, 0.0f);
			break;
			default:
			break;
			}
			CurrentDirection = dir;
		}
	}
	else if (!decode[0].compare("0"))  // stop
	{
		if (Helper::GetPing() < 200)
		{
			dir = (Direction) atoi(decode[1].c_str());
			switch (dir)
			{
			case Up:
				if (ObjectVelocity.Y > 0) ObjectVelocity.Y = 0;
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
	}
	else if (!decode[0].compare("3"))  // stop
	{
		P center = P(Position.X + Size.X / 2, Position.Y + Size.Y / 2);
		if (Bullet->State == BulletState::Idle)
		{
			string command = "#command+#dir+#x+#y";
			Helper::Replace(command, "#command", "3");
			Helper::Replace(command, "#dir", to_string((int) CurrentDirection));
			Helper::Replace(command, "#x", to_string(center.X));
			Helper::Replace(command, "#y", to_string(center.Y));
			if (Helper::Offline())
			{
				Bullet->Controll(command);
			}
			else
			{
				Helper::SEND_Controll(msg);
			}
		}
		else return 0;
	}
	return 1;
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
	InitRect();
	ShieldTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::INIT_SHIELD_TIME);
	UpdateTankRECT();
}

