#pragma once
#include "Minion.h"

class DrunkGamer :
	public Minion
{
protected:
	void deathSound() { SoundController::Play("data\\sounds\\Thwap.wav");}
public:
	DrunkGamer(float x, float y);
	~DrunkGamer(void);
	void Render(bool t);
	void Update(const float &dt);
};
