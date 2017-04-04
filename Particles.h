/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include <vector>

// The same as a class but it has public members by default
struct Particle {
    sf::CircleShape shape;
    float lifeTime;
    float velX;
    float velY;
};

// This is the container for the particle struct
class Particles {
    std::vector<Particle> m_particles;
    std::mt19937 m_random;
    bool m_shouldBeDeleted;
public:
    Particles(unsigned int numberOfParticles, float x, float y, float lifeTime);
    void update(const float deltaTime);
    void draw(sf::RenderWindow &window);

    bool shouldDelete();
};

#endif // PARTICLES_H
