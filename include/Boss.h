/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __BOSS_H__
#define __BOSS_H__

#include <SFML/Graphics.hpp>
#include "Laser.h"
#include "Player.h"

class Boss 
{
    	sf::ConvexShape m_shape;
    	sf::RectangleShape m_line1;
    	sf::RectangleShape m_line2;
    	float m_velX;
    	float m_velY;
    	std::vector<Laser> m_lasers;
    	float m_laserVel;
    	float m_shootRate;
    	float m_shootTimer;
	ParticlesManager &m_particleManager;
	Player &m_player;
public:
    	Boss(ParticlesManager& particleManager, Player& player);

    	void update(float deltaTime);
    	void draw(sf::RenderWindow& window);
    	void setPosition(float x, float y) { m_shape.setPosition(x, y); }
    	void setVelocity(float vX, float vY) { m_velX = vX; m_velY = vY; }
	void reset();

    	const sf::ConvexShape& getShape();
    	const sf::Vector2f& getPosition();
};

#endif
