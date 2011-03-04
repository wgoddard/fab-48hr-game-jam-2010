#pragma once
#include "renderable.h"

#include <hgesprite.h>

class TitleScreen :
	public Renderable
{
protected:
	hgeSprite* pieceA;
	hgeSprite* pieceB;

	HTEXTURE tex1;
	HTEXTURE tex2;
public:
	TitleScreen();
	~TitleScreen(void);
	void Render(void);
	void Update(const float &dt){}
	void Switch(int newVariation);
};

