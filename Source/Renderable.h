#pragma once
#include <hgesprite.h>
#include <hgeresource.h>

#include "global.h"

class Renderable
{
protected:
	float myX;
	float myY;
	float myAngle;
public:
	Renderable(void){ myX = 0.0f; myY = 0.0f; myAngle = 0.0f; };
	~Renderable(void){};

	virtual void Update(const float &dt) = 0;
	virtual void Render() = 0;

	float getX(){ return myX; }
	float getY(){ return myY; }
	float getAngle(){ return myAngle; }

	void setPosition(float x, float y){ myX = x; myY = y; }
	void setAngle(float angle){ myAngle = angle; }
};

