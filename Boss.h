/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Laser.h"
#include "Player.h"

class Boss {
    sf::ConvexShape m_shape;
    sf::RectangleShape m_line1;
    sf::RectangleShape m_line2;
    float m_velX;
    float m_velY;
    std::vector<Laser> m_lasers;
    float m_laserVel;
    float m_shootRate;
    ParticlesManager &m_particleManager;

    float m_shootTimer;
public:
    Boss(ParticlesManager &particleManager);
    void update(const float deltaTime, Player &player);
    void draw(sf::RenderWindow &window);

    void setPosition(float x, float y) { m_shape.setPosition(x, y); }
    void setVelocity(float vX, float vY) { m_velX = vX; m_velY = vY; }

    const sf::ConvexShape& getShape() { return m_shape; }

    const sf::Vector2f& getPosition() { return m_shape.getPosition(); }

    void reset();
};

#endif // BOSS_H
