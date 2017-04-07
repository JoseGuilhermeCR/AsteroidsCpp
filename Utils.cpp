/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "Utils.h"
#include <chrono>

const unsigned int Utils::WIDTH = 960, Utils::HEIGHT = Utils::WIDTH / 12 * 9;
std::mt19937 Utils::random(std::chrono::system_clock::now().time_since_epoch().count());

int Utils::randomRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}
