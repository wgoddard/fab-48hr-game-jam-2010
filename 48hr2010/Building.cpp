#include "Building.h"

Building::Building(float x, float y) : Minion(x, y)
{
	mySpeed = 0.0f;
	myEngageWidth = 700.0f;
	myMaxSlots = 1000;
	myW = 50;
	myH = 700;
	myDamage = 0;
	myCurrentHP = 100;
	myMaxHP = 100;

	myY += 100;

	myRect.Set(myX-myW/2, myY-myH/2, myX+myW/2, myY+myH/2);
}

Building::~Building(void)
{
}
