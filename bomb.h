#pragma once
#include "element.h"

class Bomb : public Element {
public:
	Bomb();
	void DrawElement() const;
	void DrawFrame() const;
	color getColor() const;
	void reColor();
	void reColor(color const& newColor);
};