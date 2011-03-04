#include "Egg.h"

#include <iostream>

extern hgeResourceManager resource;

Egg::Egg(float x, float y) : Resource(x,y)
{
	myTeam = 1;
	mySprite = resource.GetSprite("egg");
	//mySprite->GetBoundingBox(myX, myY, &myRect);
	myW = myH = 75;
	myRect.Set(myX-myW/2, myY-myH/2, myX+myW/2, myY+myH/2);

	//mySprite->SetTexture(tex);
	//mySprite->SetTextureRect(0,0,160,160,false);

}

Egg::~Egg(void)
{
}
