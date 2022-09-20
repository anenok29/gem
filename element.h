#pragma once
#include <iostream> 
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <windows.h> 
#include <gl/gl.h>
#include <memory>
#include <math.h>

#pragma comment(lib, "opengl32.lib") 

struct color { 
	float r, g, b;
};

enum isCases {
	SELECT, CHECKED, 
	EXPLOSION, RECOLOR 
};

class Element { 
public:
	std::vector<bool> is = { false, false, false, false }; 


	virtual void DrawElement() const = 0;
	virtual void DrawFrame() const = 0;
	virtual color getColor() const = 0;
	virtual void reColor() = 0;
	virtual void reColor(color const& newColor) = 0;
};
