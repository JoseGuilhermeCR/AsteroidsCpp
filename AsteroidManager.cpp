/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "AsteroidManager.h"

AsteroidManager::AsteroidManager(unsigned int maxAsteroidNumber)
    : m_asteroids(),
      m_currentAsteroidNumber(0),
      m_maxAsteroidNumber(maxAsteroidNumber),
      m_random(std::chrono::system_clock::now().time_since_epoch().count())
{
    m_asteroids.reserve(maxAsteroidNumber);
}

void AsteroidManager::update(const float deltaTime) {
    if (m_currentAsteroidNumber < m_maxAsteroidNumber) {
        unsigned int asteroidToAdd = m_maxAsteroidNumber - m_currentAsteroidNumber;
        for (unsigned int i = 0; i < asteroidToAdd; ++i) {
            float x = m_random() % Utils::WIDTH;

            //if (x < 960)
                //x = -100;

            float y = m_random() % Utils::HEIGHT;

            //if (y < 720)
                //y = -300;

            float r = m_random() % 60;
            float total = m_random() % 15;

            while (r < 35)
                r = m_random() % 60;

            while (total < 5)
                total = m_random() % 15;

            std::vector<int> offsets;
            offsets.reserve(total);

            for (unsigned int i = 0; i < total; ++i) {
                int offset = m_random() % 15 - m_random() % 15;
                offsets.push_back(offset);
            }

            // Random velocity to the asteroid
            bool xNeg = static_cast<bool>(m_random() % 1);
            bool yNeg = static_cast<bool>(m_random() % 1);

            float velX = (xNeg) ? -(m_random() % 20) : m_random() % 25;
            float velY = (yNeg) ? -(m_random() % 20) : m_random() % 25;

            // A random rotation value to the asteroid
            float rotation = m_random() % 180;

            m_asteroids.push_back(Asteroid(x, y, velX, velY, r, total, rotation, offsets));
            ++m_currentAsteroidNumber;
        }
    }

    for (unsigned int i = 0; i < m_asteroids.size(); ++i) {
        m_asteroids.at(i).update(deltaTime);

        if (m_asteroids.at(i).shouldDelete()) {
            m_asteroids.erase(m_asteroids.begin() + i);
            --i;
            --m_currentAsteroidNumber;
        }
    }
}

void AsteroidManager::draw(sf::RenderWindow &window) {
    for (unsigned int i = 0; i < m_asteroids.size(); ++i) {
        m_asteroids.at(i).draw(window);
    }
}

void AsteroidManager::spawnChildAsteroid(unsigned int index) {
    m_asteroids.at(index).setToDelete(true);

    if (m_asteroids.at(index).getR() / 2 < 10)
        return;

    float x = m_asteroids.at(index).getX() + m_random() % 20;
    float y = m_asteroids.at(index).getY() + m_random() % 15;

    float r = m_asteroids.at(index).getR() * 0.5f;
    float total = m_random() % 15;

    while (total < 5)
        total = m_random() % 15;

    std::vector<int> offsets;
    offsets.reserve(total);

    for (unsigned int i = 0; i < total; ++i) {
        int offset = m_random() % 10 - m_random() % 15;
        offsets.push_back(offset);
    }

    // Random velocity to the asteroid
    bool xNeg = static_cast<bool>(m_random() % 1);
    bool yNeg = static_cast<bool>(m_random() % 1);

    float velX = (xNeg) ? -(m_random() % 20) : m_random() % 25;
    float velY = (yNeg) ? -(m_random() % 20) : m_random() % 25;

    // A random rotation value to the asteroid
    float rotation = m_random() % 360;

    m_asteroids.push_back(Asteroid(x, y, velX, velY, r, total, rotation, offsets));
    m_asteroids.push_back(Asteroid(x + m_random() % 20, y - m_random() % 20, -velX, -velY, r, total, -rotation, offsets));

    m_currentAsteroidNumber += 2;
}

std::vector<Asteroid>& AsteroidManager::getAsteroids() {
    return m_asteroids;
}

void AsteroidManager::reset() {
    m_currentAsteroidNumber = 0;
    m_asteroids.clear();
}
