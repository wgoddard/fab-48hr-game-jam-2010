#include "PlayerController.h"

extern hgeResourceManager resource;
extern std::vector<Resource*> beer;
extern std::vector<Resource*> eggs;
extern std::vector<hgeParticleSystem*> particleClouds;
extern std::vector<Minion*> minions;

extern ParticleController ps;

PlayerController::PlayerController(Input* c, int variation){
	myTeam = variation;

	myResourceTimer = 0.0f;

	myCooldownOnSpawning = 0.0f;
	myCooldownOnSpawningTime = 0.125f;

	myCurrentSelection = 0;
	mySelection = new hgeSprite(resource.GetTexture("data/icons/units.png"), 0, 0, 256, 256);

	myTarget = new Target(variation);
	myController = c;
	myIcon = new ResourceIcon(variation);

	myTarget->setPosition(S_WIDTH / 2.0f, S_HEIGHT * 0.66667f);
	resFont = resource.GetFont("resourceFnt");

	myResource = INIT_RESOURCE_AMT;

	myCooldown = 0.0f;
	myCooldownTime = INIT_COOLDOWN_TIME;
	myTargetSpeed = INIT_TARGET_SPEED;

	mySpawnPos = (WIN_MAXY + WIN_MINY)/2 + WIN_MINY;

	timeoutOnChanging = 0.0;

	if (variation == TEAM_BAR)
		mySpawnLight = new hgeParticleSystem("data/particles/spawnLight.psi", resource.GetSprite("dinoTarget"));
	else
		mySpawnLight = new hgeParticleSystem("data/particles/spawnLight.psi", resource.GetSprite("barTarget"));
	mySpawnLight->Fire();
}

PlayerController::~PlayerController(void){
	delete myTarget;
	delete myIcon;
}

void PlayerController::Render(){
	myTarget->Render();
	myIcon->Render();

	mySpawnLight->Render();

	//std::cout << mySpawnPos << std::endl;

	if(myTeam == TEAM_DINO){
		resFont->SetColor(ARGB(255, 255, 255, 255));
		resFont->printf(128, 64-resFont->GetHeight()/2, HGETEXT_LEFT, "%i", myResource);

		mySelection->SetTextureRect(myCurrentSelection*256, myTeam*256, 256, 256);
		mySelection->RenderEx(10, S_HEIGHT-138, 0.0f, 0.5);
		mySelection->SetTextureRect(((myCurrentSelection+1)%3)*256, myTeam*256, 256, 256);
		mySelection->RenderEx(148, S_HEIGHT-95, 0.0f, 0.333);
		mySelection->SetTextureRect(((myCurrentSelection+2)%3)*256, myTeam*256, 256, 256);
		mySelection->RenderEx(243, S_HEIGHT-74, 0.0f, 0.25);
	} else if(myTeam == TEAM_BAR){
		resFont->SetColor(ARGB(255, 255, 255, 255));
		resFont->printf(S_WIDTH-128, 64-resFont->GetHeight()/2, HGETEXT_RIGHT, "%i", myResource);
		
		mySelection->SetTextureRect(myCurrentSelection*256, myTeam*256, 256, 256);
		mySelection->RenderEx(S_WIDTH-138, S_HEIGHT-138, 0.0f, 0.5);
		mySelection->SetTextureRect(((myCurrentSelection+1)%3)*256, myTeam*256, 256, 256);
		mySelection->RenderEx(S_WIDTH-233, S_HEIGHT-95, 0.0f, 0.333);
		mySelection->SetTextureRect(((myCurrentSelection+2)%3)*256, myTeam*256, 256, 256);
		mySelection->RenderEx(S_WIDTH-307, S_HEIGHT-74, 0.0f, 0.25);
	}

}

void PlayerController::Update(const float &dt){
	myTarget->Update(dt);
	myController->update();

	myResourceTimer -= dt;

	if (myResourceTimer <= 0)
	{
		myResourceTimer = 0.5f;
		myResource += 1;
	}

	float neoX = myTarget->getX() + (float)myController->GetX()*dt*myTargetSpeed;
	float neoY = myTarget->getY() + (float)myController->GetY()*dt*myTargetSpeed;

	if (neoY < WIN_MINY) neoY = WIN_MINY;
	if (neoY > WIN_MAXY) neoY = WIN_MAXY;
	if (neoX < WIN_MINX) neoX = WIN_MINX;
	if (neoX > WIN_MAXX) neoX = WIN_MAXX;

	myTarget->setPosition(neoX, neoY);

	mySpawnPos = neoY;

	if(myController->GetA())
		Fire();

	//if(timeoutOnChanging < 0){
		if (myController->GetCPress()) {
			SoundController::Play("data\\sounds\\tick.wav");
			myCurrentSelection--;
			if (myCurrentSelection < 0)
				myCurrentSelection = 2;
		}

		if (myController->GetDPress()) {
			SoundController::Play("data\\sounds\\tick.wav");
			myCurrentSelection++;
			if (myCurrentSelection > 2)
				myCurrentSelection = 0;
		}
		timeoutOnChanging = 0.10;
	//} else {
	//	timeoutOnChanging -= dt;
	//}

	if(myCooldown > 0)
		myCooldown -= dt;


	if(myCooldownOnSpawning > 0){
		myCooldownOnSpawning -= dt;
	} else if(myController->GetB()){
		myCooldownOnSpawning = myCooldownOnSpawningTime;
		switch (myCurrentSelection)
		{
		case 0:
			if (myResource < 2)
				break;
			if( myTeam == TEAM_BAR){
				minions.push_back(new DrunkGamer(WIN_MAXX, neoY));
				myResource -= 2;
			} else {
				minions.push_back(new Raptor(WIN_MINX, neoY));
				myResource -= 2;
			}
			break;
		case 1:
			if (myResource < 5)
				break;
			if(myTeam == TEAM_BAR){
				minions.push_back(new Fatty(WIN_MAXX, neoY));
				myResource -= 5;
			} else {
				minions.push_back(new Tricero(WIN_MINX, neoY));
				myResource -= 5;
			}
			break;
		case 2:
			if (myResource < 5)
				break;
			if(myTeam == TEAM_BAR){
				minions.push_back(new Hooker(WIN_MAXX, neoY));
				myResource -= 5;
			} else {
				minions.insert(minions.begin(), new Speedling(WIN_MINX, neoY));
				myResource -= 5;
			}
			break;
		default:
			break;
		}

		int z = 0;

		Minion* m = minions[minions.size()-1];

		while (z < minions.size())
		{
			//if (minions[z] == minions[minions.size()-1])
			//	break;
			if (minions[z]->getY() > m->getY())
			{
				minions.pop_back();
				minions.insert(minions.begin() + z, m);
				break;
			}
			++z;
		}

	}
	
	if(myCooldown < myCooldownTime / 2.0)
		myController->rumble(0.0, 0.0);

	mySpawnLight->Update(dt);
	if(myTeam == TEAM_DINO)
		mySpawnLight->MoveTo(WIN_MINX, mySpawnPos);
	else
		mySpawnLight->MoveTo(WIN_MAXX, mySpawnPos);
}

void PlayerController::Fire(){

	bool hit = false;

	if(myCooldown <= 0.0f){
		myController->rumble();
		
		ps.AddSystem(resource.GetParticleSystem("artillery"), myTarget->getX(), myTarget->getY());

		int i = 0;
		int i2k = 0;

		i2k = (int)beer.size();
		for (i = 0; i < i2k; i++){
			if(beer[i]->GetRect().TestPoint(myTarget->getX(), myTarget->getY())){
				if(myTeam == TEAM_BAR){
					myResource += beer[i]->GetValue();
				}
				delete beer[i];
				SoundController::Play("data\\sounds\\bottleopen.wav");
				hit = true;
				beer.erase(beer.begin()+i, beer.begin()+1+i);
				i2k--;
				i--;
			}
		}

		i2k = (int)eggs.size();
		for (i = 0;  i < i2k; i++){
			if(eggs[i]->GetRect().TestPoint(myTarget->getX(), myTarget->getY())){
				if(myTeam == TEAM_DINO){
					myResource += eggs[i]->GetValue();
				}
				delete eggs[i];
				SoundController::Play("data\\sounds\\bone-crack-1.mp3");
				hit = true;
				eggs.erase(eggs.begin()+i, eggs.begin()+1+i);
				i2k--;
				i--;
			}
		}

		i2k = (int)minions.size();
		for (i = 0;  i < i2k; i++){
			if(minions[i]->GetRect().TestPoint(myTarget->getX(), myTarget->getY())){
				if(myTeam != minions[i]->GetTeam()){
					if (minions[i]->IsReadyToVanish() == false) {
						if (minions[i]->IsAlive() == false)
							continue;
						minions[i]->TakeDamage(10000);
						hit = true;
						myResource += minions[i]->GetValue();
					}
					//delete minions[i];
					//minions.erase(minions.begin()+i, minions.begin()+1+i);
					//i2k--;
					//i--;
					break;
				}
			}
		}

		if (hit == false)
			SoundController::Play("data\\sounds\\thud.mp3");

		myCooldown = myCooldownTime;
	}
}