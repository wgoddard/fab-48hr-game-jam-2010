#pragma once
#include "Renderable.h"

class AnimatedObject
	: public Renderable
{
public:
	AnimatedObject(void);
	~AnimatedObject(void);

	virtual void Render(){};
	virtual void Update(const float &dt){};
};

