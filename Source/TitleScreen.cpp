#include "TitleScreen.h"

extern hgeResourceManager resource;
extern HGE *hge;

TitleScreen::TitleScreen(){
	tex1 = resource.GetTexture("data/screens/title/PartA.png");
	tex2 = resource.GetTexture("data/screens/title/PartB.png");
	pieceA = new hgeSprite(tex1, 0, 0, 1024, 900);
	pieceB = new hgeSprite(tex2, 1024, 0, 416, 900);
}

TitleScreen::~TitleScreen(void)
{
	delete pieceA;
	delete pieceB;
}

void TitleScreen::Render(){
	pieceA->Render(0, 0);
	pieceB->Render(1024, 0);
}

void TitleScreen::Switch(int newVariation){
	if(newVariation == 0){
		tex1 = resource.GetTexture("data/screens/title/PartA.png");
		tex2 = resource.GetTexture("data/screens/title/PartB.png");
	} else if(newVariation == 1){
		tex1 = resource.GetTexture("data/screens/wins/BarWinA.png");
		tex2 = resource.GetTexture("data/screens/wins/BarWinB.png");
	} else if(newVariation == 2){
		tex1 = resource.GetTexture("data/screens/wins/DinoWinA.png");
		tex2 = resource.GetTexture("data/screens/wins/DinoWinB.png");
	} else if(newVariation == 3){
		tex1 = resource.GetTexture("data/screens/map/PartA.png");
		tex2 = resource.GetTexture("data/screens/map/PartB.png");
	} else if(newVariation == 4){
		tex1 = resource.GetTexture("data/screens/menu/PartA.png");
		tex2 = resource.GetTexture("data/screens/menu/PartB.png");
	} else if(newVariation == 5){
		tex1 = resource.GetTexture("data/screens/credits/PartA.png");
		tex2 = resource.GetTexture("data/screens/credits/PartB.png");
	} else if(newVariation == 6){
		tex1 = resource.GetTexture("data/screens/instructions/PartA.png");
		tex2 = resource.GetTexture("data/screens/instructions/PartB.png");
	}

	pieceA->SetTexture(tex1);
	pieceB->SetTexture(tex2);
}