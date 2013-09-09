#pragma once
#include "unit.h"

class Resource :
	public Unit
{
public:
	Resource(float x, float y);
	virtual ~Resource(void);
};
