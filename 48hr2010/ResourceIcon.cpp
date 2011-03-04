#include "ResourceIcon.h"

extern hgeResourceManager resource;

ResourceIcon::ResourceIcon(int variation){
	myTeam = variation;

	HTEXTURE tex = resource.GetTexture("data\\icons\\Targets.png");
	mySprite = new hgeSprite(tex, 128.0f*variation, 128, 128, 128);
	mySprite->SetHotSpot(64, 64);
}


ResourceIcon::~ResourceIcon(void)
{
}

void ResourceIcon::Render(){
	if(myTeam == TEAM_DINO)
		mySprite->Render(64, 64);
	if(myTeam == TEAM_BAR)
		mySprite->Render(S_WIDTH - 64, 64);
}

void ResourceIcon::Update(const float &dt){
	//do nothing...
}