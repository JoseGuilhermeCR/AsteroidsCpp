/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "include/Particles.h"
#include "include/Utils.h"

Particles::Particles(unsigned int numberOfParticles, float x, float y, float lifeTime)
    	: 
	m_particles(),
      	m_shouldBeDeleted(false)
{
    	// We add the number of particles to the vector
    	for (unsigned int i = 0; i < numberOfParticles; ++i) 
	{
        	// Create a new particle object and set it's variables values
        	Particle particle;
        	particle.lifeTime = lifeTime;
        	// Give the particle a random velocity in the X and Y axis
        	particle.velX = Utils::randomRange(0, 50);
        	particle.velY = Utils::randomRange(0, 50);
        	// Set the radius of the particle to 1 / 4
        	particle.shape.setRadius(0.25f);
        	// Set it's color
        	particle.shape.setFillColor(sf::Color::Transparent);
        	particle.shape.setOutlineColor(sf::Color::White);
        	particle.shape.setOutlineThickness(1);
        	// Set the position of the particle based on the position of the asteroid that exploded plus/minus a random offset on both
        	// axis
        	particle.shape.setPosition(x + Utils::randomRange(-30, 30), y + Utils::randomRange(-30, 30));
        	// Push the object into the vector that holds every particle for this particle system
        	m_particles.push_back(particle);
    	}
}

void Particles::update(float deltaTime)
{
    	// If the size of the vector is zero, this particle system life is over and it should be deleted
    	// we also don't need to continue the function so we return
    	if (m_particles.size() == 0)
	{
        	m_shouldBeDeleted =  true;
        	return;
    	}

    	// Loop through each particle in the particles vector
    	for (unsigned int i = 0; i < m_particles.size(); ++i)
	{
        	// Decrease it's lifetime by the amount of deltaTime
        	m_particles.at(i).lifeTime -= deltaTime;

        	// If it's lifetime is less than 0, we just remove it from the particles vector
        	if (m_particles.at(i).lifeTime < 0)
		{
            		m_particles.erase(m_particles.begin() + i);
            		--i;
            		continue;
        	}

        	// Update the particle position using it's velocity
        	m_particles.at(i).shape.move(m_particles.at(i).velX * deltaTime, m_particles.at(i).velY * deltaTime);

        	if (m_particles.at(i).shape.getOutlineColor().a > 0)
		{
            		// Get it's outline color so we can change the color's alpha value
            		sf::Color particleColor = m_particles.at(i).shape.getOutlineColor();

            		particleColor.a -= 1 / m_particles.at(i).lifeTime;

            		// Set the outline color to the changed color
            		m_particles.at(i).shape.setOutlineColor(particleColor);
        	}
    	}
}

void Particles::draw(sf::RenderWindow& window)
{
    	// Draw each particle
    	for (unsigned int i = 0; i < m_particles.size(); ++i) 
	{
        	if (m_particles.at(i).lifeTime < 0)
            		continue;
        	window.draw(m_particles.at(i).shape);
    	}
}

bool Particles::shouldDelete() 
{
    	return m_shouldBeDeleted;
}
