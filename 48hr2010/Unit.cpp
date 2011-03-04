#include "Unit.h"
#include "hgeRectExt.h"

Unit::Unit(float x, float y)// : myX(x), myY(y)
{
	myX = x;
	myY = y;
	myValue = 1;

}

Unit::~Unit(void)
{
}

void Unit::Render(bool renderSprite)
{
	if(renderSprite)
		mySprite->Render(myX, myY);

	//Render the bounding box
	//hgeRectExt a(myRect);
	//a.Render();
	
}
