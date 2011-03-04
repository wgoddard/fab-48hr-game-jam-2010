#include "Controller.h"

Controller::Controller(int id)
{
	controllerId = id;
	rumblePower = 0.0;
}

Controller::~Controller(void)
{
}

void Controller::update(){
	DWORD dwResult;    
	XINPUT_STATE state;
	ZeroMemory( &state, sizeof(XINPUT_STATE) );

    // Simply get the state of the controller from XInput.
    dwResult = XInputGetState( controllerId, &state);

	pressC = false;
	pressD = false;
	pressStart = false;

    if( dwResult == ERROR_SUCCESS ){ 
		stateA = (int)(state.Gamepad.wButtons & XINPUT_GAMEPAD_A) || state.Gamepad.bRightTrigger > 10;
		stateB = (int)(state.Gamepad.wButtons & XINPUT_GAMEPAD_B) || state.Gamepad.bLeftTrigger > 10;
		stateC = (int)(state.Gamepad.wButtons & XINPUT_GAMEPAD_X) || (int)(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
		stateD = (int)(state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) || (int)(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
		stateStart = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START);

		if(abs(state.Gamepad.sThumbLX) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || 
				abs(state.Gamepad.sThumbLY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){
			dx = state.Gamepad.sThumbLX / 32768.0;
			dy = state.Gamepad.sThumbLY / -32768.0;
		} else {
			dx = 0.0;
			dy = 0.0;
		}

		if(abs(state.Gamepad.sThumbRX) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || 
			abs(state.Gamepad.sThumbRY) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){
			ax = state.Gamepad.sThumbRX / 32768.0;
			ay = state.Gamepad.sThumbRY / -32768.0;
		} else {
			ax = dx;
			ay = dy;
		}

		XINPUT_KEYSTROKE keystroke;
		ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
		for (dwResult = XInputGetKeystroke(controllerId, XINPUT_FLAG_GAMEPAD, &keystroke); dwResult == ERROR_SUCCESS; dwResult = XInputGetKeystroke(controllerId, XINPUT_FLAG_GAMEPAD, &keystroke))
		{
			if (keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN)
			{
				if (keystroke.VirtualKey == VK_PAD_LSHOULDER)
					pressC = true;
				if (keystroke.VirtualKey == VK_PAD_RSHOULDER)
					pressD = true;
				if (keystroke.VirtualKey == VK_PAD_START)
					pressStart = true;


				//if (keystroke.VirtualKey == VK_PAD_B)
				//	players[i]->AttackB();
				//if (keystroke.VirtualKey == VK_PAD_X)
				//	sheep[i]->PressKeyC();
				//ZeroMemory(&keystroke, sizeof(XINPUT_KEYSTROKE));
			}
		}

		//rumble((state.Gamepad.bLeftTrigger)/255.0, (state.Gamepad.bRightTrigger)/255.0);
	} else {
		//todo: actually do something here...
	}

}

void Controller::rumble(){
	XINPUT_VIBRATION vibration;
	ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
	vibration.wLeftMotorSpeed = 65535; // use any value between 0-65535 here
	vibration.wRightMotorSpeed = 65535; // use any value between 0-65535 here
	XInputSetState( controllerId, &vibration );
}

void Controller::rumble(double rateL, double rateR){
	XINPUT_VIBRATION vibration;
	ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
	vibration.wLeftMotorSpeed = (WORD)(rateL*65535); // use any value between 0-65535 here
	vibration.wRightMotorSpeed = (WORD)(rateR*65535); // use any value between 0-65535 here
	XInputSetState( controllerId, &vibration );
}

bool Controller::GetCPress(){
	return pressC;
}

bool Controller::GetDPress(){
	return pressD;
}

bool Controller::GetStartPress(){
	return pressStart;
}