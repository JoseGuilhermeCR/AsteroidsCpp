/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <map> // For std::map
#include <tuple> // For std::pair<key, type>
#include <stdexcept> // For std::out_of_range exception
#include <cassert> // For assert

class SoundManager {
    std::map<std::string, sf::Sound> m_sounds;
    sf::SoundBuffer m_soundBuffer;
public:
    SoundManager();
    void addSound(std::string key, std::string filename);
    void playSound(std::string key);
};

#endif // SOUNDMANAGER_H
