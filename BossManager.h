/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef BOSSMANAGER_H
#define BOSSMANAGER_H

#include "Boss.h"
#include "Utils.h"
#include <iostream>
#include <chrono>
#include <random>
#include <array>

class BossManager {
    Player &m_player;
    Boss m_boss;

    std::array<sf::Vector2f, 4> m_possibleSpawnLocations;
    std::array<sf::Vector2f, 4> m_possibleVelocities;

    std::mt19937 m_random;

    bool m_bossAlive;
    float m_timer;
    float m_time;
public:
    BossManager(Player &player, ParticlesManager &particlesManager);
    void update(const float deltaTime);
    void draw(sf::RenderWindow &window);

    void reset();
};

#endif // BOSSMANAGER_H
