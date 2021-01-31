#include "player.h"

using namespace sf;

Player::Player(RenderWindow &window): m_window(window)
{
	m_score = 0;

	Vector2f boardSize(160, 30);
	m_hitbox = RectangleShape(boardSize);
	m_hitbox.setPosition(Vector2f(window.getSize().x/2-boardSize.x/2, window.getSize().y-boardSize.y-20));
	m_hitbox.setFillColor(Color::White);
}

void Player::draw(void)
{
	m_window.draw(m_hitbox);
}

void Player::update(void)
{
	this->moveToX(Mouse::getPosition().x - m_window.getPosition().x);
}

int Player::getScore(void)
{
	return m_score;
}

RectangleShape Player::getHitbox(void)
{
	return m_hitbox;
}

void Player::setScore(int score)
{
	m_score = score;
}

void Player::moveToX(int x)
{
	const int borderWidth = 20;

	Vector2f boardSize = m_hitbox.getSize();
	Vector2u winSize = m_window.getSize();

	if (x - boardSize.x/2 <= borderWidth)
		x = boardSize.x/2 + borderWidth;
	else if (x + boardSize.x/2 >= winSize.x-borderWidth)
		x = winSize.x - borderWidth - boardSize.x/2;

	m_hitbox.setPosition(x - boardSize.x/2, m_window.getSize().y - m_hitbox.getSize().y - 20);
}
