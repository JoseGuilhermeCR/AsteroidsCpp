/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class HighscoreManager {
    long m_savedScore;
public:
    HighscoreManager();

    void setNewHighscore(long newHighscore);

    long getSavedScore() { return m_savedScore; }
};

#endif // HIGHSCOREMANAGER_H
