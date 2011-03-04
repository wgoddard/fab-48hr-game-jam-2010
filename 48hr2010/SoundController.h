#pragma once

#include <hge.h>
#include <hgeresource.h>

class SoundController
{
public:
	SoundController(void);
	~SoundController(void);

	static void Play(char* filename);
};

