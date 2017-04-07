/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "include/AsteroidManager.h"
#include "include/Utils.h"

AsteroidManager::AsteroidManager(unsigned int maxAsteroidNumber)
    	: 
	m_asteroids(),
      	m_currentAsteroidNumber(0),
      	m_maxAsteroidNumber(maxAsteroidNumber)
{
	m_asteroids.reserve(maxAsteroidNumber);
}

void AsteroidManager::update(float deltaTime) {
	if (m_currentAsteroidNumber < m_maxAsteroidNumber) 
	{
		unsigned int asteroidToAdd = m_maxAsteroidNumber - m_currentAsteroidNumber;
		for (unsigned int i = 0; i < asteroidToAdd; ++i) 
		{
			float x = Utils::randomRange(0, Utils::WIDTH);

            		float y = Utils::randomRange(0, Utils::HEIGHT);

            		float r = Utils::randomRange(35, 60);
            		float total = Utils::randomRange(5, 15);

            		std::vector<int> offsets;
            		offsets.reserve(total);

            		for (unsigned int i = 0; i < total; ++i) 
			{
                		int offset = Utils::randomRange(-10, 10);
                		offsets.push_back(offset);
            		}

            		// Random velocity to the asteroid
            		float velX = Utils::randomRange(-25, 25);
            		float velY = Utils::randomRange(-25, 25);

            		// A random rotation value to the asteroid
            		float rotation = Utils::randomRange(0, 180);

            		m_asteroids.push_back(Asteroid(x, y, velX, velY, r, total, rotation, offsets));
            		++m_currentAsteroidNumber;
        	}
    	}

    	for (unsigned int i = 0; i < m_asteroids.size(); ++i) 
	{
        	m_asteroids.at(i).update(deltaTime);

        	if (m_asteroids.at(i).shouldDelete()) 
		{
            		m_asteroids.erase(m_asteroids.begin() + i);
            		--i;
            		--m_currentAsteroidNumber;
        	}
    	}
}

void AsteroidManager::draw(sf::RenderWindow& window)
{
    	for (unsigned int i = 0; i < m_asteroids.size(); ++i) 
	{
        	m_asteroids.at(i).draw(window);
    	}
}

void AsteroidManager::spawnChildAsteroid(unsigned int index) 
{
	m_asteroids.at(index).setToDelete(true);

    	float radius = m_asteroids.at(index).getR();

    	if (radius / 2 < 10)
        	return;

    	float x = m_asteroids.at(index).getX() + Utils::randomRange(-radius, radius);
    	float y = m_asteroids.at(index).getY() + Utils::randomRange(-radius, radius);

    	float r = radius * 0.5f;
    	float total = Utils::randomRange(5, 15);

    	std::vector<int> offsets;
    	offsets.reserve(total);

    	for (unsigned int i = 0; i < total; ++i) 
	{
        	int offset = Utils::randomRange(-5, 10);
        	offsets.push_back(offset);
    	}

    	// Random velocity to the asteroid
    	float velX = Utils::randomRange(-25, 25);
    	float velY = Utils::randomRange(-25, 25);

    	// A random rotation value to the asteroid
    	float rotation = Utils::randomRange(0, 270);

    	m_asteroids.push_back(Asteroid(x, y, velX, velY, r, total, rotation, offsets));
    	m_asteroids.push_back(Asteroid(x + Utils::randomRange(-r, r), y + Utils::randomRange(-r, r), -velX, -velY, r, total, -rotation, offsets));

    	m_currentAsteroidNumber += 2;
}

std::vector<Asteroid>& AsteroidManager::getAsteroids() 
{
    	return m_asteroids;
}

void AsteroidManager::reset() 
{
    	m_currentAsteroidNumber = 0;
    	m_asteroids.clear();
}
