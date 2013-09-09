#pragma once
#include "animatedobject.h"

class Unit :
	public AnimatedObject
{
protected:
	int myTeam;
	hgeRect myRect;
	int myW;
	int myH;
	int myValue;
	hgeSprite * mySprite;
public:
	Unit(float x, float y);
	virtual ~Unit(void);
	int GetTeam() { return myTeam; }
	virtual hgeRect GetRect() {return myRect;}
	int GetValue() { return myValue;}
	virtual void Render(bool renderSprite = true);
};
