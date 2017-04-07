/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __ASTEROIDMANAGER_H__
#define __ASTEROIDMANAGER_H__

#include <SFML/Graphics.hpp>
#include "Asteroid.h"
#include <vector>

class AsteroidManager 
{
    	std::vector<Asteroid> m_asteroids;
    	unsigned int m_currentAsteroidNumber;
    	unsigned int m_maxAsteroidNumber;
public:
    	AsteroidManager(unsigned int maxAsteroidNumber);

    	void update(float deltaTime);
    	void draw(sf::RenderWindow& window);
    	void spawnChildAsteroid(unsigned int index);
    	void reset();

    	std::vector<Asteroid>& getAsteroids();
};

#endif
