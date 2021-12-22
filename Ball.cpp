
#include "Ball.h"
#include <iostream>
using sf::Music;


Ball::Ball(float startX, float startY) {
	c_position.x = startX;
	c_position.y = startY;
	circle.setRadius(3);
	circle.setPointCount(2000);
	circle.setOutlineThickness(5);
	circle.setPosition(c_position);
	soundEffect = new Music();
	soundEffect->openFromFile("hitSound.wav");
	soundEffect->setVolume(85);
}

FloatRect Ball::getPosition()
{
	return circle.getGlobalBounds();
}

CircleShape Ball::getShape()
{
	return circle;
}



void Ball::checkSides(Time dt, RenderWindow& window, Bat bat)
{
	//left side
	if ((this->getPosition().left + this->getPosition().width) < 0)
	{
		cameFromLeft = true; //ball hit left wall and will rebound, hence, it is true
		toRight = true; // rebound to right
		toLeft = false;
		cameFromRight = false;
		soundEffect->stop();
		soundEffect->play();
	}

	//right side
	else if ((this->getPosition().left + this->getPosition().width) > window.getSize().x)
	{
		cameFromRight = true;
		toLeft = true;
		toRight = false;
		cameFromLeft = false;
		soundEffect->stop();
		soundEffect->play();
	}


	//top side
	if ((this->getPosition().top + this->getPosition().height) < 0)
	{
		cameFromTop = true;
		toDown = true;
		toUp = false;
		cameFromBottom = false;
		soundEffect->stop();
		soundEffect->play();
	}

	//Bat and Ball intersection
	else if (this->getPosition().intersects(bat.getPosition()) == true)
	{
		collisionStatus = 1;

	}

	//bottom side
	else if ((this->getPosition().top + this->getPosition().height) > window.getSize().y)
	{
		cameFromBottom = true;
		toUp = true;
		toDown = false;
		cameFromTop = false;
		soundEffect->stop();
		soundEffect->play();
		collisionStatus = -1;
	}




}



void Ball::move(Time dt)
{
	//check if the ball hit the bat, fromwhere, and rebound it appropiately
	if (collisionStatus == 1)
	{
		//stop function is used to reset the music player position 
		soundEffect->stop();
		soundEffect->play();
		if (cameFromTop)
		{
			//rebound the ball to top if it hit the bat from the top
			toUp = true;
			toDown = false;
		}
		else if (cameFromBottom)
		{
			//rebound the ball to bottom if it hit the bat from the bottom
			toDown = true;
			toUp = false;
		}

		if (cameFromLeft)
		{
			toRight = true;
		}
		else if (cameFromRight)
		{
			toLeft = true;
		}
	}

	if (toLeft)
	{

		c_position.x -= m_Speed * dt.asSeconds();
	}
	else if (toRight)
	{
		c_position.x += m_Speed * dt.asSeconds();
	}


	if (toDown)
	{
		c_position.y += m_Speed * dt.asSeconds();
	}
	else if (toUp)
	{
		c_position.y -= m_Speed * dt.asSeconds();

	}



}






int Ball::update(Time dt, RenderWindow& window, Bat bat)
{

	circle.setPosition(c_position);
	checkSides(dt, window, bat);
	move(dt);

	// if ball hits the bottom wall
	if (collisionStatus == -1)
	{
		//reset
		collisionStatus = 0;
		return -1;
	}

	//if the ball hit the bat
	else if (collisionStatus == 1)
	{
		collisionStatus = 0;
		return 1;
	}

	return 0;
}