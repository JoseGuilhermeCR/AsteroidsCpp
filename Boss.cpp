/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "Boss.h"

Boss::Boss(ParticlesManager &particleManager)
    : m_shape(),
      m_line1(),
      m_line2(),
      m_velX(20),
      m_velY(20),
      m_lasers(),
      m_laserVel(300),
      m_shootRate(2),
      m_particleManager(particleManager)
{
    m_shape.setPointCount(8);

    m_shape.setPoint(0, sf::Vector2f(0, 0));
    m_shape.setPoint(1, sf::Vector2f(20, 20));
    m_shape.setPoint(2, sf::Vector2f(80, 20));
    m_shape.setPoint(3, sf::Vector2f(100, 0));
    m_shape.setPoint(4, sf::Vector2f(70, -20));
    m_shape.setPoint(5, sf::Vector2f(60, -35));
    m_shape.setPoint(6, sf::Vector2f(40, -35));
    m_shape.setPoint(7, sf::Vector2f(30, -20));

    m_shape.setPosition(300, 300);
    m_shape.setOutlineThickness(1);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setFillColor(sf::Color::Transparent);

    m_line1.setFillColor(sf::Color::White);
    m_line2.setFillColor(sf::Color::White);

    m_line1.setSize(sf::Vector2f(40, 1));
    m_line1.setPosition(m_shape.getPosition().x - 50 + 30, m_shape.getPosition().y - 20);

    m_line2.setSize(sf::Vector2f(100, 1));
    m_line2.setPosition(m_shape.getPosition().x - 50, m_shape.getPosition().y);

    m_shape.setOrigin(50, 0);
}

void Boss::update(const float deltaTime, Player &player) {
    float x = m_shape.getPosition().x;
    float y = m_shape.getPosition().y;

    // Movement
    x += m_velX * deltaTime;
    y += m_velY * deltaTime;

    if (x > Utils::WIDTH)
        x = 0;
    else if (x < 0)
        x = Utils::WIDTH;

    if (y > Utils::HEIGHT)
        y = 0;
    else if (y < 0)
        y = Utils::HEIGHT;

    m_shape.setPosition(x, y);

    // Set the position of the lines that are inside the boss shape
    m_line1.setPosition(x - 50 + 30, y - 20);
    m_line2.setPosition(x - 50, y);

    if (player.isPlayerVulnerable()) {
        // Shoot
        m_shootTimer += deltaTime;
        if (m_shootTimer > m_shootRate) {
            float pX = player.getX();
            float pY = player.getY();

            float difX = pX - x;
            float difY = pY - y;

            // The length of a vector from this point to the player position
            float dist = sqrt(difX * difX + difY * difY);

            difX /= dist;
            difY /= dist;

            difX *= m_laserVel;
            difY *= m_laserVel;

            m_lasers.push_back(Laser(x, y, difX, difY, 3));

            m_shootTimer = 0;
        }
    }

    const sf::ConvexShape &playerShape = player.getShapeFromPlayer();
    // Update the lasers
    for (unsigned int i = 0; i < m_lasers.size(); ++i) {
        m_lasers.at(i).update(deltaTime);

        for (unsigned int j = 0; j < playerShape.getPointCount(); ++j) {
            sf::Vector2f point = playerShape.getPoint(j);

            float dist = sqrt(pow(m_lasers.at(i).getX() - (player.getX() + point.x), 2) + pow(m_lasers.at(i).getY() - (player.getY() + point.y), 2));

            if (dist < 15) {
                m_lasers.at(i).setShouldDelete(true);
                m_particleManager.spawnParticleSystem(15, m_lasers.at(i).getX(), m_lasers.at(i).getY(), 3);
                player.die();
            }
        }

        if (m_lasers.at(i).shouldDelete()) {
            m_lasers.erase(m_lasers.begin() + i);
            --i;
            continue;
        }
    }
}

void Boss::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
    window.draw(m_line1);
    window.draw(m_line2);

    for (unsigned int i = 0; i < m_lasers.size(); ++i) {
        m_lasers.at(i).draw(window);
    }
}

void Boss::reset() {
    m_lasers.clear();
}
