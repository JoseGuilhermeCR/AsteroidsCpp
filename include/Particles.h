/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include <SFML/Graphics.hpp>
#include <vector>

// The same as a class but it has public members by default
struct Particle 
{
    	sf::CircleShape shape;
    	float lifeTime;
    	float velX;
    	float velY;
};

// This is the container for the particle struct
class Particles 
{
    	std::vector<Particle> m_particles;
    	bool m_shouldBeDeleted;
public:
    	Particles(unsigned int numberOfParticles, float x, float y, float lifeTime);
    	void update(float deltaTime);
    	void draw(sf::RenderWindow& window);

    	bool shouldDelete();
};

#endif
