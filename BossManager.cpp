/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "BossManager.h"

BossManager::BossManager(Player &player, ParticlesManager &particlesManager)
    : m_player(player),
      m_boss(particlesManager),
      m_possibleSpawnLocations(),
      m_possibleVelocities(),
      m_random(std::chrono::system_clock::now().time_since_epoch().count()),
      m_bossAlive(false),
      m_timer(5),
      m_time(m_timer)
{
    // Sets all the possible positions that the boss can spawn in
    m_possibleSpawnLocations.at(0) = sf::Vector2f(0, 0);
    m_possibleSpawnLocations.at(1) = sf::Vector2f(Utils::WIDTH, 0);
    m_possibleSpawnLocations.at(2) = sf::Vector2f(0, Utils::HEIGHT);
    m_possibleSpawnLocations.at(3) = sf::Vector2f(Utils::WIDTH, Utils::HEIGHT);

    // Sets all the possible velocities that the boss can have
    m_possibleVelocities.at(0) = sf::Vector2f(20, 20);
    m_possibleVelocities.at(1) = sf::Vector2f(-20, -20);
    m_possibleVelocities.at(2) = sf::Vector2f(-20, 20);
    m_possibleVelocities.at(3) = sf::Vector2f(20, -20);

    // Select a random position and velocity
    sf::Vector2f position = m_possibleSpawnLocations.at(m_random() % 3);
    sf::Vector2f velocity = m_possibleVelocities.at(m_random() % 3);

    // Apply the random selected position and velocity to the boss
    m_boss.setPosition(position.x, position.y);
    m_boss.setVelocity(velocity.x, velocity.y);
}

void BossManager::update(const float deltaTime) {
    if (!m_bossAlive)
        m_timer -= deltaTime;

    // If the timer is bigger than the time, we should spawn the boss
    // and set timer to 0 again
    if (m_timer < 0 && !m_bossAlive) {
        m_bossAlive = true;
        m_timer = m_time;
    }

    // We only update the boss if it is alive
    if (m_bossAlive) {
        std::vector<Laser>& playerLasers = m_player.getLasers();
        const sf::ConvexShape& m_bossShape = m_boss.getShape();

        m_boss.update(deltaTime, m_player);

        for (unsigned int i = 0; i < playerLasers.size(); ++i) {
            sf::Vector2f pos(playerLasers.at(i).getX(), playerLasers.at(i).getY());

            for (unsigned int j = 0; j < m_bossShape.getPointCount(); ++j) {
                sf::Vector2f point = m_bossShape.getPoint(j);

                float dist = sqrt(pow((m_boss.getPosition().x + point.x) - pos.x, 2) + pow((m_boss.getPosition().y + point.y) - pos.y, 2));

                if (dist < 5) {
                    playerLasers.at(i).setShouldDelete(true);
                    reset();
                    break;
                }
            }
        }
    }
}

void BossManager::draw(sf::RenderWindow &window) {
    // We only draw the boss if it is alive
    if (m_bossAlive)
        m_boss.draw(window);
}

void BossManager::reset() {
    // Boss is not alive anymore, so we change it to false
    m_bossAlive = false;
    m_timer = m_time;

    // New velocity and position to the boss
    sf::Vector2f position = m_possibleSpawnLocations.at(m_random() % 3);
    sf::Vector2f velocity = m_possibleVelocities.at(m_random() % 3);

    // Apply the position and velocity and call the boss reset function
    m_boss.setPosition(position.x, position.y);
    m_boss.setVelocity(velocity.x, velocity.y);
    m_boss.reset();
}
