#pragma once
#include "minion.h"

class Tricero :
	public Minion
{
protected:
	void Attack();
	void deathSound() { SoundController::Play("data\\sounds\\dinodie.mp3"); }
public:
	Tricero(float x, float y);
	~Tricero(void);
	void Render(bool t);
};
