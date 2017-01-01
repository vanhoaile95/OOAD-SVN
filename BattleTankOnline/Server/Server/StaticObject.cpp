#include "StaticObject.h"

StaticObject::StaticObject(P pos,BObjectName name): Object(pos,name)
{
	//InitSize();
}
StaticObject::StaticObject(P pos) : Object(pos)
{
	//InitSprite();
	//InitRect();
}
void StaticObject::Update()
{
	
}
string StaticObject::Controll( string msg)
{
	return "";
}
bool StaticObject::HandlerCollision(Collision collision, int sid)
{
	return true;
}

bool StaticObject::HandlerBulletCollision(Collision collision, int tankid, int tanktype, int sid)
{
	if (HP < ConfigsManager::Instance()->GetIntConfig(ConfigName::UNBREAK_HP))
	{
		HP -= 1;
		if (HP <= 0)
		{
			IsDisappear = true;
			enableCollision = false;

			string updateData = "#id+#x+#y+#command+#dir+#time";
			Helper::Replace(updateData, "#id", to_string(-ID));
			Helper::Replace(updateData, "#command", "10");
			Helper::Replace(updateData, "#time", to_string(ServerTimeManager::Instance()->GetServerTime()));
			Helper::PING_UpdateGameLogic(sid, updateData);
		}
	}
	return true;
}
