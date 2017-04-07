/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "Player.h"
#include "Utils.h"

Player::Player(float x, float y, float maxVel, AsteroidManager& asteroidManager,
                ParticlesManager& particleManager, UiManager& uiManager, SoundManager& soundManager)
    	: 
	m_shape(3),
      	m_maxVel(maxVel),
      	m_velX(0),
      	m_velY(0),
      	m_canShoot(false),
      	m_shootRate(0.25f),
      	m_shootTimer(0),
      	m_score(0),
      	m_lives(3),
      	m_asteroidManager(asteroidManager),
      	m_particleManager(particleManager),
      	m_uiManager(uiManager),
      	m_soundManager(soundManager),
      	m_lasers(),
      	m_vulnerable(true),
      	m_vulnerableTimer(0),
      	m_vulnerableTime(3)
{
    	m_shape.setPoint(0, sf::Vector2f(0, 40));
    	m_shape.setPoint(1, sf::Vector2f(60, 20));
    	m_shape.setPoint(2, sf::Vector2f(0, 0));

    	// Set the origin to the 'nose' of the triangle, so we rotate from that point
    	//m_shape.setOrigin(m_shape.getPoint(1));
    	// Set the origin to the center of the triangle, so we rotate from that point
    	m_shape.setOrigin(30, 20);

    	m_shape.setOutlineColor(sf::Color::White);
    	m_shape.setOutlineThickness(1);
    	m_shape.setFillColor(sf::Color::Transparent);
    	m_shape.setPosition(x, y);

    	// Reserve space for at least 20 laser objects
    	m_lasers.reserve(20);
}

void Player::update(float deltaTime)
{
    	std::vector<Asteroid> &asteroids = m_asteroidManager.getAsteroids();

    	// Store the x and y in a temp var to make the code simpler
    	float x = m_shape.getPosition().x;
    	float y = m_shape.getPosition().y;

    	// Getting a vector from an angle
    	// Vector.x = cos(rotationInRadians)
    	// Vector.y = sin(rotationInRadians)
    	// The inverse would be angle = atan2(Vector.y, Vector.x)
    	float dirX = cos(m_shape.getRotation() * 3.14 / 180);
    	float dirY = sin(m_shape.getRotation() * 3.14 / 180);

    	bool accelerated = false;
    	// Move forward
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
	{
        	m_velX += dirX;
        	m_velY += dirY;

        	// The player has accelerated this frame
        	accelerated = true;
    	}

    	// If the absolute value of the velocity on one of the axis is bigger than the maxVelocity
    	// we subtract what was added this frame so it won't be bigger anymore
    	if (fabs(m_velX) > m_maxVel)
        	m_velX -= dirX;

    	if (fabs(m_velY) > m_maxVel)
        	m_velY -= dirY;

    	// Adds the dirX and dirY times a velocity, without it, the player wouldn't be able to move
    	//x += dirX * m_vel;
    	//y += dirY * m_vel;
    	x += m_velX;
    	y += m_velY;

    	// Check for left/right movement
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
        	m_shape.rotate(360 * deltaTime);
	}
    	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
        	m_shape.rotate(-360 * deltaTime);
    	}

    	// If the player crosses the side of the screen it will appear on the other side
    	if (x > Utils::WIDTH)
        	x = 0;
    	else if (x < 0)
        	x = Utils::WIDTH;

    	if (y > Utils::HEIGHT)
        	y = 0;
    	else if (y < 0)
        	y = Utils::HEIGHT;

    	if (m_vulnerable) 
	{
        	// Check for collision between player and asteroids
        	for (Asteroid &asteroid : asteroids) 
		{
            		for (unsigned int i = 0; i < m_shape.getPointCount(); ++i) 
			{
                		sf::Vector2f point = m_shape.getPoint(i);
                		float d = Utils::dist(asteroid.getX(), m_shape.getPosition().x + point.x, asteroid.getY(), m_shape.getPosition().y + point.y);
                		if (d < asteroid.getR() + asteroid.getAverageOffset()) 
				{
                    			x = Utils::WIDTH / 2;
                    			y = Utils::HEIGHT / 2;
                    			m_shape.setRotation(360);
                    			m_velX = 0;
                    			m_velY = 0;
                    			m_canShoot = false;
                    			m_shootTimer = 0;
                    			m_lasers.clear();
                    			setLifeNumber(--m_lives);
                    			m_vulnerable = false;
                    			break;
              			}
            		}
        	}
   	}
    	else 
   	{
        	m_vulnerableTimer += deltaTime;
        	if (m_vulnerableTimer > m_vulnerableTime)
		{
            		m_vulnerableTimer = 0;
            		m_vulnerable = true;
        	}
    	}

    	// Set the position after all the calculation is done
    	m_shape.setPosition(x, y);

    	if (!accelerated)
	{
        	if (m_velX < 0)
            		m_velX += 0.02f;
        	else if (m_velX > 0)
            		m_velX -= 0.02f;

        	if (m_velY < 0)
            		m_velY += 0.02f;
        	else if (m_velY > 0)
            		m_velY -= 0.02f;
    	}

    	// If it can not shoot, then we start reloading the weapon
    	if (!m_canShoot)
	{
        	m_shootTimer += deltaTime;
        	if (m_shootTimer > m_shootRate)
		{
            		m_canShoot = true;
        	}
    	}

    	// If it can shoot, we check if the player has pressed the space bar
    	// if he/she has, we spawn the laser and reset can shoot to false and the timer to 0
    	if (m_canShoot)
	{
        	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
            		m_lasers.push_back(Laser(x, y, dirX * 800, dirY * 800, 1));
            		m_shootTimer = 0;
            		m_canShoot = false;
        	}
    	}

    	// Iterate through each laser in the array and update them
    	for (unsigned int i = 0; i < m_lasers.size(); ++i)
	{
        	m_lasers.at(i).update(deltaTime);

        	// If the laser is marked as shouldBeDeleted, we delete it and decrement i, so the loop doesn't go past the
        	// new length of the vector, and finally we continue the loop so we don't do what's after this statement
        	if (m_lasers.at(i).shouldDelete())
		{
            		m_lasers.erase(m_lasers.begin() + i);
            		--i;
            		continue;
        	}

        	// Iterate through each asteroid to see if any of them is colliding with the laser
        	for (unsigned int j = 0; j < asteroids.size(); ++j)
		{
            		// If the laser hits any asteroid, we spawn the child and increment the player score
            		if (m_lasers.at(i).hits(asteroids.at(j)))
			{
                		int val = asteroids.at(j).getR() / 2;
                		m_score += val;
                		m_particleManager.spawnParticleSystem(15, asteroids.at(j).getX(), asteroids.at(j).getY(), 2);
                		m_asteroidManager.spawnChildAsteroid(j);
                		m_uiManager.setText("ingame_scorecount", "Score: " + std::to_string(m_score));
            		}
        	}
    	}
}

void Player::draw(sf::RenderWindow& window)
{
    	//window.setView(sf::View(m_shape.getPosition(), sf::Vector2f(960, 540)));
    	// Draw the shape
    	if (!m_vulnerable)
        	m_shape.setFillColor(sf::Color::White);
    	else
        	m_shape.setFillColor(sf::Color::Black);
    	window.draw(m_shape);

    	// Draw the lasers if needed
    	for (unsigned int i = 0; i < m_lasers.size(); ++i)
	{
        	m_lasers.at(i).draw(window);
    	}
}

void Player::setLifeNumber(unsigned int lifeNumber)
{
    	m_uiManager.setText("ingame_lifecount", "Lifes: " + std::to_string(lifeNumber));
    	m_lives = lifeNumber;
}

void Player::die()
{
    	m_shape.setPosition(Utils::WIDTH / 2, Utils::HEIGHT / 2);
    	m_shape.setRotation(360);
    	m_velX = 0;
    	m_velY = 0;
    	m_canShoot = false;
    	m_shootTimer = 0;
    	m_lasers.clear();
    	setLifeNumber(--m_lives);
    	m_vulnerable = false;
}

void Player::reset()
{
    	m_uiManager.setText("ingame_lifecount", "Lifes: 3");
    	m_uiManager.setText("ingame_scorecount", "Score: 0");

    	m_shape.setPosition(Utils::WIDTH / 2, Utils::HEIGHT / 2);
    	m_shape.setRotation(360);
    	m_score = 0;
    	m_lives = 3;
    	m_velX = 0;
    	m_velY = 0;
    	m_canShoot = false;
    	m_shootTimer = 0;
    	m_vulnerable = true;

    	m_lasers.clear();
}
