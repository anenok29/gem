#pragma once
#include "element.h"

class Gem : public Element {
	color gemColor;
public:
	Gem();
	Gem(color const& newColor);

	color getColor() const;
	void DrawFrame() const;
	void reColor();
	void reColor(color const& newColor);

	void DrawElement() const;
};