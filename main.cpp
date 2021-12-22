
#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>


Color updateBatColor(int& score)
{

	if (score >= 1000 && score < 2000)
	{
		return Color::Green;
	}

	else if (score >= 2000 && score < 3000)
	{
		return Color::Blue;
	}

	else if (score >= 3000 && score < 4000)
	{
		return Color::Yellow;
	}

	else if (score >= 4000 && score < 5000)
	{
		return Color::Magenta;
	}

	else if (score >= 5000 && score < 6000)
	{
		return Color::Cyan;
	}
	else
	{
		return Color::White;
	}

}

void initialLoad(Text& scoreHud, Text& livesHud, Text& controls, Text& target, Text& gameStatus, Text& gameover, Ball& ball, Bat& bat, RenderWindow& window, Music& music)
{
	window.draw(scoreHud);
	window.draw(livesHud);
	window.draw(controls);
	window.draw(target);
	window.draw(gameStatus);
	window.draw(gameover);
	window.draw(ball.getShape());
	window.draw(bat.getShape());
	window.display();
	music.play();

}

int main()
{
	VideoMode vm;
	RenderWindow window(vm.getDesktopMode(), "Pong Game", Style::Default);
	window.setMouseCursorVisible(false);
	Music bgMusic;
	bgMusic.openFromFile("background_music.wav");
	bgMusic.setLoop(true);
	bgMusic.setVolume(30);

	int score = 0;
	bool addScore = false;
	int lives = 5;
	
	//create ball and bat objects
	Bat bat(window.getSize().x / 2, window.getSize().y-80);
	Ball ball(window.getSize().x / 2, 10);

	Font font;
	font.loadFromFile("game_over.ttf");

	Text scoreHud, livesHud, controls, target, gameStatus, gameover;

	controls.setFont(font);
	controls.setCharacterSize(45);
	controls.setFillColor(Color::White);
	controls.setPosition(25, 3);
	controls.setString("'esc' :  Quit                       |      'R' :  Restart");

	target.setFont(font);
	target.setCharacterSize(45);
	target.setFillColor(Color::White);
	target.setPosition(window.getSize().x - 150, 3);
	target.setString("target  :  6000");

	scoreHud.setFont(font);
	scoreHud.setCharacterSize(75);
	scoreHud.setFillColor(Color::White);
	scoreHud.setPosition(25, 10);

	livesHud.setFont(font);
	livesHud.setCharacterSize(75);
	livesHud.setFillColor(Color::White);
	livesHud.setPosition(165, 10);

	gameStatus.setFont(font);
	gameStatus.setCharacterSize(300);
	gameStatus.setFillColor(Color::White);
	gameStatus.setPosition((window.getSize().x / 3) + 70, (window.getSize().y / 5) - 100);
	std::string text;

	gameover.setFont(font);
	gameover.setCharacterSize(70);
	gameover.setFillColor(Color::White);
	gameover.setString("GAME OVER");

	initialLoad(scoreHud, livesHud, controls, target, gameStatus, gameover, ball, bat, window, bgMusic);
	Sleep(165);

	Clock clock;

	while (window.isOpen())
	{

		if (window.hasFocus())
		{
			//handle player input
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}

			}

			if (lives != 0 && score < 6000)
			{

				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					window.close();
				}

				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					//ball = resetBall;
					ball = Ball::Ball(window.getSize().x / 2, 10);
					score = 0;
					lives = 5;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					bat.moveLeft();
				}
				else
				{
					bat.stopLeft();
				}

				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					bat.moveRight();
				}
				else
				{
					bat.stopRight();
				}

				Time dt = clock.restart();


				//update bat and ball frames
				bat.update(dt, window, updateBatColor(score));
				int value = ball.update(dt, window, bat);

				//if ball hits bottom wall
				if (value == -1)
				{
					lives -= 1;
					if (score >= 250)
					{
						score -= 250;
					}
					else
					{
						score = 0;
					}
				}
				else if (value == 1)
				{
					addScore = true;
				}

				//in order to avoid increasing score up to thousands with a single hit, we must check that the ball hit the bat and no longer intersects with it
				if (addScore == true && ball.getPosition().intersects(bat.getPosition()) == false)
				{
					score += 430;
					addScore = false;

				}

				std::stringstream scoreStream;
				scoreStream << "Score: " << score;
				scoreHud.setString(scoreStream.str());

				std::stringstream livesStream;
				livesStream << "     |   Lives: " << lives;
				livesHud.setString(livesStream.str());


				window.clear();
				window.draw(target);
				window.draw(controls);
				window.draw(scoreHud);
				window.draw(livesHud);
				window.draw(bat.getShape());
				window.draw(ball.getShape());
				window.display();


			}
			else
			{
				if (score >= 6000)
				{
					text = "You Won!";
					gameover.setPosition(gameStatus.getPosition().x + 185, gameStatus.getPosition().y + 300);
				}
				else
				{
					text = "You Lost";
					//to properly align it
					gameover.setPosition(gameStatus.getPosition().x + 160, gameStatus.getPosition().y + 300);
				}

				std::stringstream gameStatusStream;
				gameStatusStream << text;
				gameStatus.setString(gameStatusStream.str());

				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					window.close();
				}

				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					ball = Ball::Ball(window.getSize().x / 2, 10);
					score = 0;
					lives = 3;
				}

				window.clear();
				window.draw(target);
				window.draw(controls);
				window.draw(scoreHud);
				window.draw(livesHud);
				window.draw(gameStatus);
				window.draw(gameover);
				window.draw(bat.getShape());
				window.draw(ball.getShape());
				window.display();


			}


		}
	}


	return 0;
}

