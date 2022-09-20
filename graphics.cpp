#include "gem.h"
#include "bomb.h"
#include "recolor.h"

void Gem::DrawElement() const { 
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0.1f, 0.6f);
	glVertex2f(0.25f, 0.8f);
	glVertex2f(0.3f, 0.8f);
	glVertex2f(0.4f, 0.6f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(gemColor.r, gemColor.g, gemColor.b);
	glVertex2f(0.3f, 0.8f);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.7f, 0.8f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.75f * gemColor.r, 0.75f * gemColor.g, 0.75f * gemColor.b);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.7f, 0.8f);
	glVertex2f(0.75f, 0.8f);
	glVertex2f(0.9f, 0.6f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(gemColor.r, gemColor.g, gemColor.b);
	glVertex2f(0.1f, 0.6f);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.5f, 0.1f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.75f * gemColor.r, 0.75f * gemColor.g, 0.75f * gemColor.b);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.5f, 0.1f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f * gemColor.r, 0.5f * gemColor.g, 0.5f * gemColor.b);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.9f, 0.6f);
	glVertex2f(0.5f, 0.1f);
	glEnd();
}

void Gem::DrawFrame() const { 
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex2f(0.5f, 0.1f);
	glVertex2f(0.1f, 0.6f);
	glVertex2f(0.25f, 0.8f);
	glVertex2f(0.75f, 0.8f);
	glVertex2f(0.9f, 0.6f);
	glVertex2f(0.5f, 0.1f);
	glEnd();
}

void ReColor::DrawElement() const {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	float x, y;
	float cnt = 20;
	float r = 0.5f;
	float alpha = 3.1415926f * 2.0f / cnt;
	for (int i = -1; i < cnt; i++) {
		x = sin(alpha * i) * r;
		y = cos(alpha * i) * r;
		glVertex2f(x + 0.5f, y + 0.5f);
	}
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0.1f, 0.6f);
	glVertex2f(0.25f, 0.8f);
	glVertex2f(0.3f, 0.8f);
	glVertex2f(0.4f, 0.6f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(prevColor.r, prevColor.g, prevColor.b);
	glVertex2f(0.3f, 0.8f);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.7f, 0.8f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.75f * prevColor.r, 0.75f * prevColor.g, 0.75f * prevColor.b);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.7f, 0.8f);
	glVertex2f(0.75f, 0.8f);
	glVertex2f(0.9f, 0.6f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(prevColor.r, prevColor.g, prevColor.b);
	glVertex2f(0.1f, 0.6f);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.5f, 0.1f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.75f * prevColor.r, 0.75f * prevColor.g, 0.75f * prevColor.b);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.5f, 0.1f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f * prevColor.r, 0.5f * prevColor.g, 0.5f * prevColor.b);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.9f, 0.6f);
	glVertex2f(0.5f, 0.1f);
	glEnd();
}

void ReColor::DrawFrame() const {
	float x, y;
	float dot = 100;
	float r = 0.5f;
	float alpha = 3.1415926f * 2.0f / dot;
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.6f, 0.0f);
	for (int i = -1; i < dot; i++) {
		x = sin(alpha * i) * r;
		y = cos(alpha * i) * r;
		glVertex2f(x + 0.5f, y + 0.5f);
	}
	glEnd();
}

void Bomb::DrawElement() const { 
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	float x, y;
	float cnt = 20;
	float r = 0.4f;
	float alpha = 3.1415926f * 2.0f / cnt;
	for (int i = -1; i < cnt; i++) {
		x = sin(alpha * i) * r;
		y = cos(alpha * i) * r;
		glVertex2f(x + 0.5f, y + 0.5f);
	}
	glColor3f(0, 0, 0);
	glPointSize(2);
	for (int i = -1; i < cnt; i++) {
		x = sin(alpha * i) * r;
		y = cos(alpha * i) * r;
		glVertex2f(x + 0.5f, y + 0.5f);
	}
	glEnd();
}

void Bomb::DrawFrame() const {
	float x, y;
	float dot = 100;
	float r = 0.4f;
	float alpha = 3.1415926f * 2.0f / dot;
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.6f, 0.0f);
	for (int i = -1; i < dot; i++) {
		x = sin(alpha * i) * r;
		y = cos(alpha * i) * r;
		glVertex2f(x + 0.5f, y + 0.5f);
	}
	glEnd();
}