#pragma once
#include "minion.h"

class Speedling :
	public Minion
{
protected:
	void Attack();
	void deathSound() { SoundController::Play("data\\sounds\\teradie.mp3"); }
public:
	Speedling(float x, float y);
	~Speedling(void);
	void Update(const float &dt);
};
