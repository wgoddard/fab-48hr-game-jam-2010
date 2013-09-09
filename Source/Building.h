#pragma once
#include "minion.h"

class Building : public Minion
{
public:
	Building(float x, float y);
	virtual ~Building(void);
	//virtual void Update(const float &dt){}
	virtual void Render(bool t){};
};
