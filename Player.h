/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <sstream>
#include "SoundManager.h"
#include "Utils.h"
#include "UiManager.h"
#include "AsteroidManager.h"
#include "ParticlesManager.h"
#include "Laser.h"

class Player {
    sf::ConvexShape m_shape;
    float m_maxVel;
    float m_velX;
    float m_velY;
    bool m_canShoot;
    float m_shootRate;
    float m_shootTimer;
    long m_score;
    unsigned int m_lives;
    AsteroidManager &m_asteroidManager;
    ParticlesManager &m_particleManager;
    UiManager &m_uiManager;
    SoundManager &m_soundManager;
    std::vector<Laser> m_lasers;
    bool m_vulnerable;
    float m_vulnerableTimer;
    float m_vulnerableTime;
public:
    Player(float x, float y, float maxVel, AsteroidManager &asteroidManager,
            ParticlesManager &particleManager, UiManager &uiManager, SoundManager &soundManager);

    void update(const float deltaTime);
    void draw(sf::RenderWindow &window);
    void setLifeNumber(unsigned int lifeNumber);
    void die();
    void reset();

    template <typename T> std::string to_string(const T &n);

    float getX() { return m_shape.getPosition().x; }
    float getY() { return m_shape.getPosition().y; }

    // unsigned int getPlayerPointCount() { return m_shape.getPointCount(); }
    const sf::ConvexShape& getShapeFromPlayer() { return m_shape; }

    bool isPlayerVulnerable() { return m_vulnerable; }
    unsigned int getLifeNumber() { return m_lives; }
    long getScore() { return m_score; }

    std::vector<Laser>& getLasers() { return m_lasers; }
};

#endif // PLAYER_H
