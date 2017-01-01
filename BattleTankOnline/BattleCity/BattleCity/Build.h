#ifndef BUILD_H
#define BUILD_H

#include "Map.h"
//#include "QuadTree.h"

#include "StaticObject.h"

static Object* MakeObject(BObjectName type, P pos)
{
	Object *obj = NULL;
	switch (type)
	{
		case BASE1:
		case SMALL_BRICK:
		case BRICK:
		case LARGE_BRICK:
		case SMALL_BLOCK:
		case BLOCK:
		case LARGE_BLOCK:
		case SMALL_IRONBLOCK:
		case IRONBLOCK:
		case LARGE_IRONBLOCK:
			obj = new StaticObject(pos, type);
			break;
	default:
		obj = new StaticObject(pos, type);
		break;
	}
	return obj;
}


static map<int,Object*>* BuildListObject(Map* Map)
{
	map<int, Object*>*  ListObjects = new map<int, Object*>();

	for (list<GameObject *>::iterator i = Map->GetGameObjects().begin(); i != Map->GetGameObjects().end(); i++)
	{
		Object *obj = NULL;

		float X = (float)(*i)->GetX();
		float Y = (float)(*i)->GetY();

		BObjectName objname = (BObjectName)(*i)->GetType();
		switch (objname)
		{
		case PLAYER0:
		case PLAYER1:
		case PLAYER2:
		case PLAYER3:

		case BASE1:
		case BRICK:
		case BLOCK:
		case IRONBLOCK:
		case TREE:
		case WATER:
			obj = MakeObject(objname, P(X, Y));
			break;
		default:
			obj = MakeObject(objname, P(X, Y));
			break;
			
		}
		
		if (obj != NULL)
		{
			obj->InitSprite();
			obj->ID = (*i)->GetID();
			pair<int,Object*> p((*i)->GetID(), obj);
			ListObjects->insert(p);
		}
	}
	return ListObjects;
}
#endif