#include "gem.h"

namespace rgb { 
	color palette[8] = {
		{0.0f, 0.0f, 0.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 0.0f},
		{1.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
	};
};

const int FromRed = 2;
const int SixColors = 6;

Gem::Gem() { gemColor = rgb::palette[FromRed + rand() % (SixColors)]; } 
Gem::Gem(color const& newColor) { gemColor = newColor; } 

color Gem::getColor() const { return gemColor; }
void Gem::reColor() { gemColor = rgb::palette[FromRed + rand() % (SixColors)]; } 
void Gem::reColor(color const& newColor) { gemColor = newColor; } 
