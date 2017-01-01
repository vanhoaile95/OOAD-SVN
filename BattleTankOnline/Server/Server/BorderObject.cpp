#include "BorderObject.h"


BorderObject::BorderObject(BObjectName name) : StaticObject(P(0,0),name)
{
	//InitSprite();
	InitRect();

}
void BorderObject::InitRect()
{
	switch (ObjectName)
	{
	case BORDER_BELOW:
		Size = P(28 * 32, 32);
		Position = P(0, -4);
		break;
	case BORDER_ABOVE:
		Size = P(28 * 32, 32);
		Position = P(0,668);
		break;
	case BORDER_LEFT:
		Size = P(32, 32 * 22);
		Position = P(0, -4);
		break;
	case BORDER_RIGHT:
		Size = P(32, 32 * 22);
		Position = P(864, -4);
		break;
	default:
		break;
	}
}