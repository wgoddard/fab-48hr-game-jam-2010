#include "Fatty.h"

extern hgeResourceManager resource;
extern std::vector<Minion*> minions;

Fatty::Fatty(float x, float y) : Minion(x,y) {
	myTeam = 0;
	myW = 150;
	myH = 100;

	mySpeed = 60.0f;
	myCooldown = 0.0f;
	myAttackSpeed = 2.0f;
	myDamage = 1;
	myCurrentHP = 15;
	myMaxHP = 15;
	myMaxSlots = 5;
	myEngageWidth = 220.0f;

	myTargetBox = hgeRect(myX, myY - myEngageWidth/2, myX + (300 * (myTeam == 0 ? -1 : 1)), myY + myEngageWidth/2);
	myRect.Set(myX-myW/2, myY-myH/2, myX+myW/2, myY+myH/2);


	currentFrame = 0;
	animationCooldown = 0.0f;

	HTEXTURE texA = resource.GetTexture("data/graphics/minions/bar/FatguyA.png");
	HTEXTURE texB = resource.GetTexture("data/graphics/minions/bar/FatguyB.png");

	mySprite = new hgeSprite(texA, 0, 0, 500, 250);
	spriteB = new hgeSprite(texB, 0, 0, 500, 250);

	mySprite->SetHotSpot(200, 150);
	spriteB->SetHotSpot(200, 150);
	
	aniWalkNum = 2;
	aniAttackNum = 4;
	aniDeathNum = 3;

	int currentFrame = 0;
}

Fatty::~Fatty(void){
	delete mySprite;
	delete spriteB;
}

void Fatty::Attack()
{
	if (myCooldown <= 0) {
		myCooldown = myAttackSpeed;
		
		for (int i = 0; i < myTargets.size(); ++i) {
			int damageTaken = myTargets[i]->Defend(myDamage, this);
			TakeDamage( damageTaken);
		}


		for (int i = 0; i < myTargets.size(); ++i) {
			if (myTargets.size() > 0 && myTargets[i]->IsAlive() == false) {
				myTargets.erase(myTargets.begin()+i);
			}
		}
	}
}

void Fatty::Render(bool renderSprite){
	if (IsAlive() == false){
		if(currentFrame != 2)
			spriteB->SetTextureRect(currentFrame*spriteB->GetWidth(), 0, spriteB->GetWidth(), spriteB->GetHeight());
		else
			spriteB->SetTextureRect(0, spriteB->GetHeight(), spriteB->GetWidth(), spriteB->GetHeight());
		spriteB->Render(myX, myY);
		return;
	}

	if (myCooldown > 0) {
		if(currentFrame == 0)
			mySprite->SetTextureRect(0, mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
		if(currentFrame == 1)
			mySprite->SetTextureRect(mySprite->GetWidth(), mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
		if(currentFrame == 2)
			mySprite->SetTextureRect(0, 2*mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
		if(currentFrame == 3)
			mySprite->SetTextureRect(mySprite->GetWidth(), 2*mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
	} else if (IsAlive()){
		mySprite->SetTextureRect(currentFrame*mySprite->GetWidth(), 0, mySprite->GetWidth(), mySprite->GetHeight());
	}

	mySprite->Render(myX, myY);
	Minion::Render(false);
}