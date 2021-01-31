#include "ball.h"

using namespace sf;

Ball::Ball(RenderWindow &window): m_window(window)
{
	const float radius = 20;

	this->m_velocity = this->m_defaultVelocity;
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		Color color(255, 255, 255, 255 - 25*i);

		this->m_hitboxes[i] = CircleShape(radius);
		this->m_hitboxes[i].setFillColor(color);
	}

	this->setStartingPosition();
}

void Ball::draw(void)
{
	for (int i = 9; i > 0; i--)
		m_window.draw(m_hitboxes[i]);
}

void Ball::update(float delta, Player &player, Enemy &ai)
{
	// ball interacts with window
	Vector2f pos = m_hitboxes[0].getPosition();
	float radius = m_hitboxes[0].getRadius();
	Vector2u winSize = m_window.getSize();

	if (pos.x < 0) {
		m_hitboxes[0].move(-pos.x, 0);
		m_dir.x *= -1;
	} else if (pos.x+radius*2 > winSize.x) {
		m_hitboxes[0].move(-pos.x + winSize.x - radius*2, 0);
		m_dir.x *= -1;
	} else if (pos.y < 0 || pos.y+radius*2 > winSize.y) {
		if (pos.y < 0)
			player.setScore(player.getScore()+1);
		else
			ai.setScore(ai.getScore()+1);

		this->setStartingPosition();
	}

	// ball interacts with boards
	if ((this->collision(player.getHitbox()) && m_dir.y > 0) || (this->collision(ai.getHitbox()) && m_dir.y < 0)) {
		m_dir.y *= -1;
		this->increaseVelocity();
	}

	this->move(delta);
}

void Ball::move(float delta)
{
	Vector2f pos = this->m_hitboxes[0].getPosition() + delta*this->m_velocity*this->m_dir;

	for (int i = 9; i >= 1; i--)
		this->m_hitboxes[i].setPosition(this->m_hitboxes[i-1].getPosition());
	this->m_hitboxes[0].setPosition(pos);
}

void Ball::increaseVelocity(void)
{
	if (this->m_velocity < 2000)
		this->m_velocity *= 1.2;
}

void Ball::setStartingPosition(void)
{
	Vector2u winSize = m_window.getSize();
	this->m_velocity = this->m_defaultVelocity;

	for (int i = 0; i < 10; i++)
		this->m_hitboxes[i].setPosition(winSize.x/2-this->m_hitboxes[i].getRadius(), winSize.y/2-this->m_hitboxes[i].getRadius());

	// temporary
	int sign = rand()%2 == 0 ? 1 : -1;;
	float angle = rand()%55 + 20;
	float radian = sign*angle*M_PI/180.0;
	this->m_dir.x = cos(radian);
	this->m_dir.y = sin(radian);
}

bool Ball::collision(const RectangleShape &board)
{
	Vector2f boardPos  = board.getPosition();
	Vector2f boardSize = board.getSize();
	Vector2f ballPos = this->m_hitboxes[0].getPosition();
	float ballRadius = this->m_hitboxes[0].getRadius();

	return ballPos.x	      < boardPos.x+boardSize.x &&
	       ballPos.y	      < boardPos.y+boardSize.y &&
	       ballPos.x+ballRadius*2 > boardPos.x &&
	       ballPos.y+ballRadius*2 > boardPos.y;
}

