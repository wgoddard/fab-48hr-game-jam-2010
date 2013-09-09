#pragma once
#include "renderable.h"

#include "SoundController.h"

//#include "global.h"

class DayNight 
	: public Renderable {
private:
	hgeSprite *sky;
	hgeSprite *star;
	hgeSprite *sun;
	hgeSprite *moon;
	hgeSprite *glow;
	hgeSprite *clock;

	float myTime;

	hgeColor colourTop;
	hgeColor colourBottom;

	float starX[NUM_STARS];
	float starY[NUM_STARS];
	float starS[NUM_STARS];
	float starA[NUM_STARS];

	hgeColor colSun;
	hgeColor colSunGlow;
	hgeColor colMoon;
	hgeColor colMoonGlow;
	hgeColor colSeaGlow;

	float sunX, sunY, sunS, sunGlowS;
	float moonX, moonY, moonS, moonGlowS;
	float seaGlowX, seaGlowSX, seaGlowSY;
public:
	DayNight(void);
	~DayNight(void);
	void Update(const float &dt);
	void Render();
	int GetHour() { return (int)(myTime*0.4f); }
	int GetMinutes() { float dt = myTime*0.4f; while(dt >= 1.0f){ dt -= 1.0f; } return (int)(dt*60.0f); }
	float GetTime() { return myTime*0.4f; }
	bool IsDay() { return (GetHour() > 6 && GetHour() < 18); }
};
