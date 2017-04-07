/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include <SFML/Audio.hpp>
#include <map> // For std::map

class SoundManager
{
    	std::map<std::string, sf::Sound> m_sounds;
    	sf::SoundBuffer m_soundBuffer;
public:
    	SoundManager();
    	void addSound(const std::string& key, const std::string& filename);
    	void playSound(const std::string& key);
};

#endif
