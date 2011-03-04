#pragma once
#include "building.h"

class Den :
	public Building
{
private:
	bool hasDied;
public:
	Den(float x, float y);
	~Den(void);
	void Render(bool t = true);

};
