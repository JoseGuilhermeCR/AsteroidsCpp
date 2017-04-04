/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "HighscoreManager.h"

HighscoreManager::HighscoreManager()
    : m_savedScore(0)
{
    std::string value;
    std::ifstream rs("highscore.sav");

    if (rs.is_open()) {
        std::getline(rs, value);
        std::istringstream iss(value);
        iss >> m_savedScore;

        rs.close();
    }
    else {
        std::cerr << "Could not open highscore file." << std::endl;
    }

    std::cout << "Loaded highscore: " << m_savedScore << std::endl;
}

void HighscoreManager::setNewHighscore(long newHighscore) {
    m_savedScore = newHighscore;

    std::ofstream ws("highscore.sav", std::ios::trunc | std::ios::out);
    ws << m_savedScore;
    ws.close();
}
