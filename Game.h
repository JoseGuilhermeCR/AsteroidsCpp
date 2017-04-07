/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef GAME_H
#define GAME_H

#include "SoundManager.h"
#include "GameState.h"
#include "UiManager.h"
#include "HighscoreManager.h"
#include "ParticlesManager.h"
#include "AsteroidManager.h"
#include "BossManager.h"

class Game 
{
    	sf::RenderWindow m_window;
    	sf::Clock m_clock;

    	SoundManager m_soundManager;
    	UiManager m_uiManager;
    	HighscoreManager m_highscoreManager;
    	ParticlesManager m_particleManager;
    	AsteroidManager m_asteroidManager;
    	Player m_player;
    	BossManager m_bossManager;
    	float m_deltaTime;
    	bool m_paused;

    	GameState m_currentState;
public:
    	Game();

   	void update();
    	void draw();

    	void changeState(GameState newState);
};

#endif // GAME_H
