/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H

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

#endif // ASTEROIDMANAGER_H
