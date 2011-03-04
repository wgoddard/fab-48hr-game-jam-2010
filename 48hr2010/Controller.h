#pragma once
#include "input.h"

#include <windows.h>
#include <XInput.h>

class Controller :
	public Input
{
private:
	int controllerId;
	double rumblePower;

	bool pressC;
	bool pressD;
	bool pressStart;
public:
	Controller(int id);
	~Controller(void);

	void update();
	void rumble();
	void rumble(double, double);
	bool GetCPress();
	bool GetDPress();
	virtual bool GetStartPress();
};
