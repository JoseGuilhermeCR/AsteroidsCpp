/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SoundManager.h"
#include "UiManager.h"
#include "AsteroidManager.h"
#include "ParticlesManager.h"
#include "Laser.h"
#include <vector>

class Player 
{
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
    	Player(float x, float y, float maxVel, AsteroidManager& asteroidManager,
            	ParticlesManager& particleManager, UiManager& uiManager, SoundManager& soundManager);

    	void update(float deltaTime);
    	void draw(sf::RenderWindow& window);
    	void setLifeNumber(unsigned int lifeNumber);
    	void die();
    	void reset();

    	float getX();
    	float getY();
    	const sf::ConvexShape& getShapeFromPlayer();
    	bool isPlayerVulnerable();
    	unsigned int getLifeNumber();
    	long getScore();
    	std::vector<Laser>& getLasers();
};

#endif
