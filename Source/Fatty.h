#pragma once
#include "minion.h"

class Fatty :
	public Minion
{
protected:
	void Attack();
	
	hgeSprite* spriteB;
	void deathSound() { SoundController::Play("data\\sounds\\fattydie.wav"); }
public:
	Fatty(float x, float y);
	~Fatty(void);
	void Render(bool);
};
