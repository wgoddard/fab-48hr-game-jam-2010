#include "SoundController.h"

extern HGE *hge;
extern hgeResourceManager resource;

SoundController::SoundController(void){

}


SoundController::~SoundController(void){

}

void SoundController::Play(char* filename){
	hge->Effect_Play(resource.GetEffect(filename));
}