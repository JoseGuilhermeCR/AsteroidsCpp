/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "include/Button.h"

Button::Button(float x, float y, float width, float height, const sf::Color& fillColor,
                const sf::Color& borderColor, GameState gameState)
    	: 
	m_shape(),
      	m_width(width),
      	m_height(height),
      	m_fillColor(fillColor),
      	m_borderColor(borderColor),
      	m_gameState(gameState),
      	m_text(),
      	m_textColor(),
      	m_delta(0),
      	m_hovered(false),
      	m_clicked(false),
      	m_hoverTime(0.5),
      	m_hoverTimer(0)
{
    	m_shape.setPosition(x, y);
    	m_shape.setSize(sf::Vector2f(width, height));

    	m_shape.setFillColor(m_fillColor);
    	m_shape.setOutlineColor(m_borderColor);
    	m_shape.setOutlineThickness(1);
}

void Button::update(float deltaTime, const sf::Vector2i& mousePosition)
{
    	m_clicked = false;
    	m_hovered = false;
    	// Check if the button is currently being hovered
    	if (mousePosition.x > m_shape.getPosition().x && mousePosition.x < m_shape.getPosition().x + m_shape.getSize().x)
        	if (mousePosition.y > m_shape.getPosition().y && mousePosition.y < m_shape.getPosition().y + m_shape.getSize().y)
            		m_hovered = true;

    	if (m_hovered)
        	m_hoverTimer += deltaTime;

    	if (m_hovered)
	{
        	float nWidth = m_shape.getSize().x + sin(m_delta) * 10;

        	if (nWidth < m_width)
            		nWidth = m_width;

        	m_shape.setSize(sf::Vector2f(nWidth, m_height));
        	m_delta += 0.1;
    	}
    	else 
	{
        	m_shape.setSize(sf::Vector2f(m_width, m_height));
		m_delta = 0;
    	}

    	// Check if the user clicked while hovering the button
    	if (m_hovered && m_hoverTimer > m_hoverTime)
	{
        	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
            		m_clicked = true;
            		m_hoverTimer = 0;
        	}
    	}
}

void Button::draw(sf::RenderWindow& window)
{
    	window.draw(m_shape);
    	window.draw(m_text);
}

void Button::setText(const std::string& text, unsigned int cSize, const sf::Font& font, const sf::Color& color)
{
    	m_text.setCharacterSize(cSize);
    	m_text.setFont(font);
    	m_text.setColor(color);
    	m_text.setString(text);
    	m_text.setPosition(m_shape.getPosition().x + m_width / 4, m_shape.getPosition().y + m_height / 4);
    	m_textColor = color;
}

bool Button::clicked()
{
	return m_clicked;
}

const sf::String& Button::getText()
{
	return m_text.getString();
}

GameState Button::getState()
{
	return m_gameState;
}
