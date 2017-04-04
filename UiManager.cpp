/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "UiManager.h"

UiManager::UiManager(const std::string& fontFilename)
    : m_font(),
      m_uiTexts(),
      m_buttons(),
      m_eventMap()
{
    // Load the font (if the font is not loaded, the game will stop running)
    assert (m_font.loadFromFile(fontFilename));

    std::string menuBtnContents[] {"Play", "Highscore", "Help", "Exit"};
    for (unsigned int i = 0; i < 4; ++i) {
        Button btn(Utils::WIDTH / 2 - 300 / 2, (i != 3) ?  i * 100 + 200 : i * 200, 300, 75,
                    sf::Color::Black, sf::Color::White, GameState::IN_MENU);
        btn.setText(menuBtnContents[i], 24, m_font, sf::Color::White);

        m_buttons.push_back(btn);
    }

    std::string highscoreBtnContents[] {"Clear Highscore", "Back"};
    for (unsigned int i = 0; i < 2; ++i) {
        Button btn(Utils::WIDTH / 2 - 300 / 2, Utils::HEIGHT / 2 + i * 100 + 50, 300, 75, sf::Color::Black,
                    sf::Color::White, GameState::IN_HIGHSCORE);
        btn.setText(highscoreBtnContents[i], 24, m_font, sf::Color::White);

        m_buttons.push_back(btn);
    }

    for (unsigned int i = 0; i < 1; ++i) {
        Button btn(Utils::WIDTH / 2 - 300 / 2, Utils::HEIGHT - 75 * 2, 300, 75,
                    sf::Color::Black, sf::Color::White, GameState::IN_GAME_OVER);
        btn.setText("Continue", 24, m_font, sf::Color::White);

        m_buttons.push_back(btn);
    }
}

void UiManager::update(const float deltaTime, const sf::Vector2i &mousePosition, GameState currentState) {
    for (unsigned int i = 0; i < m_buttons.size(); ++i) {
        if (m_buttons.at(i).getState() != currentState)
            continue;

        m_buttons.at(i).update(deltaTime, mousePosition);

        if (m_buttons.at(i).clicked()) {
            try {
                m_eventMap.at(m_buttons.at(i).getText())();
            }
            catch (std::out_of_range& orr) {
                std::cerr << "This button onClick event has no callback." << std::endl;
            }
        }
    }
}

void UiManager::draw(sf::RenderWindow &window, GameState currentState) {
    for (Text &text : m_uiTexts) {
        if (text.state != currentState || !text.visible)
            continue;

        window.draw(text.t);
    }

    for (Button &btn : m_buttons) {
        if (btn.getState() != currentState)
            continue;

        btn.draw(window);
    }
}

void UiManager::addUiText(std::string text, std::string id, unsigned int charSize, float x, float y,
                           const sf::Color &color, bool visible, GameState state) {
    for (Text &text : m_uiTexts) {
        if (id == text.id) {
            std::cout << "Id {" << id << "} is already registered!" << std::endl;
            return;
        }
    }

    Text newUiText;
    newUiText.id = id;
    newUiText.state = state;
    newUiText.visible = visible;

    newUiText.t.setFont(m_font);
    newUiText.t.setString(text);
    newUiText.t.setCharacterSize(charSize);
    newUiText.t.setPosition(x, y);
    newUiText.t.setColor(color);

    m_uiTexts.push_back(newUiText);
}

void UiManager::setText(std::string id, std::string newText) {
    for (unsigned int i = 0; i < m_uiTexts.size(); ++i) {
        if (m_uiTexts.at(i).id == id) {
            m_uiTexts.at(i).t.setString(newText);
            break;
        }
        if (i == m_uiTexts.size() - 1)
            std::cerr << "The text does not exist." << std::endl;
    }
}

void UiManager::setTextVisible(std::string id, bool b) {
    for (unsigned int i = 0; i < m_uiTexts.size(); ++i) {
        if (m_uiTexts.at(i).id == id) {
            m_uiTexts.at(i).visible = b;
            break;
        }
        if (i == m_uiTexts.size() - 1)
            std::cerr << "This text does not exist." << std::endl;
    }
}

void UiManager::setEvent(std::string buttonName, std::function<void()> callback) {
    // Insert the pair of the key and callback to the event map
    m_eventMap.insert(std::pair<std::string, std::function<void()>>(buttonName, callback));
}
