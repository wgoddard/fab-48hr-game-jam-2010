#include "KeyboardWASD.h"

KeyboardWASD::KeyboardWASD(void){

}

KeyboardWASD::~KeyboardWASD(void){
	
}

void KeyboardWASD::update(){
	if(hge->Input_GetKeyState(HGEK_A)){
		dx = -1.0;
	} else if(hge->Input_GetKeyState(HGEK_D)){
		dx = 1.0;
	} else {
		dx = 0.0;
	}
	
	if(hge->Input_GetKeyState(HGEK_W)){
		dy = -1.0;
	} else if(hge->Input_GetKeyState(HGEK_S)){
		dy = 1.0;
	} else {
		dy = 0.0;
	}

	stateStart = hge->Input_GetKeyState(HGEK_Q);

	stateA = hge->Input_GetKeyState(HGEK_C);
	stateB = hge->Input_GetKeyState(HGEK_V);
	stateC = hge->Input_GetKeyState(HGEK_B);
	stateD = hge->Input_GetKeyState(HGEK_N);

	ax = dx;
	ay = dy;
}

void KeyboardWASD::rumble(){
	//Bwahaha... Can't vibrate a keyboard
}

void KeyboardWASD::rumble(double, double){
	//Bwahaha... Can't vibrate a keyboard with double-double!
}

bool KeyboardWASD::GetCPress()
{
	return hge->Input_KeyDown(HGEK_B);
}

bool KeyboardWASD::GetDPress()
{
	return hge->Input_KeyDown(HGEK_N);
}

bool KeyboardWASD::GetStartPress(){
	return hge->Input_KeyDown(HGEK_Q);
}