#include "QuadTree.h"

QuadTree::QuadTree()
{
	this->_RootNode = NULL;
	this->_RectWorld = NULL;
}

QuadTree::QuadTree(QNode *root)
{
	this->_RootNode = root;
}

void QuadTree::InsertListObjInView(RECT viewport, QNode* node)
{
	if (this->_RootNode == node)
	{
		this->_ListObjInView.clear();
	}

	if (node->GetChildNode(1) ==  NULL)
	{
		if (Intersect(&node->GetBound(), &viewport))
		{
			std::list<Object *>::iterator i, j;
			for (i = node->GetListObjects().begin(); i != node->GetListObjects().end(); i++)
			{
				if ((*i)->CheckInView()) 
				{
					// kiểm tra xem obj đã tồn tại trong list chưa nếu chưa tồn tại, duyệt hết mảng
					for (j = this->_ListObjInView.begin(); j != this->_ListObjInView.end(); j++)
					{
						if ((*i) == (*j))
						{
							break;
						}
					}
					// Nếu chưa tồn tại thì thêm vào list object in view theo thứ tự từng lớp
					if (j == this->_ListObjInView.end())
					{
						InsertObjectToList(*i);
					} // end thêm list object 
					
				}
				
			}
		}
	}
	else
	{
		if (Intersect(&node->GetChildNode(1)->GetBound(), &viewport))
		{
			InsertListObjInView(viewport, node->GetChildNode(1));
		}
		if (Intersect(&node->GetChildNode(2)->GetBound(), &viewport))
		{
			InsertListObjInView(viewport, node->GetChildNode(2));
		}
		if (Intersect(&node->GetChildNode(3)->GetBound(), &viewport))
		{
			InsertListObjInView(viewport, node->GetChildNode(3));
		}
		if (Intersect(&node->GetChildNode(4)->GetBound(), &viewport))
		{
			InsertListObjInView(viewport, node->GetChildNode(4));
		}
	}
}
void QuadTree::InsertFreeObjToListView(std::list<Object*> listFreeObject)
{
	for each (Object* obj in listFreeObject)
	{
		if (obj->CheckInView() || obj->IsGlobalObject())
		{
			InsertObjectToList(obj);
		}
	}
}
void QuadTree::InsertMarioToListView(Object* _Mario)
{
	InsertObjectToList(_Mario);
}
void QuadTree::InsertObjectToList(Object *obj)
{
	std::list<Object *>::iterator j;

	if (this->_ListObjInView.size() == 0)
	{
		this->_ListObjInView.push_back(obj);
	}
	else
	{
		for (j = this->_ListObjInView.begin(); j != this->_ListObjInView.end(); ++j)
		{
			if (obj->GetDrawLayer() <= (*j)->GetDrawLayer())
			{
				this->_ListObjInView.insert(j, obj);
				break;
			}
		}
		if (j == this->_ListObjInView.end())
		{
			this->_ListObjInView.push_back(obj);
		}
	}
}
std::list<Object*> & QuadTree::GetListObjectsInView()
{
	return this->_ListObjInView;
}
QNode* QuadTree::GetRootNode()
{
	return _RootNode;
}

void QuadTree::RemoveObj(Object *obj, QNode *node)
{
	if (node->GetChildNode(1) == NULL)
	{
		node->RemoveObj(obj);
	}
	else
	{
		this->RemoveObj(obj, node->GetChildNode(1));
		this->RemoveObj(obj, node->GetChildNode(2));
		this->RemoveObj(obj, node->GetChildNode(3));
		this->RemoveObj(obj, node->GetChildNode(4));
	}
}
void QuadTree::RemoveObjInView(Object* obj)
{
	for (std::list<Object *>::iterator i = this->_ListObjInView.begin(); i != this->_ListObjInView.end(); i++)
	{
		if ((*i) == obj)
		{
			_ListObjInView.remove(*i);
			break;
		}
	}
}
void QuadTree::ReplaceObj(Object *obj, Object *obj2, QNode *node)
{
	if (node->GetChildNode(1) == NULL)
	{
		node->RemoveObj(obj);
		node->AddObj(obj2);
	}
	else
	{
		this->ReplaceObj(obj, obj2, node->GetChildNode(1));
		this->ReplaceObj(obj, obj2, node->GetChildNode(2));
		this->ReplaceObj(obj, obj2, node->GetChildNode(3));
		this->ReplaceObj(obj, obj2, node->GetChildNode(4));
	}
}
