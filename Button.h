/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "GameState.h"

class Button {
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
    float m_hoverTimer;
    float m_hoverTime;
public:
    Button(float x, float y, float width, float height, const sf::Color &fillColor,
            const sf::Color &borderColor, GameState gameState);

    void update(const float deltaTime, const sf::Vector2i &mousePositon);
    void draw(sf::RenderWindow &window);
    void setText(std::string text, unsigned int cSize, const sf::Font &font, const sf::Color &color);

    bool clicked() { return m_clicked; }
    const sf::String& getText() { return m_text.getString(); }
    GameState getState() { return m_gameState; }
};

#endif // BUTTON_H
