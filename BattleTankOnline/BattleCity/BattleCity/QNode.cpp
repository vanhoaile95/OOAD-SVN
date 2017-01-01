#include "QNode.h"

QNode::QNode(int id, const RECT &rect)
{
	this->tl = NULL;
	this->tr = NULL;
	this->bl = NULL;
	this->br = NULL;
	this->_NodeID = id;
	this->_Bound = rect;
}

int QNode::GetID()
{
	return this->_NodeID;
}

int QNode::GetParentID()
{
	return (int)this->_NodeID/8;
}

std::list<Object*> & QNode::GetListObjects()
{
	return *this->_ListObjects;
}

void QNode::InsertObjects(std::list<Object*> *ListObjects)
{
	this->_ListObjects = ListObjects;
}

void QNode::AddChildNode(QNode* node)
{
	int num = node->GetID() % 8;
	switch (num)
	{
	case 1:
		this->tl = node;
		break;
	case 2:
		this->tr = node;
		break;
	case 3:
		this->bl = node;
		break;
	case 4:
		this->br = node;
	}
}

QNode::~QNode()
{
}

RECT & QNode::GetBound()
{
	return this->_Bound;
}

QNode* QNode::GetChildNode(int i)
{
	switch (i)
	{
	case 1:
		return this->tl;
	case 2:
		return this->tr;
	case 3:
		return this->bl;
	case 4:
		return this->br;
	default:
		return this->tl;
	}
}

void QNode::RemoveObj(Object *obj)
{
	_ListObjects->remove(obj);
}
void QNode::AddObj(Object *obj)
{
	_ListObjects->push_back(obj);
}