#include "Bar.h"

extern hgeResourceManager resource;
extern std::vector<Minion*> minions;

Bar::Bar(float x, float y) : Building(x,y)
{
	hasDied = false;
	mySprite = resource.GetSprite("bar");
	mySprite->SetTexture(resource.GetTexture("data/screens/map/bar.png"));
	myTeam = 0;
	myTargetBox = hgeRect(myX, myY - myEngageWidth/2, myX + (50 * (myTeam == 0 ? -1 : 1)), myY + myEngageWidth/2);
}

Bar::~Bar(void)
{
}

void Bar::Render(bool t){
	int section = 5 - 5*((float)myCurrentHP/myMaxHP);


	if(section > 2 && !hasDied){
		HTEXTURE tex2 = resource.GetTexture("data/screens/map/bar2.png");
		mySprite->SetTexture(tex2);
		hasDied = true;
	}

	if(section < 3)
		mySprite->SetTextureRect(section*267, 0, 267, 900);
	else
		mySprite->SetTextureRect((section-3)*267, 0, 267, 900);

	mySprite->Render(myX, myY);

	resource.GetFont("resourceFnt")->printf(myX, myY, HGETEXT_LEFT, "%i", myCurrentHP);
}