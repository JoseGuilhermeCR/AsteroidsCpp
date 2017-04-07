/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "include/SoundManager.h"
#include <iostream>
#include <string>
#include <tuple> // for pair<key, value>
#include <stdexcept> // fort out_of_range exception
#include <cassert> // for assert

SoundManager::SoundManager()
    	: 
	m_sounds(),
      	m_soundBuffer()
{
}

void SoundManager::addSound(const std::string& key, const std::string& filename)
{
    	// If it doesn't load the sound the program should exit
    	assert (m_soundBuffer.loadFromFile(filename));

    	sf::Sound sound;
    	sound.setBuffer(m_soundBuffer);

    	// Insert the sound into the map
    	//m_sounds.insert(std::pair<std::string, sf::Sound>(key, sound));
	m_sounds.insert(std::make_pair(key, sound));
}

void SoundManager::playSound(const std::string& key)
{
    	try 
	{
        	m_sounds.at(key).play();
    	}
    	catch (std::out_of_range& oor) 
	{
        	std::cerr << "The sound you are trying to play does not exist." << std::endl;
    	}
}
