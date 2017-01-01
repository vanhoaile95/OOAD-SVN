#ifndef QNODE_H
#define QNODE_H

#include <list>
#include "Object.h"
#include <d3d9.h>
#include <d3dx9.h>

class QNode
{
	QNode *tl, *tr, *bl, *br;
	int _NodeID;
	std::list<Object*> *_ListObjects;
	RECT _Bound;
public:
	QNode(int id, const RECT &);
	~QNode();
	int GetParentID();
	int GetID();
	void InsertObjects(std::list<Object*> *ListObjects);
	std::list<Object*> & GetListObjects();
	void AddChildNode(QNode* node);
	RECT & GetBound();
	QNode* GetChildNode(int i);
	void RemoveObj(Object *);
	void AddObj(Object*);
};
#endif
