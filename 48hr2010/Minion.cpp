#include "Minion.h"

extern std::vector<Minion*> minions;

Minion::Minion(float x, float y) : Unit(x,y)
{


	myType = 0;
	readyToVanish = false;
	//deathWait = 0.0f;
	mySpeed = 120.0f;
	myCooldown = 0.0f;
	myAttackSpeed = 2.0f;
	myDamage = 1;
	myCurrentHP = 2;
	myMaxHP = 2;
	myMaxSlots = 1;
	myEngageWidth = 150.0f;
	myTargetBox = hgeRect(myX, myY - myEngageWidth/2, myX + (300 * (myTeam == 0 ? -1 : 1)), myY + myEngageWidth/2);
	myRect.Set(myX-myW/2, myY-myH/2, myX+myW/2, myY+myH/2);

	currentFrame = 0;
	animationCooldown = 0.0f;

	aniWalkNum = 1;
	aniAttackNum = 1;
	aniDeathNum = 1;

	aniWalkSpeed[0] = 0.125f;
	aniWalkSpeed[1] = 0.125f;
	aniWalkSpeed[2] = 0.125f;
	aniWalkSpeed[3] = 0.125f;
	aniWalkSpeed[4] = 0.125f;
	aniWalkSpeed[5] = 0.125f;
	aniWalkSpeed[6] = 0.125f;
	aniWalkSpeed[7] = 0.125f;

	aniAttackSpeed[0] = 0.125f;
	aniAttackSpeed[1] = 0.125f;
	aniAttackSpeed[2] = 0.125f;
	aniAttackSpeed[3] = 0.125f;
	aniAttackSpeed[4] = 0.125f;
	aniAttackSpeed[5] = 0.125f;
	aniAttackSpeed[6] = 0.125f;
	aniAttackSpeed[7] = 0.125f;

	aniDeathSpeed[0] = 0.5f;
	aniDeathSpeed[1] = 0.5f;
	aniDeathSpeed[2] = 0.5f;
	aniDeathSpeed[3] = 0.5f;
	aniDeathSpeed[4] = 0.5f;
	aniDeathSpeed[5] = 0.5f;
	aniDeathSpeed[6] = 0.5f;
	aniDeathSpeed[7] = 0.5f;
}

Minion::~Minion(void)
{
	for(int i = 0; i < (int)myTargets.size(); i++){
		myTargets[i]->unlockTarget(this);
	}
}

void Minion::Update(const float &dt)
{	
	myCooldown -= dt;
	animate(dt);

	if (IsAlive() == false) 
	{
		//std::cout << "I'm dead\n";
		return;
	}



	//If you can still engage targets, try to
	if (myTargets.size() < myMaxSlots)
	{
		FindTarget();
	}

	//If there is a target, begin to engage the first one
	if (myTargets.size() > 0 )
	{
		int directionY = myTargets[0]->getY() - myY;

		if (abs(directionY) > 3) //y Distance is now small
		{
			float dy = mySpeed * dt * (directionY > 0 ? 1 : -1);

			myRect.y1 += dy;
			myRect.y2 += dy;
			myTargetBox.y1 += dy;
			myTargetBox.y2 += dy;

			myY += dy;
		}

		//Check to move forward if not yet in contact on x axis

		int directionX = myTargets[0]->getX() - myX;

		if (abs(directionX) > myW) //x Distance is now small
		{
			float dx = mySpeed * dt * (myTeam == 0 ? -1 : 1);

			myRect.x1 += dx;
			myRect.x2 += dx;
			myTargetBox.x1 += dx;
			myTargetBox.x2 += dx;

			myX += dx;
		}

		if (abs(directionX) <= myW && abs(directionY) <= 3)
		{
			//std::cout << "Battle\n";
			Attack();
		}



		
	}
	else
	{
		float dx = mySpeed * dt * (myTeam == 0 ? -1 : 1);
		//if (myTeam == 0)
		//{
		//	if (myX <= WIN_MINX)
		//		//Attackbuilding
		//		dx = 0;
		//}
		//else
		//{
		//	if (myX >= WIN_MAXX)
		//		//AttackBuilding
		//		dx = 0;
		//}
		//Move forward until at the target base (implement check!)
		myRect.x1 += dx;
		myRect.x2 += dx;
		myTargetBox.x1 += dx;
		myTargetBox.x2 += dx;

		myX += dx;
	}
}

int Minion::Defend(int damage, Minion* attacker)
{
	TakeDamage(damage);
	if (myCooldown <= 0) //Check if minion can attack
		myCooldown = myAttackSpeed;
	return myDamage;
}

void Minion::TakeDamage(int damage)
{
	myCurrentHP -= damage;
	if (IsAlive() == false)
	{
		//I just died
		currentFrame = 0;
		animationCooldown = aniDeathSpeed[0];
		deathSound();
		//myCooldown = 0;
	}
}

void Minion::Attack()
{
	if (myCooldown <= 0) //Check if minion can attack
	{
		if (myTargets[0]->IsAlive() == false)
			return;
		myCooldown = myAttackSpeed;
		
		int damageTaken = myTargets[0]->Defend(myDamage, this);

		TakeDamage(damageTaken);

		if (myTargets[0]->IsAlive() == false){
			myTargets.erase(myTargets.begin());
		}

	}
}

void Minion::Render(bool renderSprite){
	//myTargetBox.Render();

	if (IsAlive() == false)
	{
		mySprite->SetTextureRect(currentFrame*mySprite->GetWidth(), 2*mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
		Unit::Render(renderSprite);
		return;
	}

	if(myCooldown > 0){
		mySprite->SetTextureRect(currentFrame*mySprite->GetWidth(), 1*mySprite->GetHeight(), mySprite->GetWidth(), mySprite->GetHeight());
	} else if (IsAlive()){
		mySprite->SetTextureRect(currentFrame*mySprite->GetWidth(), 0, mySprite->GetWidth(), mySprite->GetHeight());
	} 

	Unit::Render(renderSprite);
}

void Minion::Engage(Minion* target){
	myTargets.push_back(target);
}

void Minion::unlockTarget(Minion* target){
	for(int i = 0; i < (int)myTargets.size(); i++){
      
		if(myTargets.size() > 1000)
			return;
		if(myTargets[i] == target){
			myTargets[i] == NULL;
			myTargets.erase(myTargets.begin()+i);
		}
	}
}

void Minion::animate(float dt)
{
	animationCooldown -= dt;

	if(animationCooldown <= 0.0f){

		if(myCooldown > 0 && IsAlive()){ //Attacking
			currentFrame++;
			if(aniAttackNum <= currentFrame){
				currentFrame = 0;
			} 

			animationCooldown = aniAttackSpeed[currentFrame];
		} else if (IsAlive()) { //No attacking, but alive, so walking
			currentFrame++;
			if(currentFrame >= aniWalkNum){
				currentFrame = 0;
			}
			animationCooldown = aniWalkSpeed[currentFrame];
		} else { //Dead
			currentFrame++;
			if(currentFrame >= aniDeathNum){
				readyToVanish = true;
			}
			animationCooldown = aniDeathSpeed[currentFrame];
		}
	}
}

void Minion::FindTarget()
{
		//Attempt to find another target to engage

		Minion* closestTarget = NULL;
		float closestDistance = 99999999.0f;

		for (int i = 0; i < minions.size(); ++i)
		{
			if (minions[i]->GetTeam() == myTeam)
				continue;
			if (minions[i]->GetRect().Intersect(&myTargetBox) )
			{
				//Potentital target found, check if it's available for combat
				if (minions[i]->IsAvailable() == false)
					continue;

				bool isSame = false;
				for (int j = 0; j < myTargets.size(); ++j)
				{
					if (minions[i] == myTargets[j])
						isSame = true;
				}

				if (isSame) continue;
				
				//Now check if it's the closest one in terms of time to engagement (factoring both move speeds)
				float x1, y1, x2, y2;

				x1 = myX; y1 = myY;
				x2 = minions[i]->getX(); y2 = minions[i]->getY();

				float distance = ( ((x1 * x1 + x2 * x2) + (y1 * y1 + y2 * y2)) / (mySpeed + minions[i]->GetSpeed()) );
				if (distance < closestDistance){
					closestDistance = distance;
					closestTarget = minions[i];
				}

			}
		}
		if (closestTarget != NULL)
		{
			myTargets.push_back(closestTarget);
			closestTarget->Engage(this);
		}
}