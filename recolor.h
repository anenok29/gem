#pragma once
#include "element.h"

class ReColor : public Element {
	color prevColor;
public:
	ReColor(color const& prev);

	void DrawElement() const;

	void DrawFrame() const;
	color getColor() const;
	void reColor();
	void reColor(color const& newColor);
};
