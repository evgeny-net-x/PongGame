#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

#include <cmath>
#include <ctime>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

float length(Vector2f &_this)
{return sqrt(_this.x*_this.x + _this.y*_this.y);}

float length(Vector2i &_this)
{return sqrt(_this.x*_this.x + _this.y*_this.y);}

float dot(Vector2f &a, Vector2f &b)
{return a.x*b.x + a.y*b.y;}

float dot(Vector2i &a, Vector2i &b)
{return a.x*b.x + a.y*b.y;}

class Board {
public:
	int score;
	RectangleShape &board;

	Board(Vector2f &size, Vector2f &pos, const Color &color): board(*(new RectangleShape(size)))
	{
		this->score = 0;
		this->board.setPosition(pos);
		this->board.setFillColor(color);
	}

	~Board()
	{
		delete &this->board;
	}

	void moveTo(float pos, Window &window)
	{
		const int borderWidth = 20;

		Vector2f boardSize = this->board.getSize();
		Vector2u winSize = window.getSize();

		if (pos-boardSize.x/2 <= borderWidth)
			pos = boardSize.x/2 + borderWidth;
		else if (pos+boardSize.x/2 >= winSize.x-borderWidth)
			pos = winSize.x - borderWidth - boardSize.x/2;

		this->board.setPosition(Vector2f(pos-boardSize.x/2, this->board.getPosition().y));
	}
};

class Ball {
public:
	const float defaultVelocity = 450.0;
	float velocity;
	Vector2f dir;
	CircleShape balls[10];

	Ball(float radius, Vector2f &pos, Vector2f &dir, const Color &color)
	{
		this->dir = dir;
		this->velocity = this->defaultVelocity;
		srand(time(NULL));

		for (int i = 0; i < 10; i++) {
			Color col(color.r, color.g, color.b, color.a - 25*i);

			this->balls[i] = CircleShape(radius);
			this->balls[i].setPosition(pos);
			this->balls[i].setFillColor(col);
		}
	}

	void move(float delta)
	{
		Vector2f pos = this->balls[0].getPosition() + delta*this->velocity*this->dir;

		for (int i = 9; i >= 1; i--)
			this->balls[i].setPosition(this->balls[i-1].getPosition());
		this->balls[0].setPosition(pos);
	}

	void increaseVelocity(void)
	{
		if (this->velocity < 2000)
			this->velocity *= 1.1;
	}

	void collision(const Window &window)
	{
		Vector2f pos = this->balls[0].getPosition();
		float radius = this->balls[0].getRadius();
		Vector2u winSize = window.getSize();

		if (pos.x < 0) {
			pos.x = 0;
			this->dir.x *= -1;
		} else if (pos.x+radius*2 > winSize.x) {
			pos.x = winSize.x - radius*2;
			this->dir.x *= -1;
		} else if (pos.y < 0 || pos.y+radius*2 > winSize.y) {
			pos.x = winSize.x/2;
			pos.y = winSize.y/2;
			this->velocity = this->defaultVelocity;

			// temporary
			float angle = rand()%55 + 20;
			float radian = angle*M_PI/180.0;
			this->dir.x = cos(radian);
			this->dir.y = sin(radian);
		}

		this->balls[0].setPosition(pos);
	}

	bool collision(const RectangleShape &board)
	{
		Vector2f boardPos  = board.getPosition();
		Vector2f boardSize = board.getSize();
		Vector2f ballPos = this->balls[0].getPosition();
		float ballRadius = this->balls[0].getRadius();

		return ballPos.x	      < boardPos.x+boardSize.x &&
		       ballPos.y	      < boardPos.y+boardSize.y &&
		       ballPos.x+ballRadius*2 > boardPos.x &&
		       ballPos.y+ballRadius*2 > boardPos.y;
	}
};

int main(void)
{
	const int FPS = 30;
	const int screenScalar = 300;
	const float ballRadius = 20;
	Vector2i windowSize(4*screenScalar, 3*screenScalar);
	Vector2f boardSize(160, 30);
	Font font;
	font.loadFromFile("/Library/Fonts/Arial Unicode.ttf");
	Color textColor(255, 255, 255, 200);

	Vector2f gridPos(windowSize.x, 10);
	RectangleShape grid(gridPos);
	grid.setFillColor(textColor);
	grid.setPosition(0, windowSize.y/2-5);

	Vector2f playerPos(windowSize.x/2-boardSize.x/2, windowSize.y-boardSize.y-20);
	Text playerScore = Text();
	playerScore.setFont(font);
	playerScore.setFillColor(textColor);
	playerScore.setCharacterSize(200);
	playerScore.setPosition(windowSize.x-250, windowSize.y/2);

	Vector2f aiPos(windowSize.x/2-boardSize.x/2, 20);
	const float aiVelocity = 500;
	Text aiScore = Text();
	aiScore.setFont(font);
	aiScore.setFillColor(textColor);
	aiScore.setCharacterSize(200);
	aiScore.setPosition(windowSize.x-250, windowSize.y/2-250);

	Vector2f ballDir(-0.5/1.25, -1/1.25);
	Vector2f ballPos(playerPos.x+boardSize.x/2-ballRadius, playerPos.y-ballRadius*2);

	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "Pong");
	Board player(boardSize, playerPos, Color::White);
	Board ai(boardSize, aiPos, Color::White);
	Ball ball(ballRadius, ballPos, ballDir, Color::White);

	Clock clock;
	bool redraw = true;

	while (window.isOpen()) {
		// Управление game loop
		float delta = clock.getElapsedTime().asSeconds();
		if (delta < 1.0/FPS)
			sleep(seconds(1.0/FPS - delta));
		else {
			redraw = true;
			clock.restart();
		}

		// Управление
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseMoved)
				player.moveTo(Mouse::getPosition().x - window.getPosition().x, window);
		}

		// AI move
		float velocity = abs(ball.dir.x);
		if (aiVelocity < ball.velocity)
			velocity *= aiVelocity;
		else
			velocity *= ball.velocity;

		if (ball.balls[0].getPosition().x+ball.balls[0].getRadius() < ai.board.getPosition().x+ai.board.getSize().x/2)
			ai.moveTo(ai.board.getPosition().x+ai.board.getSize().x/2 - delta*velocity, window);
		else
			ai.moveTo(ai.board.getPosition().x+ai.board.getSize().x/2 + delta*velocity, window);

		// Interact with window
		Vector2f pos = ball.balls[0].getPosition();
		float radius = ball.balls[0].getRadius();
		Vector2u winSize = window.getSize();

		if (pos.x < 0) {
			pos.x = 0;
			ball.dir.x *= -1;
		} else if (pos.x+radius*2 > winSize.x) {
			pos.x = winSize.x - radius*2;
			ball.dir.x *= -1;
		} else if (pos.y < 0 || pos.y+radius*2 > winSize.y) {
			pos.x = winSize.x/2;
			pos.y = winSize.y/2;
			ball.velocity = ball.defaultVelocity;

			if (pos.y < 0)
				player.score++;
			else
				ai.score++;

			// temporary
			float angle = rand()%55 + 20;
			float radian = angle*M_PI/180.0;
			ball.dir.x = cos(radian);
			ball.dir.y = sin(radian);
		}

		ball.balls[0].setPosition(pos);

		// Interact with boards
		if ((ball.collision(player.board) && ball.dir.y > 0) || (ball.collision(ai.board) && ball.dir.y < 0)) {
			ball.dir.y *= -1;
			ball.increaseVelocity();
		}
		ball.collision(player.board);
		ball.collision(ai.board);

		// Движение мяча
		ball.move(delta);

		// Управление game loop
		if (redraw) {
			redraw = false;
			window.clear(Color(30, 30, 30));
			window.draw(grid);

			for (int i = 9; i > 0; i--)
				window.draw(ball.balls[i]);
			window.draw(player.board);
			window.draw(ai.board);

			stringstream score1;
			if (player.score < 10)
				score1 << 0;
			score1 << player.score;
			playerScore.setString(score1.str());

			stringstream score2;
			if (ai.score < 10)
				score2 << 0;
			score2 << ai.score;
			aiScore.setString(score2.str());

			window.draw(playerScore);
			window.draw(aiScore);

			window.display();
                }

		if (player.score == 10 || ai.score == 10)
			break;
	}

	return 0;
}
