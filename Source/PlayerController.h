#pragma once

#include "Renderable.h"
#include "Controller.h"
#include "Target.h"
#include "global.h"
#include "ResourceIcon.h"
#include <vector>
#include "Resource.h"
#include "Minion.h"
#include "ParticleController.h"
#include <hgeparticle.h>
#include "SoundController.h"

#include "DrunkGamer.h"
#include "Raptor.h"
#include "Tricero.h"
#include "Fatty.h"
#include "Speedling.h"
#include "Hooker.h"

class PlayerController
	: public Renderable {
private:
	//My Children
	Input* myController;
	Target* myTarget;
	ResourceIcon* myIcon;
	hgeFont *resFont;

	hgeSprite *mySelection;

	//My Data
	int myTeam;
	int myResource;
	float myResourceTimer;
	float myCooldown;
	float myCooldownTime;
	float myTargetSpeed;

	float mySpawnPos;

	float myCooldownOnSpawning;
	float myCooldownOnSpawningTime;

	float timeoutOnChanging;

	int myCurrentSelection;

	hgeParticleSystem *mySpawnLight;
public:
	PlayerController(Input* c, int variation);
	~PlayerController(void);

	void Render();
	void Update(const float &dt);
	void Fire();

	Input* getMyController(){ return myController; }
};

