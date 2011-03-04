#pragma once
#include "staticobject.h"
class ResourceIcon :
	public StaticObject
{
protected:
	hgeSprite* mySprite;
	int myTeam;
public:
	ResourceIcon(int variation);
	~ResourceIcon(void);
	void Render();
	void Update(const float &dt);
};

