/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef PARTICLESMANAGER_H
#define PARTICLESMANAGER_H

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

#endif // PARTICLESMANAGER_H
