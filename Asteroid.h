/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef ASTEROID_H
#define ASTEROID_H

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
    	float m_averageOffset;
    	std::vector<int> m_offsets;
    	bool m_shouldBeDeleted;
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

#endif // ASTEROID_H
