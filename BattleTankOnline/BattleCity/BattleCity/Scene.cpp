#include "Scene.h"
Scene::Scene()
{
	WaitingForResponse = false;
}
Scene::~Scene()
{

}

SelectedValue Scene::GetValue()
{
	return SelectedValue::None;
}


