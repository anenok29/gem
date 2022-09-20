#include "gamefield.h"

GameField& GameField::getGameField() {
	static GameField instance;
	return instance;
}


bool operator==(color const& rgb1, color const& rgb2) { //�������� ��������� ������
	return (rgb1.r == rgb2.r && rgb1.g == rgb2.g && rgb1.b == rgb2.b);
}

GameField::GameField() { // ������������� ����
	for (int x = 0; x < getW(); x++) {
		for (int y = 0; y < getH(); y++) {
			cell[x][y] = new Gem();
		}
	}
}

void GameField::drawField() const {
	glLoadIdentity();
	glScalef(2.0f / getW(), 2.0f / getH(), 1);
	glTranslatef(-getW() / 2.0f, -getH() / 2.0f, 0); //������� ��� ������������ ����

	for (int x = 0; x < getW(); x++)
	{
		for (int y = 0; y < getH(); y++)
		{
			glPushMatrix();
			glTranslatef(float(x), float(y), 0);
			getCell(x, y)->DrawElement();
			if (getCell(x, y)->is[SELECT])
				getCell(x, y)->DrawFrame();
			glPopMatrix();
		}
	}
}

void GameField::swapGems() { //����������� ������
	int dx = 1, dy = 1;
	for (int x = 0; x < getW(); x++) {
		for (int y = 0; y < getH(); y++) {
			if (getCell(x, y)->is[SELECT]) {
				if (x != getW() - 1 && getCell(x + dx, y)->is[SELECT])
				{
					getCell(x, y)->is[SELECT] = false;
					cell[x + dx][y]->is[SELECT] = false;
					std::swap(cell[x][y], cell[x + dx][y]);
				}
				else if (y != getH() - 1 && getCell(x, y + dy)->is[SELECT])
				{
					getCell(x, y)->is[SELECT] = false;
					getCell(x, y + dy)->is[SELECT] = false;
					std::swap(cell[x][y], cell[x][y + dy]);
				}
			}
		}
	}
}

void GameField::BonusReColor() {
	for (int x = 0; x < getW(); x++) {
		for (int y = 0; y < getH(); y++) {
			if (getCell(x, y)->is[SELECT] && getCell(x, y)->is[RECOLOR]) {
				getCell(x, y)->is[SELECT] = false;
				getCell(x, y)->is[RECOLOR] = false;
				color forChange = getCell(x, y)->getColor();
				delete getCell(x, y);
				cell[x][y] = new Gem(forChange);
				for (int i = 0; i < 2; i++) {
					int rng1 = 50, rng2 = 50;
					while (x + rng1 >= getW() || x + rng1 < 0 || y + rng2 >= getH() || y + rng2 < 0) {
						rng1 = 1 + rand() % 3;
						rng2 = 1 + rand() % 3;
						if (rand() % 2) {
							rng1 *= -1;
						}
						if (rand() % 2) {
							rng2 *= -1;
						}
					}
					getCell(x + rng1, y + rng2)->reColor(forChange);
				}
			}
		}
	}
}

void GameField::BlowUP() {
	int x1, y1;
	for (int x = 0; x < getW(); x++) {
		for (int y = 0; y < getH(); y++) {
			if (getCell(x, y)->is[SELECT] && getCell(x, y)->is[EXPLOSION]) {
				getCell(x, y)->is[SELECT] = false;
				getCell(x, y)->is[EXPLOSION] = false;
				delete getCell(x, y);
				cell[x][y] = new Gem();
				for (int y2 = y; y2 < getH() - 1; y2++)
				{
					std::swap(cell[x][y2], cell[x][y2 + 1]);
				}
				for (int i = 0; i < 4; i++) {
					x1 = rand() % getW();
					y1 = rand() % getH();
					SmashOut({ x1, y1 });
				}
			}

		}
	}
}

const int BonusChance = 20;

const int BombOrRecolor = 2;

void GameField::SmashOut(xy const& position) { //������� "�����������" �����
	int x = position.x, y = position.y;
	if (getCell(x, y)->is[EXPLOSION]) {
		getCell(x, y)->is[SELECT] = true;
		BlowUP();
	}
	if (rand() % BonusChance == 1) {
		if (rand() % BombOrRecolor) {
			color resetColor = getCell(x, y)->getColor();
			if (y == getH() - 1) {
				delete getCell(x, y);
				cell[x][y] = new ReColor(resetColor);
				return;
			}
			else {
				delete getCell(x, y + 1);
				cell[x][y + 1] = new ReColor(resetColor);
			}
		}
		else {
			if (y == getH() - 1) {
				delete getCell(x, y);
				cell[x][y] = new Bomb();
				return;
			}
			else {
				cell[x][y + 1] = new Bomb();
			}
		}
	}
	for (; y < getH() - 1; y++)
	{
		std::swap(cell[x][y], cell[x][y + 1]);
	}
	getCell(x, y)->reColor();
}

void GameField::UpDownLeftRight(xy const& point, std::vector<xy>& positions, color const& rgb) {

	if (point.x >= getW() || point.x < 0 || point.y >= getH() || point.y < 0)
		return;
	if (getCell(point.x, point.y)->is[EXPLOSION] || getCell(point.x, point.y)->is[RECOLOR] || getCell(point.x, point.y)->is[CHECKED]) {

		getCell(point.x, point.y)->is[CHECKED] = true;
		return;
	}
	if (getCell(point.x, point.y)->getColor() == rgb) {
		getCell(point.x, point.y)->is[CHECKED] = true;
		positions.push_back(point);
		UpDownLeftRight({ point.x + 1, point.y }, positions, rgb);
		UpDownLeftRight({ point.x - 1, point.y }, positions, rgb);
		UpDownLeftRight({ point.x, point.y + 1 }, positions, rgb);
		UpDownLeftRight({ point.x, point.y - 1 }, positions, rgb);
	}
}

bool comparator(xy const& point1, xy const& point2) { // ���������� ��� ���������� �������
	return point1.y < point2.y;
}

void GameField::CheckCombinations() {
	std::vector<xy> positions;
	for (int y = getH() - 1; y > -1; y--) {
		for (int x = 0; x < getW(); x++) {
			UpDownLeftRight({ x,y }, positions, cell[x][y]->getColor());
			if (positions.size() > 2)
			{
				std::sort(positions.begin(), positions.end(), comparator);

				while (!positions.empty())
				{
					SmashOut(positions.back());
					positions.pop_back();
				}
			}
			else if (!positions.empty())
			{
				while (!positions.empty()) positions.pop_back();
			}
		}
	}
	for (int y = 0; y < getH(); y++) {
		for (int x = 0; x < getW(); x++) {
			getCell(x, y)->is[CHECKED] = false;
		}
	}
}