#include "recolor.h"

ReColor::ReColor(color const& prev) { prevColor = prev; is[RECOLOR] = true; } //áîíóń ďĺđĺęđŕřčâŕíč˙ őđŕíčň â ńĺáĺ ďđĺäűäóůčé öâĺň



color ReColor::getColor() const { return prevColor; }
void ReColor::reColor() {}
void ReColor::reColor(color const& newColor) {}