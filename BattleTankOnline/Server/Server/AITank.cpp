#include "AITank.h"
//#include "Global.h"

AITank::AITank(P pos, BObjectName Name,int tankid) :Tank(pos, Name,tankid)
{

}
void AITank::EnableAIMode()
{
	FireFullTime = ConfigsManager::Instance()->GetIntConfig(ConfigName::AITANK_CD_TIME);
	EnableAI = true;
}
void AITank::Update()
{
	if (EnableAI)
	{
		AITimeControl += ServerTimeManager::Instance()->DeltaTime;
		AIFireControl += ServerTimeManager::Instance()->DeltaTime;

		if (AIFireControl > FireFullTime)
		{
			
			Helper::PING_UpdateGameLogic(SID, Controll("3|0"));
			AIFireControl = 0;

			//Position = InitPoint;
		}

		if (AITimeControl > TimeChangeControl
			|| (Collide.Collider == TypeBoxCollision::BlockBox && AITimeControl > 500))
		{
			TimeChangeControl = Helper::Rand(1000, 2000);
			AIControll();
		}
	}
	Tank::Update();
}

void AITank::AIControll()
{
	AITimeControl = 0;
	int currentvalue = Helper::Rand(0,4);
	int colidevalue = (int)(Collide.Direction);
	if (currentvalue == colidevalue)
	{
		currentvalue++;
	}
	if (currentvalue >= 4)
	{
		currentvalue = (int)Collision::getOppositeDirection(Collide.Direction);
	}
	string msg = "1|#direction";
	Helper::Replace(msg, "#direction", to_string(currentvalue));
	Helper::PING_UpdateGameLogic(SID,Controll(msg));
}