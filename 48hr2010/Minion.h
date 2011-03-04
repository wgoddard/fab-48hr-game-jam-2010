#pragma once
#include "unit.h"
#include "hgeRectExt.h"
#include "SoundController.h"
//#include <cmath>
#include <vector>

class Minion :
	public Unit
{
protected:
	float mySpeed;
	float myCooldown;
	float myAttackSpeed;
	int myDamage;
	int myCurrentHP;
	int myMaxHP;
	//int myCurrentSlots;
	std::vector<Minion*> myTargets;
	int myMaxSlots;
	float myEngageWidth;
	hgeRectExt myTargetBox;
	virtual void Attack();

	short myType;

	//float deathWait;
	bool readyToVanish;

	int aniWalkNum, aniAttackNum, aniDeathNum;
	float aniWalkSpeed[8], aniAttackSpeed[8], aniDeathSpeed[8];
	int currentFrame;
	float animationCooldown;
	void animate(float dt);
	virtual void deathSound() {}
	void FindTarget();
public:
	Minion(float x, float y);
	virtual ~Minion(void);
	virtual void Update(const float &dt);
	virtual void Render(bool renderSprite = true);
	float GetSpeed() { return mySpeed; }
	void Engage(Minion* target);
	bool IsAvailable() { return ((int)myTargets.size() < myMaxSlots); }
	virtual int Defend(int damage, Minion* attacker); //Takes unit damage, and returns possible damage
	void TakeDamage(int damage);
	bool IsAlive() { return myCurrentHP > 0; }
	void unlockTarget(Minion* target);
	bool IsReadyToVanish() { return readyToVanish; }
	short GetType() { return myType; }
};
