#include "DrunkGamer.h"

extern hgeResourceManager resource;
extern std::vector<Minion*> minions;

DrunkGamer::DrunkGamer(float x, float y) : Minion(x,y)
{
	myW = myH = 80;
	myRect.Set(myX-myW/2, myY-myH/2, myX+myW/2, myY+myH/2);

	mySprite = resource.GetSprite("nerd");
	myTeam = 0;
	myTargetBox = hgeRect(myX, myY - myEngageWidth/2, myX + (300 * (myTeam == 0 ? -1 : 1)), myY + myEngageWidth/2);

	aniWalkNum = 2;
	aniAttackNum = 3;
	aniDeathNum = 6;
}

DrunkGamer::~DrunkGamer(void) {
	
}

void DrunkGamer::Render(bool t){
	Minion::Render(t);
}

void DrunkGamer::Update(const float &dt){
	Minion::Update(dt);
}