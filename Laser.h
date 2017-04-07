/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>
#include "Asteroid.h"

class Laser 
{
    	sf::CircleShape m_shape;
    	float m_velX;
    	float m_velY;
    	float m_lifeTime;
    	bool m_shouldBeDeleted;
public:
    	Laser(float x, float y, float velX, float velY, float lifeTime);

    	void update(float deltaTime);
    	void draw(sf::RenderWindow& window);
    	void setShouldDelete(bool b);

    	bool hits(Asteroid& asteroid);
    	bool shouldDelete(); 
    	float getX();
    	float getY();
};

#endif // LASER_H
