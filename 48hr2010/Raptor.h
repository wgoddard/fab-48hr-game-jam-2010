#pragma once
#include "Minion.h"

class Raptor :
	public Minion
{
protected:
	void deathSound() { SoundController::Play("data\\sounds\\Beast.wav"); }
public:
	Raptor(float x, float y);
	~Raptor(void);
};
