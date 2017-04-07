/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __BOSSMANAGER_H__
#define __BOSSMANAGER_H__

#include "Boss.h"
#include <array>

class BossManager
{
    	Player &m_player;
    	Boss m_boss;
	std::array<sf::Vector2f, 4> m_possibleSpawnLocations;
    	std::array<sf::Vector2f, 4> m_possibleVelocities;
    	bool m_bossAlive;
    	float m_timer;
    	float m_time;
public:
    	BossManager(Player& player, ParticlesManager& particlesManager);
    	void update(float deltaTime);
    	void draw(sf::RenderWindow& window);

    	void reset();
};

#endif
