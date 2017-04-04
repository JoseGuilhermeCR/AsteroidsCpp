/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "Laser.h"

Laser::Laser(float x, float y, float velX, float velY, float lifeTime)
    : m_shape(2),
      m_velX(velX),
      m_velY(velY),
      m_lifeTime(lifeTime),
      m_shouldBeDeleted(false)
{
    m_shape.setPosition(x, y);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(1);
    m_shape.setFillColor(sf::Color::Transparent);
}

void Laser::update(const float deltaTime) {
    float x = m_shape.getPosition().x;
    float y = m_shape.getPosition().y;

    x += m_velX * deltaTime;
    y += m_velY * deltaTime;

    if (x > Utils::WIDTH - m_shape.getRadius())
        x = 0;
    else if (x < 0)
        x = Utils::WIDTH - m_shape.getRadius();

    if (y > Utils::HEIGHT - m_shape.getRadius())
        y = 0;
    else if (y < 0)
        y = Utils::HEIGHT - m_shape.getRadius();

    m_shape.setPosition(x, y);

    m_lifeTime -= deltaTime;
    if (m_lifeTime < 0)
        m_shouldBeDeleted = true;
}

void Laser::draw(sf::RenderWindow &window) {
    // Draw the shape
    window.draw(m_shape);
}

bool Laser::hits(Asteroid &asteroid) {
    float distance = dist(m_shape.getPosition().x, m_shape.getPosition().y, asteroid.getX(), asteroid.getY());
    if (distance < asteroid.getR()) {
        m_shouldBeDeleted = true;
        return true;
    }
    return false;
}

bool Laser::shouldDelete() {
    return m_shouldBeDeleted;
}

float Laser::dist(float ax, float ay, float bx, float by) {
    return (float)sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
}
