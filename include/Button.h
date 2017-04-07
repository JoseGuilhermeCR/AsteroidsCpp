/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <SFML/Graphics.hpp>
#include "GameState.h"

class Button 
{
    	sf::RectangleShape m_shape;
    	float m_width;
    	float m_height;
    	const sf::Color &m_fillColor;
    	const sf::Color &m_borderColor;
    	GameState m_gameState;
    	sf::Text m_text;
    	sf::Color m_textColor;
    	float m_delta;
    	bool m_hovered;
    	bool m_clicked;
	float m_hoverTime;
    	float m_hoverTimer;
public:
    	Button(float x, float y, float width, float height, const sf::Color& fillColor,
            	const sf::Color& borderColor, GameState gameState);

    	void update(float deltaTime, const sf::Vector2i& mousePositon);
    	void draw(sf::RenderWindow& window);
    	void setText(const std::string& text, unsigned int cSize, const sf::Font& font, const sf::Color& color);

    	bool clicked();
    	const sf::String& getText();
    	GameState getState();
};

#endif
