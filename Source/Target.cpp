#include "Target.h"

extern hgeResourceManager resource;

Target::Target(int variation){
	HTEXTURE tex = resource.GetTexture("data\\icons\\Targets.png");
	mySprite = new hgeSprite(tex, 128.0f*variation, 0, 128, 128);
	mySprite->SetHotSpot(64, 64);
}


Target::~Target(void){
	delete mySprite;
}

void Target::Render(){
	mySprite->Render(myX, myY);
}

void Target::Update(const float &dt){

}