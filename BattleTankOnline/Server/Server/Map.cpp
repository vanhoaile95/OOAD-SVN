#include "Map.h"
#include <string>

int GameObject::GetID()
{
	return this->_ID;
}

void GameObject::SetPosition(float X, float Y)
{
	_X = (int)X;
	_Y = (int)Y;
}

int GameObject::GetX()
{
	return this->_X;
}

int GameObject::GetY()
{
	return this->_Y; 
}

int GameObject::GetType()
{
	return this->_Type;
}

void GameObject::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();
	_ID = atoi(xml.GetAttrib("ID").c_str());
	_Type = atoi(xml.GetAttrib("Type").c_str());
	_X = atoi(xml.GetAttrib("X").c_str());
	_Y = atoi(xml.GetAttrib("Y").c_str());
}



void GameObjects::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();
	if (xml.GetElemContent() != "")
	{
		xml.IntoElem();
		GameObject *_GameObject;
		while (xml.FindElem("GameObject"))
		{
			_GameObject = new GameObject();
			_GameObject->Deserialize(xml.GetSubDoc().c_str());
			_ListGameObjects.push_back(_GameObject);
		}
	}
}

list<GameObject *> & GameObjects::GetGameObjects()
{
	return _ListGameObjects;
}



void Node::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();
	_Height = atoi(xml.GetAttrib("Height").c_str());
	_Width = atoi(xml.GetAttrib("Width").c_str());
	_X = atoi(xml.GetAttrib("X").c_str());
	_Y = atoi(xml.GetAttrib("Y").c_str());
	_ID = atoi(xml.GetAttrib("ID").c_str());
	xml.IntoElem();

	GameObjects *_GameObjects;
	while (xml.FindElem("GameObjects"))
	{
		_GameObjects = new GameObjects();
		_GameObjects->Deserialize(xml.GetSubDoc().c_str());
		_ListGameObjects = _GameObjects->GetGameObjects();
	}
}

list<GameObject *> & Node::GetGameObjects()
{
	return _ListGameObjects;
}

int Node::GetID()
{
	return _ID;
}

int Node::GetX()
{
	return _X;
}

int Node::GetY()
{
	return _Y;
}

int Node::GetWidth()
{
	return _Width;
}

int Node::GetHeight()
{
	return _Height;
}



void Nodes::Deserialize(const char *noidungcon)
{
	CMarkup xml(noidungcon);
	xml.FindElem();
	xml.IntoElem();

	list<GameObject *>::iterator i, j;
	pair<Node *, list<GameObject *> *> *p;
	Node *_Node;
	while (xml.FindElem("Node"))
	{
		_Node = new Node();
		_Node->Deserialize(xml.GetSubDoc().c_str());
		_ListNodes.push_back(_Node);
		
		p = new pair<Node *, list<GameObject *> *>(_Node, &_Node->GetGameObjects());
		_ObjectsInNodes.insert(*p);
		
		// thêm object vào list _ListObjects
		for (i = _Node->GetGameObjects().begin(); i != _Node->GetGameObjects().end(); i++)
		{
			j = _ListGameObjects.begin();
			while (j != _ListGameObjects.end()) // kiểm tra xem j đã tồn tại trong list chưa
			{
				if ((*j)->GetID() == (*i)->GetID())
					break;
				j++;
			}
			if (j == _ListGameObjects.end())
			{
				_ListGameObjects.push_back(*i);
			}
		}
	}
}

list<Node *> & Nodes::GetNodes()
{
	return _ListNodes;
}

list<GameObject *> & Nodes::GetGameObjects()
{
	return _ListGameObjects;
}

map<Node *, list<GameObject *> *> & Nodes::GetObjectsInNodes()
{
	return _ObjectsInNodes;
}



void SaveData::Deserialize(const char *tenfile)
{
	CMarkup xml;
	xml.Load(tenfile);
	xml.FindElem();
	xml.IntoElem();
	while (xml.FindElem())
	{
		if (xml.GetTagName() == "Width")
		{
			this->_Width = atoi(xml.GetData().c_str());
		}

		if (xml.FindElem("Height"))
		{
			this->_Height = atoi(xml.GetData().c_str());
		}

		if (xml.FindElem("Nodes"))
		{
			_Nodes.Deserialize(xml.GetSubDoc().c_str());

			_ListNodes = _Nodes.GetNodes();
			_ListGameObjects = _Nodes.GetGameObjects();
			_ObjectsInNodes = _Nodes.GetObjectsInNodes();
		}
	}
}

int SaveData::GetWidth()
{
	return this->_Width;
}

int SaveData::GetHeight()
{
	return this->_Height;
}

list<Node *> & SaveData::GetNodes()
{
	return _ListNodes;
}

list<GameObject *> & SaveData::GetGameObjects()
{
	return _ListGameObjects;
}

map<Node *, list<GameObject *> *> & SaveData::GetObjectsInNodes()
{
	return _ObjectsInNodes;
}



Map::Map(const char *filename)
{
	_Filename = filename;
}

void Map::LoadMap()
{
	char file[300];
	char tmpFilename[50];
	
	// Draw
	strcpy(tmpFilename, _Filename.c_str());
	strcat(tmpFilename, ".xml");

	GetCurrentDirectoryA(sizeof(file), file);
	file[sizeof(file) - 1] = '\0';
	strcat(file, "\\Map\\");
	strcat(file, tmpFilename);

	_data.Deserialize(file);
	
	_ListNodes = _data.GetNodes();
	_ListGameObjects = _data.GetGameObjects();
	_ObjectsInNodes = _data.GetObjectsInNodes();



	// Update
	/*strcpy(tmpFilename, _Filename.c_str());
	strcat(tmpFilename, "Update.xml");

	GetCurrentDirectoryA(sizeof(file), file);
	file[sizeof(file) - 1] = '\0';
	strcat(file, "\\Mission\\");
	strcat(file, tmpFilename);

	_updateData.Deserialize(file);
	
	_Update_ListNodes = _updateData.GetNodes();
	_Update_ListGameObjects = _updateData.GetGameObjects();
	_Update_ObjectsInNodes = _updateData.GetObjectsInNodes();*/
}

int Map::GetWidth()
{
	return _data.GetWidth();
}

int Map::GetHeight()
{
	return _data.GetHeight();
}

list<Node *> & Map::GetNodes()
{
	return _ListNodes;
}

list<GameObject *> & Map::GetGameObjects()
{
	return _ListGameObjects;
}

map<Node *, list<GameObject *> *> & Map::GetObjectsInNodes()
{
	return _ObjectsInNodes;
}

//list<Node *> & Map::GetUpdateNodes()
//{
//	return _Update_ListNodes;
//}
//
//list<GameObject *> & Map::GetUpdateGameObjects()
//{
//	return _Update_ListGameObjects;
//}
//
//map<Node *, list<GameObject *> *> & Map::GetUpdateObjectsInNodes()
//{
//	return _Update_ObjectsInNodes;
//}

