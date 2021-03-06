#pragma once
#include <SFML/Graphics.hpp>
#include "Bat.h"
#include <SFML/Audio/Music.hpp>

using namespace sf;
class Ball
{
private:
	Vector2f c_position;
	CircleShape circle;
	Music* soundEffect;
	float m_Speed = 1100.0f;
	bool toLeft = true;
	bool toRight = false;
	bool toUp = false;
	bool toDown = true;
	bool cameFromLeft = false;
	bool cameFromRight = false;
	bool cameFromTop = true;
	bool cameFromBottom = false;
	int collisionStatus = 0;
public:
	Ball(float startX, float startY);
	FloatRect getPosition();
	CircleShape getShape();
	void checkSides(Time dt, RenderWindow& window, Bat bat); //check all four walls, including the bat
	void move(Time dt);
	int update(Time dt, RenderWindow& window, Bat bat);
};
