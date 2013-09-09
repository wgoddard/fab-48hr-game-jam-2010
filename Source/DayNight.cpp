#include "DayNight.h"

extern hgeResourceManager resource;
extern HGE *hge;

DayNight::DayNight(void){
	HTEXTURE texObjects = resource.GetTexture("data/graphics/objects.png");

	sky = new hgeSprite(0, 0, 0, S_WIDTH, WIN_MINY);
	star = new hgeSprite(texObjects,72,81,9,9);
	star->SetHotSpot(5,5);

	sun=new hgeSprite(texObjects,81,0,114,114);
	sun->SetHotSpot(57,57);
	moon=new hgeSprite(texObjects,0,0,81,81);
	moon->SetHotSpot(40,40);
	star=new hgeSprite(texObjects,72,81,9,9);
	star->SetHotSpot(5,5);

	glow=new hgeSprite(texObjects,128,128,128,128);
	glow->SetHotSpot(64,64);
	glow->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_NOZWRITE);

	for(int i=0; i<NUM_STARS; i++) {
		starX[i] = hge->Random_Float(0, S_WIDTH);
		starY[i] = hge->Random_Float(0, WIN_MINY);
		starS[i] = hge->Random_Float(0.1f, 0.7f);
	}

	myTime = 0;
}

DayNight::~DayNight(void) {
	delete sky;
	delete star;
	delete sun;
	delete moon;
	delete glow;
}

void DayNight::Update(const float &dt) {
	myTime += dt;
	if (myTime > 60)
		myTime = 0;

	float zenith = -(GetTime()/12.0f*M_PI-M_PI_2);;

	hgeColor colWhite;
	colWhite.SetHWColor(0xFFFFFFFF);

	DWORD topColours[] = {0xFF15092A, 0xFF6C6480, 0xFF89B9D0};
	DWORD bottomColours[] = {0xFF303E57, 0xFFAC7963, 0xFFCAD7DB};
	int sequence[] = {0, 0, 1, 2, 2, 2, 1, 0, 0};

	hgeColor col1, col2;

	int seq_id = (int)(GetHour()/3);
	float seq_residue = GetHour()/3.0f - seq_id + GetMinutes()/180.0f;

	col1.SetHWColor(topColours[sequence[seq_id]]);
	col2.SetHWColor(topColours[sequence[seq_id+1]]);
	colourTop = col2*seq_residue + col1*(1.0f-seq_residue);

	col1.SetHWColor(bottomColours[sequence[seq_id]]);
	col2.SetHWColor(bottomColours[sequence[seq_id+1]]);
	colourBottom = col2*seq_residue + col1*(1.0f-seq_residue);

	float a;

	if(seq_id>=6 || seq_id<2)
		for(int i=0; i < NUM_STARS; i++)
		{
			a = 1.0f-starY[i]/WIN_MINY;
			a *= hge->Random_Float(0.6f, 1.0f);
			if(seq_id>=6)
				a *= sinf((GetTime() - 18.0f)/6.0f*M_PI_2);
			else
				a*=sinf((1.0f-GetTime()/6.0f)*M_PI_2);
			starA[i]=a;
		}

	// Calculate sun position, scale and colors

	     if(seq_id==2) a=sinf(seq_residue*M_PI_2);
	else if(seq_id==5) a=cosf(seq_residue*M_PI_2);
	else if(seq_id>2 && seq_id<5) a=1.0f;
	else a=0.0f;
	
	colSun.SetHWColor(0xFFEAE1BE);
	colSun=colSun*(1-a)+colWhite*a;

	a=(cosf((float)GetTime()/6.0f*M_PI)+1.0f)/2.0f;
	if(seq_id>=2 && seq_id<=6) {
		colSunGlow=colWhite*a;
		colSunGlow.a=1.0f;
	} else
		colSunGlow.SetHWColor(0xFF000000);

	sunX=S_WIDTH*0.5f+cosf(zenith)*ORBITS_RADIUS;
	sunY=WIN_MINY*1.2f+sinf(zenith)*ORBITS_RADIUS/1.5;
	sunS=1.0f-0.3f*sinf((GetHour()-6.0f)/12.0f*M_PI);
	sunGlowS=3.0f*(1.0f-a)+3.0f;

	// Calculate moon position, scale and colors

	if(seq_id>=6) a=sinf((GetTime()-18.0f)/6.0f*M_PI_2);
	else a=sinf((1.0f-GetHour()/6.0f)*M_PI_2);
	colMoon.SetHWColor(0x20FFFFFF);
	colMoon=colMoon*(1-a)+colWhite*a;

	colMoonGlow = colWhite;
	colMoonGlow.a = 0.5f*a;

	moonX=S_WIDTH*0.5f+cosf(zenith-M_PI)*ORBITS_RADIUS;
	moonY=WIN_MINY*1.2f+sinf(zenith-M_PI)*ORBITS_RADIUS/1.5;
	moonS=1.0f-0.3f*sinf((GetHour()+6.0f)/12.0f*M_PI);
	moonGlowS=a*0.4f+0.5f;

	int scene = ((GetTime()+18.0f)/24.0f*18.0f);

	scene = scene % 18;

	static bool playedDay = false;
	if (GetHour() == 6 && playedDay == false)
	{
		SoundController::Play("data\\sounds\\rooster.wav");
		playedDay = true;
	}
	if (GetHour() == 18 && playedDay == true)
	{
		SoundController::Play("data\\sounds\\cricket.wav");
		playedDay = false;
	}
}

void DayNight::Render() {
	sky->SetColor(colourTop.GetHWColor(), 0);
	sky->SetColor(colourTop.GetHWColor(), 1);
	sky->SetColor(colourBottom.GetHWColor(), 2);
	sky->SetColor(colourBottom.GetHWColor(), 3);
	sky->Render(0, 0);

	if(GetHour() >= 18 || GetHour() < 6)
		for(int i=0; i<NUM_STARS; i++) {
			star->SetColor((DWORD(starA[i]*255.0f)<<24) | 0xFFFFFF);
			star->RenderEx(starX[i], starY[i], 0.0f, starS[i]);
		}

	// Render sun
	
	glow->SetColor(colSunGlow.GetHWColor());
	glow->RenderEx(sunX, sunY, 0.0f, sunGlowS);
	sun->SetColor(colSun.GetHWColor());
	sun->RenderEx(sunX, sunY, 0.0f, sunS);

	// Render moon

	glow->SetColor(colMoonGlow.GetHWColor());
	glow->RenderEx(moonX, moonY, 0.0f, moonGlowS);
	moon->SetColor(colMoon.GetHWColor());
	moon->RenderEx(moonX, moonY, 0.0f, moonS);
}