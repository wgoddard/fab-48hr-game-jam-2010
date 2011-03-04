#include "ParticleController.h"

ParticleController::ParticleController(void){

}


ParticleController::~ParticleController(void){
	parMan.KillAll();
	while((int)systems.size() > 0){
		delete systems[0];
		systems.erase(systems.begin(), systems.begin()+1);
	}
}

void ParticleController::Render(){
	parMan.Render();
}

void ParticleController::Update(const float &dt){
	parMan.Update(dt);

	int ki = (int)systems.size();
	for(int i = 0; i < ki; i++){
		if(!parMan.IsPSAlive(systems[i])){
			parMan.KillPS(systems[i]);
			systems.erase(systems.begin()+i, systems.begin()+i+1);
			ki--;
			i--;
		}
	}
}

void ParticleController::AddSystem(hgeParticleSystem* newSystem, float x, float y){
	systems.push_back(newSystem);
	parMan.SpawnPS(&newSystem->info, x, y);
}