#include "Speedling.h"

extern hgeResourceManager resource;
extern std::vector<Minion*> minions;

Speedling::Speedling(float x, float y) : Minion(x,y)
{
	myTeam = 1;
	myType = 1;
	myW = myH = 55;

	mySpeed = 30.0f;
	myCooldown = 0.0f;
	myAttackSpeed = 3.5f;
	myDamage = 20;
	myCurrentHP = 1;
	myMaxHP = 1;
	myMaxSlots = 1;
	myEngageWidth = 120.0f;
	myTargetBox = hgeRect(myX, myY - myEngageWidth/2, myX + (750 * (myTeam == 0 ? -1 : 1)), myY + myEngageWidth/2);
	myRect.Set(myX-myW/2, myY-myH/2, myX+myW/2, myY+myH/2);

	currentFrame = 0;
	animationCooldown = 0.0f;




	mySprite = resource.GetSprite("speedling");

	myTargetBox = hgeRect(myX, myY - myEngageWidth/2, myX + (300 * (myTeam == 0 ? -1 : 1)), myY + myEngageWidth/2);

	aniWalkNum = 4;
	aniAttackNum = 4;
	aniDeathNum = 3;

	aniAttackSpeed[0] = 0.125f;
	aniAttackSpeed[1] = 0.125f;
	aniAttackSpeed[2] = 0.125f;
	aniAttackSpeed[3] = 0.8f;


	int currentFrame = 0;
}

Speedling::~Speedling(void)
{
}




void Speedling::Attack()
{
	if (myCooldown <= 0) //Check if minion can attack
	{
		myCooldown = myAttackSpeed;
		
		if (myTargets[0]->GetType() == 0)
		{
			myTargets[0]->Defend(myDamage, this);
		}
		else
			TakeDamage(myTargets[0]->Defend(myDamage, this));

		if (myTargets.size() > 0 && myTargets[0]->IsAlive() == false){
			myTargets.erase(myTargets.begin());
		}

	}
}

void Speedling::Update(const float &dt)
{	
	myCooldown -= dt;
	animate(dt);


	if (IsAlive() == false) 
	{
		return;
	}


	//If you can still engage targets, try to
	if (myTargets.size() < myMaxSlots)
	{
		//Attempt to find another target to engage
		FindTarget();
	}

	//If there is a target, begin to engage the first one
	if (myTargets.size() > 0 )
	{
			Attack();	
	}
	else
	{
		float dx = mySpeed * dt * (myTeam == 0 ? -1 : 1);

		myRect.x1 += dx;
		myRect.x2 += dx;
		myTargetBox.x1 += dx;
		myTargetBox.x2 += dx;

		myX += dx;
	}
}