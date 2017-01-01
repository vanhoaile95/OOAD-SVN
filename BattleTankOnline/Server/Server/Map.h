#ifndef MAP_H
#define MAP_H

#include <list>
#include <map>
#include "Markup.h"
#include <Windows.h>

using namespace std;

class SaveData; // Dữ liệu lưu trong toàn file xml
class Nodes; //
class Node; //
class GameObjects; // 
class GameObject; // 


class GameObject
{
private:
	int _ID;
	int _X;
	int _Y;
	int _Type;
public:
	void Deserialize(const char *);
	int GetID();
	void SetPosition(float X,float Y);
	int GetX();
	int GetY();
	int GetType();
};


class GameObjects
{
private:
	list<GameObject *> _ListGameObjects;
public:
	void Deserialize(const char *);
	list<GameObject *> & GetGameObjects();
};


class Node
{
private:
	int _Width;
	int _Height;
	int _ID;
	int _X;
	int _Y;
	list<GameObject *> _ListGameObjects;

public:
	void Deserialize(const char *);
	list<GameObject *> & GetGameObjects();
	int GetID();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
};


class Nodes
{
private:
	list<Node *> _ListNodes;
	list<GameObject *> _ListGameObjects;
	map<Node *, list<GameObject *> *> _ObjectsInNodes;
public:
	void Deserialize(const char *);
	list<Node *> & GetNodes();
	list<GameObject *> & GetGameObjects();
	map<Node *, list<GameObject *> *> & GetObjectsInNodes();
};


class SaveData
{
private:
	int _Width; // chiều rộng map
	int _Height; // chiều cao map
	Nodes _Nodes;

	list<Node *> _ListNodes;
	list<GameObject *> _ListGameObjects;
	map<Node *, list<GameObject *> *> _ObjectsInNodes;
public:
	void Deserialize(const char *);
	int GetWidth();
	int GetHeight();
	list<Node *> & GetNodes();
	list<GameObject *> & GetGameObjects();
	map<Node *, list<GameObject *> *> & GetObjectsInNodes();
};


class Map
{
public:
	string _Filename;
private:
	SaveData _data;
	list<Node *> _ListNodes;
	list<GameObject *> _ListGameObjects, _ListStartPosition;
	map<Node *, list<GameObject *> *> _ObjectsInNodes;
public:
	Map(const char *filename);
	void LoadMap();
	int GetWidth();
	int GetHeight();
	list<Node *> & GetNodes();
	list<GameObject *> & GetGameObjects();
	map<Node *, list<GameObject *> *> & GetObjectsInNodes();

	/*list<Node *> & GetUpdateNodes();
	list<GameObject *> & GetUpdateGameObjects();
	map<Node *, list<GameObject *> *> & GetUpdateObjectsInNodes();*/
};

#endif