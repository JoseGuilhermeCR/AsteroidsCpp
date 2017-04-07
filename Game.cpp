/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "include/Game.h"
#include "include/Utils.h"
#include <string>

Game::Game()
    	:
	m_window(sf::VideoMode(Utils::WIDTH, Utils::HEIGHT), "Asteroids", sf::Style::Close),
      	m_clock(),
      	m_soundManager(),
      	m_uiManager("Roboto-Regular.ttf"),
      	m_highscoreManager(),
      	m_particleManager(),
      	m_asteroidManager(5),
      	m_player(Utils::WIDTH / 2, Utils::HEIGHT / 2, 5, m_asteroidManager, m_particleManager, m_uiManager, m_soundManager),
      	m_bossManager(m_player, m_particleManager),
      	m_deltaTime(0),
      	m_paused(false),
      	m_currentState(GameState::IN_MENU)
{
    	m_window.setFramerateLimit(60);

    	// Load sounds
    	//m_soundManager.addSound("test", "test.wav");

    	// Menu Texts
    	m_uiManager.addUiText("ASTEROIDS", "menu_title", 64, 325, 100,
                           	sf::Color::White, true, GameState::IN_MENU);
    	m_uiManager.addUiText("Developed by JoseGuilhermeCR", "menu_develop",
                           	18, 5, 690, sf::Color::White, true, GameState::IN_MENU);
    	m_uiManager.addUiText("Version: 1.00", "menu_version",
                           	18, 850, 690, sf::Color::White, true, GameState::IN_MENU);

    	// In Game Texts
    	m_uiManager.addUiText("Lifes: 3", "ingame_lifecount", 18, 5, 5,
                          	sf::Color::White, true, GameState::IN_GAME);
    	m_uiManager.addUiText("Score: 0", "ingame_scorecount", 18, 5, 25,
                          	sf::Color::White, true, GameState::IN_GAME);
    	m_uiManager.addUiText("Paused!", "ingame_paused", 64, Utils::WIDTH / 2 - 64,
                          	Utils::HEIGHT / 2 - 64, sf::Color::White, false, GameState::IN_GAME);

    	// GameOver Texts
    	m_uiManager.addUiText("Game Over!", "gameover_title", 64,
                          	Utils::WIDTH / 2 - 128, Utils::HEIGHT / 2 - 64, sf::Color::Red, true,
                          	GameState::IN_GAME_OVER);
    	m_uiManager.addUiText("Your score:", "gameover_scored", 32,
                          	Utils::WIDTH / 2 - 128, Utils::HEIGHT / 2 + 64, sf::Color::Red, true,
                          	GameState::IN_GAME_OVER);
    	m_uiManager.addUiText("New highscore:", "gameover_newhighscore", 32,
                          	Utils::WIDTH / 2 - 128, Utils::HEIGHT / 2 + 128, sf::Color::Green, false,
                          	GameState::IN_GAME_OVER);

    	// Highscore Texts
    	m_uiManager.addUiText("Highscore: " + std::to_string(m_highscoreManager.getSavedScore()), "highscore_highscore", 64,
                          	Utils::WIDTH / 2 - 128, Utils::HEIGHT / 2 - 64, sf::Color::White, true,
                          	GameState::IN_HIGHSCORE);

    	// Help Texts
    	m_uiManager.addUiText("Controls: ", "help_controls", 64, 64, 64, sf::Color::White, true, GameState::IN_HELP);
    	m_uiManager.addUiText("A - rotate to the left", "help_a", 32, 64, 132, sf::Color::White, true, GameState::IN_HELP);
    	m_uiManager.addUiText("D - rotate to the right ", "help_d", 32, 64, 196, sf::Color::White, true, GameState::IN_HELP);
    	m_uiManager.addUiText("W - move forward", "help_w", 32, 64, 256, sf::Color::White, true, GameState::IN_HELP);
    	m_uiManager.addUiText("P - pause the game", "help_p", 32, 64, 312, sf::Color::White, true, GameState::IN_HELP);
    	m_uiManager.addUiText("Contact in github.com/JoseGuilhermeCR", "help_contact", 16, 32, Utils::HEIGHT - 32, sf::Color::White, true, GameState::IN_HELP);

    	// Usage of lambda [] (parameters) -> return type {CODE};
    	// []  Capture nothing (or, a scorched earth strategy?)
    	// [&] Capture any referenced variable by reference
    	// [=] Capture any referenced variable by making a copy
    	// [=, &foo] Capture any referenced variable by making a copy, but capture variable foo by reference
    	// [bar] Capture bar by making a copy; don't copy anything else
    	// [this] Capture the this pointer of the enclosing class
    	// Main Menu actions
    	m_uiManager.setEvent("Play", [this] () { changeState(GameState::IN_GAME); });
    	m_uiManager.setEvent("Highscore", [this] () { changeState(GameState::IN_HIGHSCORE); });
    	m_uiManager.setEvent("Help", [this] () { changeState(GameState::IN_HELP); });
    	m_uiManager.setEvent("Exit", [this] () { m_window.close(); });
    	// Highscore actions
    	m_uiManager.setEvent("Clear Highscore", [this] () { m_highscoreManager.setNewHighscore(0);
                                                        	m_uiManager.setText("highscore_highscore", "Highscore: " + std::to_string(m_player.getScore()));
                                                      	});
    	m_uiManager.setEvent("Back", [this] () { changeState(GameState::IN_MENU); });
    	// GameOver actions
    	m_uiManager.setEvent("Continue", [this] () { changeState(GameState::IN_MENU); });

    	while (m_window.isOpen()) 
	{
        	update();
        	draw();
    	}
}

void Game::update() 
{
    	m_deltaTime = m_clock.restart().asSeconds();

    	sf::Event e;
    	if (m_currentState == GameState::IN_GAME)
	{
        	while (m_window.pollEvent(e))
		{
            		if (e.type == sf::Event::KeyPressed)
			{
                		if (e.key.code == sf::Keyboard::Escape)
				{
                    			changeState(GameState::IN_MENU);
                		}
                		else if (e.key.code == sf::Keyboard::P)
				{
                    			m_paused = !m_paused;
                    			m_uiManager.setTextVisible("ingame_paused", m_paused);
                		}
            		}
        	}

        	if (!m_paused)
		{
            		m_particleManager.update(m_deltaTime);
            		m_asteroidManager.update(m_deltaTime);
            		m_player.update(m_deltaTime);
            		m_bossManager.update(m_deltaTime);

            		if (m_player.getLifeNumber() == 0)
			{
                		m_uiManager.setText("gameover_scored", "Your score: " + std::to_string(m_player.getScore()));

                		if (m_player.getScore() > m_highscoreManager.getSavedScore())
				{
                    			m_uiManager.setText("gameover_newhighscore", "New Highscore: " + std::to_string(m_player.getScore()) + "!");
                    			m_uiManager.setTextVisible("gameover_newhighscore", true);

                    			m_uiManager.setText("highscore_highscore", "Highscore: " + std::to_string(m_player.getScore()));

                    			m_highscoreManager.setNewHighscore(m_player.getScore());
                		}

                		changeState(GameState::IN_GAME_OVER);
            		}
        	}
    }
    	else if (m_currentState == GameState::IN_MENU)
	{
        	while (m_window.pollEvent(e))
		{
            		if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape))
                		m_window.close();
            		if (e.type == sf::Event::KeyPressed)
			{
                		if (e.key.code == sf::Keyboard::P)
                    			changeState(GameState::IN_GAME);
				/*if (e.key.code == sf::Keyboard::T)
		    			m_soundManager.playSound("test");*/
            		}
        	}

        	m_asteroidManager.update(m_deltaTime);
    	}
    	else if (m_currentState == GameState::IN_HIGHSCORE)
	{
        	while (m_window.pollEvent(e))
		{
            		if (e.type == sf::Event::Closed)
               			m_window.close();
            		if (e.type == sf::Event::KeyPressed)
			{
                		if (e.key.code == sf::Keyboard::Escape)
                    			changeState(GameState::IN_MENU);
            		}
        	}

        	m_asteroidManager.update(m_deltaTime);
    	}
    	else if (m_currentState == GameState::IN_HELP)
	{
        	while (m_window.pollEvent(e))
		{
           		if (e.type == sf::Event::Closed)
                		m_window.close();
           		if (e.type == sf::Event::KeyPressed)
			{
                		if (e.key.code == sf::Keyboard::Escape)
                    			changeState(GameState::IN_MENU);
            		}
        	}

        	m_asteroidManager.update(m_deltaTime);
    	}
    	else if (m_currentState == GameState::IN_GAME_OVER)
	{
        	while (m_window.pollEvent(e))
		{
            		if (e.type == sf::Event::Closed)
                		m_window.close();
            		if (e.type == sf::Event::KeyPressed)
			{
                		if (e.key.code == sf::Keyboard::C)
                    			changeState(GameState::IN_MENU);
            		}
        	}

        	m_asteroidManager.update(m_deltaTime);
    	}


    	// Call the uiManager update function which handles all updates that are needed
    	// to the ui stuff
    	m_uiManager.update(m_deltaTime, sf::Mouse::getPosition(m_window), m_currentState);
}

void Game::draw() 
{
	if (m_currentState == GameState::IN_GAME)
	{
            m_window.clear(sf::Color::Black);

            m_particleManager.draw(m_window);
            m_asteroidManager.draw(m_window);
            m_player.draw(m_window);

            m_bossManager.draw(m_window);
        }
        else if (m_currentState == GameState::IN_MENU)
	{
            m_window.clear(sf::Color::Black);

            m_asteroidManager.draw(m_window);
        }
        else if (m_currentState == GameState::IN_HIGHSCORE)
	{
            m_window.clear(sf::Color::Black);

            m_asteroidManager.draw(m_window);
        }
        else if (m_currentState == GameState::IN_HELP)
	{
            m_window.clear(sf::Color::Black);

            m_asteroidManager.draw(m_window);
        }
        else if (m_currentState == GameState::IN_GAME_OVER)
	{
            m_window.clear(sf::Color::Black);

            m_asteroidManager.draw(m_window);
        }

        // Draw all the ui stuff for the game, depending on the currentState
        m_uiManager.draw(m_window, m_currentState);

        m_window.display();
}

void Game::changeState(GameState newState)
{
    	// This function tells in which state the game was, and in which state it is now,
    	// and allows specific variables to be changed depending on the states changed
    	switch (m_currentState) 
	{
        	case GameState::IN_GAME:
            		m_particleManager.reset();
            		m_asteroidManager.reset();
            		m_player.reset();
            		m_bossManager.reset();
            		m_paused = false;
            		m_uiManager.setTextVisible("ingame_paused", false);
            		break;
        	case GameState::IN_MENU:
            		m_asteroidManager.reset();
            		break;
        	case GameState::IN_HIGHSCORE:
            		m_asteroidManager.reset();
            		break;
        	case GameState::IN_HELP:
            		m_asteroidManager.reset();
            		break;
        	case GameState::IN_GAME_OVER:
            		m_uiManager.setTextVisible("gameover_newhighscore", false);
            		m_asteroidManager.reset();
            		break;
        	default:
            		break;
    	}

    	m_currentState = newState;
}
