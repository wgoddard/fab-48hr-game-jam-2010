#include "Keyboard.h"

Keyboard::Keyboard(void){

}

Keyboard::~Keyboard(void){
	
}

void Keyboard::update(){
	if(hge->Input_GetKeyState(HGEK_LEFT)){
		dx = -1.0;
	} else if(hge->Input_GetKeyState(HGEK_RIGHT)){
		dx = 1.0;
	} else {
		dx = 0.0;
	}
	
	if(hge->Input_GetKeyState(HGEK_UP)){
		dy = -1.0;
	} else if(hge->Input_GetKeyState(HGEK_DOWN)){
		dy = 1.0;
	} else {
		dy = 0.0;
	}

	stateStart = hge->Input_GetKeyState(HGEK_ENTER);

	stateA = hge->Input_GetKeyState(HGEK_H);
	stateB = hge->Input_GetKeyState(HGEK_J);
	stateC = hge->Input_GetKeyState(HGEK_K);
	stateD = hge->Input_GetKeyState(HGEK_L);

	ax = dx;
	ay = dy;
}

bool Keyboard::GetCPress(){
	return hge->Input_KeyDown(HGEK_K);
}

bool Keyboard::GetDPress(){
	return hge->Input_KeyDown(HGEK_L);
}

bool Keyboard::GetStartPress(){
	return hge->Input_KeyDown(HGEK_ENTER);
}

void Keyboard::rumble(){
	//Bwahaha... Can't vibrate a keyboard
}

void Keyboard::rumble(double, double){
	//Bwahaha... Can't vibrate a keyboard with double-double!
}