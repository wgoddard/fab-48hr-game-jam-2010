#pragma once
#include "input.h"

#include "hge.h"

extern HGE *hge;

class KeyboardWASD :
	public Input
{
public:
	KeyboardWASD(void);
	virtual ~KeyboardWASD(void);

	void update();
	void rumble();
	void rumble(double, double);

	virtual bool GetCPress();
	virtual bool GetDPress();
	virtual bool GetStartPress();
};
