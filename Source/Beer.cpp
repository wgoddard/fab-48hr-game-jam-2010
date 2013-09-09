#include "Beer.h"

extern hgeResourceManager resource;

Beer::Beer(float x, float y) : Resource(x,y)
{
	myTeam = 0;
	mySprite = resource.GetSprite("beer");
	//mySprite->GetBoundingBox(myX, myY, &myRect);
	myW = myH = 75;
	myRect.Set(myX-myW/2, myY-myH/2, myX+myW/2, myY+myH/2);
}

Beer::~Beer(void)
{
}
