#include "Raptor.h"

extern hgeResourceManager resource;
extern std::vector<Minion*> minions;

Raptor::Raptor(float x, float y) : Minion(x,y)
{
	myW = myH = 80;
	myRect.Set(myX-myW/2, myY-myH/2, myX+myW/2, myY+myH/2);

	mySprite = resource.GetSprite("raptor");
	myTeam = 1;
	myTargetBox = hgeRect(myX, myY - myEngageWidth/2, myX + (300 * (myTeam == 0 ? -1 : 1)), myY + myEngageWidth/2);

	aniWalkNum = 4;
	aniAttackNum = 3;
	aniDeathNum = 4;

	//aniWalkSpeed[0] = 0.08f;
	//aniWalkSpeed[1] = 0.03f;
	//aniWalkSpeed[2] = 0.03f;
	//aniWalkSpeed[3] = 0.03f;

	int currentFrame = 0;
}

Raptor::~Raptor(void)
{
}
