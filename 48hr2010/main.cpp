
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
#include <vector>

#include <hge.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgefont.h>
#include <hgeparticle.h>
#include <hgeresource.h>

#include "hgeRectExt.h"

#include "global.h"
#include "Input.h"
#include "Controller.h"
#include "Keyboard.h"
#include "KeyboardWASD.h"

#include "Renderable.h"

#include "TitleScreen.h"

#include "PlayerController.h"
#include "ParticleController.h"

#include "Egg.h"
#include "Beer.h"
#include "Raptor.h"
#include "DrunkGamer.h"
#include "Bar.h"
#include "Den.h"
#include "Tricero.h"

#include "DayNight.h"

// Pointer to the HGE interface.
HGE *hge=0;

std::vector<Input*> controllers;
std::vector<Resource*> beer;
std::vector<Resource*> eggs;
std::vector<Minion*> minions;
Building* bar = NULL;
Building* den = NULL;

ParticleController ps = ParticleController();

hgeResourceManager resource;

HSTREAM music = NULL;

DayNight* daytime;

TitleScreen* titleScreen;
PlayerController* playerA;
PlayerController* playerB;

int menuPosition = 0;
bool blinked = false;
float menuCD = 0.0f;

bool FrameFunc();
bool RenderFunc();
bool TitleFrameFunc();
bool TitleRenderFunc();
bool BlankityRenderFunc();
bool BlankityFrameFunc();
bool MenuFrameFunc();
bool MenuRenderFunc();

void cleanUpMemory(){
	while(beer.size() > 0){
		delete beer[0];
		beer.erase(beer.begin());
	}

	while(eggs.size() > 0){
		delete eggs[0];
		eggs.erase(eggs.begin());
	}

	while(minions.size() > 0){
		delete minions[0];
		minions.erase(minions.begin());
	}
	
	den = new Den(133,450);
	bar = new Bar(S_WIDTH-134, 450);

	Input* p = playerA->getMyController();
	Input* q = playerB->getMyController();

	delete playerA;
	delete playerB;

	playerA = new PlayerController(p, 0);
	playerB = new PlayerController(q, 1);

	minions.push_back(den);
	minions.push_back(bar);
}

bool TitleFrameFunc() {
	float dt=hge->Timer_GetDelta();
	int i = 0;

	static float myBlah = 0.0f;
	myBlah += dt;

	if(myBlah > 1.0f)
		myBlah = -1.0f;

	if(myBlah > 0)
		blinked = true;
	else
		blinked = false;

	if(hge->Input_GetKeyState(HGEK_ESCAPE)){
		return true;
	}

	controllers[0]->update();
	controllers[1]->update();
	controllers[2]->update();
	controllers[3]->update();

	if(controllers[0]->AnyKey() || controllers[1]->AnyKey() || controllers[2]->GetStart() || controllers[3]->GetStart()){
		if(controllers[0]->AnyKey() || controllers[1]->AnyKey()){
			playerA = new PlayerController(controllers[0], 0);
			playerB = new PlayerController(controllers[1], 1);
		} else {
			playerA = new PlayerController(controllers[2], 1);
			playerB = new PlayerController(controllers[3], 0);
		}

		hge->System_SetState(HGE_FRAMEFUNC, MenuFrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, MenuRenderFunc);
		titleScreen->Switch(4);
	}

	return false;
}

bool TitleRenderFunc() {
	hge->Gfx_BeginScene();

	hge->Gfx_Clear(0);

	titleScreen->Render();

	if(blinked)
		resource.GetSprite("startButton")->Render(S_WIDTH/2, S_HEIGHT*0.85);

	hge->Gfx_EndScene();

	return false;
}


bool BlankityRenderFunc() {
	hge->Gfx_BeginScene();

	hge->Gfx_Clear(0);

	titleScreen->Render();

	hge->Gfx_EndScene();

	return false;
}

bool BlankityFrameFunc() {
	float dt=hge->Timer_GetDelta();
	int i = 0;

	if(hge->Input_GetKeyState(HGEK_ESCAPE)){
		return true;
	}

	menuCD -= dt;

	controllers[0]->update();	controllers[1]->update();	controllers[2]->update();	controllers[3]->update();

	if((controllers[0]->AnyKey() || controllers[1]->AnyKey() || controllers[2]->AnyKey() || controllers[3]->AnyKey()) && menuCD <= 0.0f){
		hge->System_SetState(HGE_FRAMEFUNC, MenuFrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, MenuRenderFunc);
		titleScreen->Switch(4);
		menuCD = 0.20f;
	}

	return false;
}

bool WinRenderFunc() {
	hge->Gfx_BeginScene();

	hge->Gfx_Clear(0);

	titleScreen->Render();

	hge->Gfx_EndScene();

	return false;
}

bool WinFrameFunc() {
	float dt=hge->Timer_GetDelta();
	int i = 0;

	if(hge->Input_GetKeyState(HGEK_ESCAPE)){
		return true;
	}

	if(playerA->getMyController()->GetStartPress() || playerB->getMyController()->GetStartPress()){
		hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
		titleScreen->Switch(3);
	}

	return false;
}

bool MenuRenderFunc() {
	hge->Gfx_BeginScene();

	hge->Gfx_Clear(0);

	titleScreen->Render();

	if(menuPosition == 0) {
		resource.GetSprite("menuButtonPlayGlow")->Render(0.0f, 0.0f);
	} else {
		resource.GetSprite("menuButtonPlayNoneGlow")->Render(0.0f, 0.0f);
	}

	if(menuPosition == 1) {
		resource.GetSprite("menuButtonInstructionsGlow")->Render(0.0f, 0.0f);
	} else {
		resource.GetSprite("menuButtonInstructionsNoneGlow")->Render(0.0f, 0.0f);
	}

	if(menuPosition == 2){
		resource.GetSprite("menuButtonCreditsGlow")->Render(0.0f, 0.0f);
	} else {
		resource.GetSprite("menuButtonCreditsNoneGlow")->Render(0.0f, 0.0f);
	}

	if(menuPosition == 3){
		resource.GetSprite("menuButtonQuitGlow")->Render(0.0f, 0.0f);
	} else {
		resource.GetSprite("menuButtonQuitNoneGlow")->Render(0.0f, 0.0f);
	}


	hge->Gfx_EndScene();

	return false;
}

bool MenuFrameFunc() {
	float dt=hge->Timer_GetDelta();
	int i = 0;

	if(hge->Input_GetKeyState(HGEK_ESCAPE)){
		return true;
	}

	playerA->getMyController()->update();
	playerB->getMyController()->update();

	float blargh = 0.0f;

	menuCD -= dt;

	if(menuCD <= 0.0f){
		blargh = playerA->getMyController()->AimY() + playerB->getMyController()->AimY();
		if(playerA->getMyController()->AnyKey() || playerB->getMyController()->AnyKey()){
			if(menuPosition == 1 || menuPosition == 2 || menuPosition == 3){
				if(menuPosition == 1)
					titleScreen->Switch(6);
				if(menuPosition == 2)
					titleScreen->Switch(5);
				if(menuPosition == 3)
					return true;
				hge->System_SetState(HGE_FRAMEFUNC, BlankityFrameFunc);
				hge->System_SetState(HGE_RENDERFUNC, BlankityRenderFunc);
			}
			if(menuPosition == 0){
				titleScreen->Switch(3);
				hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
				hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
			}
			menuCD = 0.20f;
		}
	}

	if(blargh != 0.0f){
		if(blargh > 0)
			menuPosition++;
		else
			menuPosition--;

		if(menuPosition > 3)
			menuPosition = 0;
		if(menuPosition < 0)
			menuPosition = 3;

		SoundController::Play("data/sounds/tick.wav");

		menuCD = 0.20f;
	}

	return false;
}

bool FrameFunc() {
	float dt=hge->Timer_GetDelta();
	int i = 0;

	if(hge->Input_GetKeyState(HGEK_ESCAPE)){
		return true;
	}

	playerA->Update(dt);
	playerB->Update(dt);

	playerA->getMyController()->update();
	playerB->getMyController()->update();

	if(playerA->getMyController()->GetStartPress() || playerB->getMyController()->GetStartPress()){
		cleanUpMemory();
		hge->System_SetState(HGE_FRAMEFUNC, MenuFrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, MenuRenderFunc);
		titleScreen->Switch(4);
		menuCD = 0.2;
		return false;
	}

	//Step through the day
	daytime->Update(dt);

	//Spawn resource collection items
	static float spawnEgg;
	static float spawnBeer;
	if (daytime->IsDay()) {
		//Mating time
		spawnEgg += dt * 5;
		spawnBeer += dt;
	} else {
		//Happy hour
		spawnEgg += dt;
		spawnBeer += dt * 5;
	}

	if (spawnEgg > 10 && eggs.size() < 3) {
		spawnEgg = 0;
		eggs.push_back(new Egg((float)(hge->Random_Int((int)WIN_MINX, (int)(WIN_MINX + (WIN_MAXX - WIN_MINX)/2.0f))), (float)(hge->Random_Int((int)WIN_MINY, (int)WIN_MAXY))));
	}

	if (spawnBeer > 10 && beer.size() < 3) {
		spawnBeer = 0;
		beer.push_back(new Beer((float)hge->Random_Int((int)(WIN_MINX + (WIN_MAXX - WIN_MINX)/2.0f), (int)WIN_MAXX), (float)hge->Random_Int((int)WIN_MINY, (int)WIN_MAXY)));
	}


	if (den->IsReadyToVanish() || bar->IsReadyToVanish()){
		if(bar->IsReadyToVanish()){
			titleScreen->Switch(2);
		} else {
			titleScreen->Switch(1);
		}
		
		cleanUpMemory();

		hge->System_SetState(HGE_FRAMEFUNC, WinFrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, WinRenderFunc);

		return false;
	}

	for (int i = 0; i < (int)minions.size(); ++i)
	{
		if (minions[i]->IsReadyToVanish())
		{
			delete minions[i];
			minions.erase(minions.begin() + i);
			--i;
		}

	}

	for (int i = 0; i < (int)minions.size(); ++i)
	{
		(minions[i])->Update(dt);
	}

	ps.Update(dt);

	return false;
}


bool RenderFunc() {
	int i = 0;

	hge->Gfx_BeginScene();

	hge->Gfx_Clear(0);

	daytime->Render();

	titleScreen->Render();

	for (int i = 0; i < (int)eggs.size(); ++i) {
		(eggs[i])->Render();
	}
	for (int i = 0; i < (int)beer.size(); ++i) {
		(beer[i])->Render();
	}
	for (int i = 0; i < (int)minions.size(); ++i) {
		(minions[i])->Render();
	}

	ps.Render();

	playerA->Render();
	playerB->Render();

	hge->Gfx_EndScene();

	return false;
}


//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
int main (int argc, char * argv[]) {
	controllers.push_back(new Keyboard());
	controllers.push_back(new KeyboardWASD());
	controllers.push_back(new Controller(0));
	controllers.push_back(new Controller(1));
	controllers.push_back(new Controller(2));
	controllers.push_back(new Controller(3));

	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "log.log");
	hge->System_SetState(HGE_FRAMEFUNC, TitleFrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, TitleRenderFunc);
	hge->System_SetState(HGE_TITLE, "Atramentarious 48 Hour 2010");
	hge->System_SetState(HGE_FPS, 100);
	hge->System_SetState(HGE_WINDOWED, S_WINDOWED);
	hge->System_SetState(HGE_SCREENWIDTH, S_WIDTH);
	hge->System_SetState(HGE_SCREENHEIGHT, S_HEIGHT);
	hge->System_SetState(HGE_SCREENBPP, S_BPP);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_ZBUFFER, true);

	resource.ChangeScript("data/resources.txt");

	if(hge->System_Initiate()) 
	{
		titleScreen = new TitleScreen();
		daytime = new DayNight();
		den = new Den(133,450);
		bar = new Bar(S_WIDTH-134, 450);
		minions.push_back(den);
		minions.push_back(bar);

		music = hge->Stream_Load("data\\music\\jungle-run.mp3");
		hge->Stream_Play(music, true);

		//Get things rolling.
		hge->System_Start();
	}

	// Clean up and shutdown

	int i = 0;

	for(i=0; i<(int)controllers.size(); i++){
		delete controllers[i];
	}
	controllers.clear();

	delete playerA;
	delete playerB;
	delete titleScreen;
	delete daytime;

	//Delete vector data

	resource.Purge();

	hge->System_Shutdown();
	hge->Release();

	//Memory leak from vectors :(
	_CrtDumpMemoryLeaks();

	return 0;
}