/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef LASER_H
#define LASER_H

#include "Asteroid.h"

class Laser {
    sf::CircleShape m_shape;
    float m_velX;
    float m_velY;
    float m_lifeTime;
    bool m_shouldBeDeleted;
public:
    Laser(float x, float y, float velX, float velY, float lifeTime);

    void update(const float deltaTime);
    void draw(sf::RenderWindow &window);

    bool hits(Asteroid &asteroid);

    bool shouldDelete();
    void setShouldDelete(bool b) { m_shouldBeDeleted = b; }

    float dist(float ax, float ay, float bx, float by);

    float getX() { return m_shape.getPosition().x; }
    float getY() { return m_shape.getPosition().y; }
};

#endif // LASER_H
