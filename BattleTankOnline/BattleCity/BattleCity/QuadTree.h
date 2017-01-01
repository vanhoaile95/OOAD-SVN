#ifndef QUADTREE_H
#define QUADTREE_H

#include "QNode.h"
#include <map>
#include "Factory.h"
#

enum MQuadTreeType
{
	DRAW,
	UPDATE
};

class QuadTree
{
	QNode* _RootNode;
	std::list<Object*> _ListObjInView;
	RECT* _RectWorld;
public:
	QuadTree();
	QuadTree(QNode *root);

	void InsertListObjInView(RECT viewport, QNode* node);
	void InsertFreeObjToListView(std::list<Object*> listFreeObject);
	void InsertMarioToListView(Object * _Mario);

	void InsertObjectToList(Object * obj);
	std::list<Object*> & GetListObjectsInView();
	QNode* GetRootNode();
	void RemoveObj(Object *, QNode *);
	void RemoveObjInView(Object * obj);
	void ReplaceObj(Object *obj, Object *obj2, QNode *node);
};
#endif