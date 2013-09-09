#define S_WINDOWED true
#define S_WIDTH 1440
#define S_HEIGHT 900
#define S_BPP 32
#define Uint32 int

#define TEAM_DINO 1
#define TEAM_BAR 0

//Pixels per unit
#define PPU 44.0

//Window Sizes
#define WIN_MINX S_WIDTH*0.125f
#define WIN_MAXX S_WIDTH*0.875f
#define WIN_MINY S_HEIGHT*0.45f
#define WIN_MAXY S_HEIGHT*1.0f

//Implementation details
#define INIT_RESOURCE_AMT 25
#define INIT_TARGET_SPEED 500.0f
#define INIT_COOLDOWN_TIME 0.75f

//Time Of Day Settings
#define ORBITS_RADIUS	(S_WIDTH*0.43f)
#define NUM_STARS 100

//Macro
#define ARGB(a,r,g,b) ((DWORD(a)<<24) + (DWORD(r)<<16) + (DWORD(g)<<8) + DWORD(b))

#include <iostream>