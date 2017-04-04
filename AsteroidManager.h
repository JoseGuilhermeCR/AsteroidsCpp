/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H

#include <chrono>
#include <random>
#include "Asteroid.h"

class AsteroidManager {
    std::vector<Asteroid> m_asteroids;
    unsigned int m_currentAsteroidNumber;
    unsigned int m_maxAsteroidNumber;
    std::mt19937 m_random;
public:
    AsteroidManager(unsigned int maxAsteroidNumber);

    void update(const float deltaTime);
    void draw(sf::RenderWindow &window);
    void spawnChildAsteroid(unsigned int index);
    void reset();

    std::vector<Asteroid>& getAsteroids();
};

#endif // ASTEROIDMANAGER_H
