#pragma once
#include "minion.h"

class Hooker :
	public Minion
{
protected:
	void Attack();
	void deathSound() { SoundController::Play("data\\sounds\\y1.mp3"); }
public:
	Hooker(float x, float y);
	~Hooker(void);
	void Update(const float &dt);

};
