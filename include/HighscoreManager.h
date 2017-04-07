/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __HIGHSCOREMANAGER_H__
#define __HIGHSCOREMANAGER_H__

class HighscoreManager 
{
    	long m_savedScore;
public:
    	HighscoreManager();

    	void setNewHighscore(long newHighscore);

    	long getSavedScore();
};

#endif
