#pragma once
#include "renderable.h"
class StaticObject :
	public Renderable
{
public:
	StaticObject(void);
	~StaticObject(void);

	virtual void Update(const float &dt) = 0;
	virtual void Render() = 0;
};

