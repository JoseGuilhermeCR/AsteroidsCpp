/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert> // For assert
#include <functional> // For std::function<void()>
#include "GameState.h"
#include "Utils.h"
#include "Button.h"

struct Text {
    sf::Text t;
    std::string id;
    GameState state;
    bool visible;
};

class UiManager {
    sf::Font m_font;
    std::vector<Text> m_uiTexts;
    std::vector<Button> m_buttons;

    std::map<std::string, std::function<void()>> m_eventMap;
public:
    UiManager(const std::string& fontFilename);

    void update(const float deltaTime, const sf::Vector2i &mousePosition, GameState currentState);
    void draw(sf::RenderWindow &window, GameState state);

    void addUiText(std::string text, std::string id, unsigned int charSize, float x, float y,
                    const sf::Color &color, bool visible, GameState state);

    void setText(std::string id, std::string newText);
    void setTextVisible(std::string id, bool b);

    void setEvent(std::string buttonName, std::function<void()> callback);
};

#endif // UIMANAGER_H
