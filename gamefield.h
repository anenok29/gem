#pragma once
#include "element.h"
#include "bomb.h"
#include "gem.h"
#include "recolor.h"
#include "windows.h"
#include "winbase.h"
#include <algorithm>
#include <array>

#define gamefield GameField::getGameField() 


struct xy {
	int x, y;
};

class GameField {

	static const int mapW = 8; 
	static const int mapH = 8;

	std::array<std::array<Element*, mapW>, mapH> cell;

	GameField();

public:

	int getW() const { return mapW; }
	int getH() const { return mapH; }

	Element* getCell(int x, int y) const { return cell[x][y]; }

	void drawField() const;

	void swapGems();

	void BonusReColor();
	void BlowUP();

	void SmashOut(xy const& position);
	void UpDownLeftRight(xy const& startpos, std::vector<xy>& positions, color const& rgb);
	void CheckCombinations();

	static GameField& getGameField();

};
