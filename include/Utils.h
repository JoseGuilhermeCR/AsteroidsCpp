/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#ifndef __UTILS_H__
#define __UTILS_H__

#include <random>
#include <cmath>

class Utils
{
	static std::mt19937 random;
public:
	static const unsigned int WIDTH;
	static const unsigned int HEIGHT;

	static int randomRange(int min, int max);

	// Template functions have to be declared in the header file
	template <typename T>
	static T mapNumber(T value, T start1, T stop1, T start2, T stop2) {
		return (value - start1 ) / (stop1 - start1) * (stop2 - start2) + start2;
	}

	template <typename T>
	static T dist(T ax, T ay, T bx, T by) {
		return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
	}
};

#endif
