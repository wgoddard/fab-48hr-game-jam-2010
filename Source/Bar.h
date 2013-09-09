#pragma once
#include "building.h"

class Bar : public Building
{
private:
	bool hasDied;
public:
	Bar(float x, float y);
	~Bar(void);
	void Render(bool t = true);
};
