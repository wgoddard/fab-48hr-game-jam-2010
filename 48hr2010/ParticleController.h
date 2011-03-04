#pragma once
#include "renderable.h"

#include <hgeparticle.h>
#include <vector>

class ParticleController :
	public Renderable
{
private:
	hgeParticleManager parMan;
	std::vector<hgeParticleSystem*> systems;
public:
	ParticleController(void);
	~ParticleController(void);
	void Render();
	void Update(const float &dt);
	void AddSystem(hgeParticleSystem* newSystem, float x, float y);
};