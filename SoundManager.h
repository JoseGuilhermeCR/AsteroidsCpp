/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <map> // For std::map
#include <string>

class SoundManager
{
    	std::map<std::string, sf::Sound> m_sounds;
    	sf::SoundBuffer m_soundBuffer;
public:
    	SoundManager();
    	void addSound(const std::string& key, const std::string& filename);
    	void playSound(const std::string& key);
};

#endif // SOUNDMANAGER_H
