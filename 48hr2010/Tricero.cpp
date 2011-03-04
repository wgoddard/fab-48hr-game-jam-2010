#include "Tricero.h"

extern hgeResourceManager resource;
extern std::vector<Minion*> minions;

Tricero::Tricero(float x, float y) : Minion(x,y)
{
	myTeam = 1;
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

	mySprite = resource.GetSprite("trice");


	aniWalkNum = 2;
	aniAttackNum = 3;
	aniDeathNum = 2;

	aniDeathSpeed[1] = 1.0f;

	int currentFrame = 0;
}

Tricero::~Tricero(void)
{
}

void Tricero::Attack()
{
	if (myCooldown <= 0) //Check if minion can attack
	{
		myCooldown = myAttackSpeed;
		
		for (int i = 0; i < myTargets.size(); ++i)
		{
			int damageTaken = myTargets[i]->Defend(myDamage, this);
			TakeDamage( damageTaken);
		}


		for (int i = 0; i < myTargets.size(); ++i)
		{
			if (myTargets.size() > 0 && myTargets[i]->IsAlive() == false){
				myTargets.erase(myTargets.begin()+i);
			}
		}

	}
}

void Tricero::Render(bool t){
	Minion::Render(false);

	if (IsAlive() == false)	{
		mySprite->SetTextureRect(currentFrame*mySprite->GetWidth(), 3*mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
		mySprite->Render(myX, myY);
		return;
	}

	if(myCooldown > 0) {
		if(currentFrame != 2)
			mySprite->SetTextureRect(currentFrame*mySprite->GetWidth(), 1*mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
		else
			mySprite->SetTextureRect(0, 2*mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
	} else if (IsAlive()){
		mySprite->SetTextureRect(currentFrame*mySprite->GetWidth(), 0, mySprite->GetWidth(), mySprite->GetHeight());
	}

	mySprite->Render(myX, myY);
}