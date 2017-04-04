/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

class Asteroid {
    sf::ConvexShape m_shape;
    float m_velX;
    float m_velY;
    float m_r;
    float m_total;
    float m_rotation;
    float m_averageOffset;
    std::vector<int> m_offsets;
    bool m_shouldBeDeleted;
public:
    Asteroid(float x, float y, float velX, float velY, float r, float total, float rotation, const std::vector<int> &offsets);

    void update(const float deltaTime);
    void draw(sf::RenderWindow &window);
    void setToDelete(bool b);

    float mapNumber(float value, float start1, float stop1, float start2, float stop2);

    bool shouldDelete() { return m_shouldBeDeleted; }
    float getX() { return m_shape.getPosition().x; }
    float getY() { return m_shape.getPosition().y; };
    float getR() { return m_r; }

    float getAverageOffset() { return m_averageOffset; }
};

#endif // ASTEROID_H
