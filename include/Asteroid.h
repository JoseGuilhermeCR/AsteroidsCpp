/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <SFML/Graphics.hpp>
#include <vector>

class Asteroid 
{
    	sf::ConvexShape m_shape;
    	float m_velX;
    	float m_velY;
    	float m_r;
    	float m_total;
    	float m_rotation;
    	std::vector<int> m_offsets;
    	bool m_shouldBeDeleted;
	float m_averageOffset;
public:
    	Asteroid(float x, float y, float velX, float velY, float r, float total, float rotation, const std::vector<int> &offsets);

    	void update(const float deltaTime);
    	void draw(sf::RenderWindow& window);
    	void setToDelete(bool b);

    	bool shouldDelete();
    	float getX();
    	float getY();
    	float getR();
    	float getAverageOffset();
};

#endif
