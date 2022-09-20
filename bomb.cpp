#include "bomb.h"

Bomb::Bomb() { is[EXPLOSION] = true; } // ������������� �����

color Bomb::getColor() const { return { 0,0,0 }; };
void Bomb::reColor() {}
void Bomb::reColor(color const& newColor) {}