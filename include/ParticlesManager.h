/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __PARTICLESMANAGER_H__
#define __PARTICLESMANAGER_H__

#include <vector>
#include "Particles.h"

class ParticlesManager 
{
    	std::vector<Particles> m_particles;
public:
    	ParticlesManager();

    	void update(float deltaTime);
    	void draw(sf::RenderWindow& window);
    	void reset();

    	void spawnParticleSystem(unsigned int number, float x, float y, float lifeTime);
};

#endif
