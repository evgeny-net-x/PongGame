#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include <cmath>
#include <ctime>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <SFML/Graphics.hpp>
//#include <SFML/Keyboard.hpp>

using namespace std;
using namespace sf;

float length(Vector2f &_this)
{return sqrt(_this.x*_this.x + _this.y*_this.y);}

float length(Vector2i &_this)
{return sqrt(_this.x*_this.x + _this.y*_this.y);}

int main(void)
{
	const int FPS = 30;
	const int screenScalar = 300;
	const int borderWidth = 20;

	RenderWindow window(VideoMode(4*screenScalar, 3*screenScalar), "SFML works!");

	RectangleShape board(Vector2f(160, 30));
	board.setPosition(window.getSize().x/2-board.getSize().x/2, window.getSize().y-board.getSize().y-20);
	board.setFillColor(Color::White);

	CircleShape ball(30);
	ball.setPosition(board.getPosition().x+board.getSize().x/2-ball.getRadius(), board.getPosition().y-ball.getRadius()*2);
	ball.setFillColor(Color::Red);

	Vector2f ballDir(-0.5, -1);
	ballDir *= 400/length(ballDir);

	Clock clock;
	bool redraw = true;

	while (window.isOpen()) {
		float delta = clock.getElapsedTime().asSeconds();

		if (delta >= 1.0/FPS) {
			redraw = true;
			clock.restart();
		} else {
			Time sleepTime = seconds((1.0/FPS) - delta);
			sleep(sleepTime);
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseMoved) {
				int winX = window.getPosition().x;
				int mouseX = Mouse::getPosition().x;
				int posX = mouseX-winX;

				if (posX-board.getSize().x/2 <= borderWidth)
					posX = board.getSize().x/2 + borderWidth;
				else if (posX+board.getSize().x/2 >= window.getSize().x-borderWidth)
					posX = window.getSize().x-borderWidth - board.getSize().x/2;

				Vector2f position(posX-board.getSize().x/2, board.getPosition().y);
				board.setPosition(position);
			}
		}

		Vector2f ballPos = ball.getPosition() + delta*ballDir;
		if (ballPos.x <= 0) { // ball on left side of screen case
			ballPos.x = 0;
			ballDir.x *= -1;
			cout << -2 << endl;
		} else if (ballPos.x+ball.getRadius()*2 >= window.getSize().x) { // ball on right side of screen case
			ballPos.x = window.getSize().x - ball.getRadius()*2;
			ballDir.x *= -1;
			cout << -1 << endl;
		}

		if (ballPos.y <= 0) { // top case
			ballPos.y = 0;
			ballDir.y *= -1;
			cout << 0 << endl;
		} else if (ballPos.y+ball.getRadius()*2 >= board.getPosition().y && ballPos.x+ball.getRadius() >= board.getPosition().x && ballPos.x+ball.getRadius() <= board.getPosition().x+board.getSize().x) { // ball on board case
			ballPos.y = board.getPosition().y - ball.getRadius()*2;
			ballDir.y *= -1;

			if (length(ballDir) < 2000) {
				ballDir.x *= 1.1;
				ballDir.y *= 1.1;
			}
			cout << 1 << endl;
		} else if (ballPos.y+ball.getRadius()*2 >= board.getPosition().y && ballPos.x+ball.getRadius()*2 >= board.getPosition().x && ballPos.x+ball.getRadius()*2 <= board.getPosition().x+board.getSize().x) { // ball on left side of board case
			ballPos.x = board.getPosition().x - ball.getRadius()*2;
			ballDir.x *= -1;
			cout << 2 << endl;
		} else if (ballPos.y+ball.getRadius()*2 >= board.getPosition().y && ballPos.x <= board.getPosition().x+board.getSize().x && ballPos.x >= board.getPosition().x) { // ball on right side of board case
			ballPos.x = board.getPosition().x+board.getSize().x;
			ballDir.x *= -1;
			cout << 3 << endl;
		} else if (ballPos.y+ball.getRadius()*2 >= window.getSize().y) { // ball out of board case
			ballPos.y = 0;
			cout << 4 << endl;
		}

		ball.setPosition(ballPos);

		if (redraw) {
                        redraw = false;
                        window.clear(Color(0, 0, 0));
                        window.draw(board);
                        window.draw(ball);
                        window.display();
                }
	}

	return 0;
}
