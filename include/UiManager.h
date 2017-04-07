/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional> // For std::function<void()>
#include "GameState.h"
#include "Utils.h"
#include "Button.h"

struct Text 
{
    	sf::Text t;
    	std::string id;
    	GameState state;
    	bool visible;
};

class UiManager 
{
    	sf::Font m_font;
    	std::vector<Text> m_uiTexts;
    	std::vector<Button> m_buttons;
    	std::map<std::string, std::function<void()>> m_eventMap;
public:
   	UiManager(const std::string& fontFilename);

    	void update(float deltaTime, const sf::Vector2i& mousePosition, GameState currentState);
    	void draw(sf::RenderWindow& window, GameState state);
    	void addUiText(const std::string& text, const std::string& id, unsigned int charSize, float x, float y, 
							const sf::Color& color, bool visible, GameState state);
    	void setText(const std::string& id, const std::string& newText);
    	void setTextVisible(const std::string& id, bool b);
    	void setEvent(const std::string& eventName, std::function<void()> callback);
};

#endif
