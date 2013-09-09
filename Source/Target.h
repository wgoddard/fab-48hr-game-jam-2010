#pragma once
#include "staticobject.h"
class Target :
	public StaticObject
{
private:
	hgeSprite* mySprite;
public:
	Target(int variation);
	~Target(void);

	void Render();
	void Update(const float &dt);
};

