/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "include/ParticlesManager.h"

ParticlesManager::ParticlesManager()
    	: 
	m_particles()
{
}

void ParticlesManager::update(float deltaTime)
{
    	// Iterate over each particle system and update it
    	for (unsigned int i = 0; i < m_particles.size(); ++i)
	{
        	m_particles.at(i).update(deltaTime);

        	if (m_particles.at(i).shouldDelete())
		{
            		m_particles.erase(m_particles.begin() + i);
            		--i;
            		continue;
        	}
    	}
}

void ParticlesManager::draw(sf::RenderWindow& window)
{
    	// Draw the particle effects if needed
    	for (unsigned int i = 0; i < m_particles.size(); ++i)
	{
        	m_particles.at(i).draw(window);
    	}
}

void ParticlesManager::reset()
{
    	m_particles.clear();
}

void ParticlesManager::spawnParticleSystem(unsigned int number, float x, float y, float lifeTime) 
{
    	m_particles.push_back(Particles(number, x, y, lifeTime));
}
