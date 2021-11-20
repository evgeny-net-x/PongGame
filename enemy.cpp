#include "enemy.h"

using namespace sf;

Enemy::Enemy(RenderWindow &window): m_window(window)
{
	m_score = 0;

	m_hitbox = RectangleShape(Vector2f(160, 30));
	m_hitbox.setPosition(Vector2f(window.getSize().x/2-m_hitbox.getSize().x/2, 20));
	m_hitbox.setFillColor(Color::White);
}

void Enemy::draw(void)
{
	m_window.draw(m_hitbox);
}

void Enemy::update(float deltaInSec, Ball &ball)
{
	float velocity = abs(ball.getDirection().x);

	if (this->ballOutsideVerticalBounds(ball))
		velocity *= m_maxVelocity; // To catch the ball you need set the max speed
	else
		velocity *= fmin(ball.getVelocity(), m_maxVelocity); // equals the enemy's speed to the ball's speed so that it moves smoothly, otherwise there will be jerking

    const float ballCenterX = ball.getCenterPosition().x;
    const float enemyCenterX = this->getCenterPosition().x;
    const float step = deltaInSec*velocity;
	if (ballCenterX < enemyCenterX)
		this->moveToX(enemyCenterX - step);
	else
		this->moveToX(enemyCenterX + step);
}

Vector2f Enemy::getCenterPosition(void) {
    Vector2f pos = m_hitbox.getPosition();
    Vector2f size = m_hitbox.getSize();
    Vector2f halfSize = Vector2f(size.x/2, size.y/2);

    return pos + halfSize;
}

bool Enemy::ballOutsideVerticalBounds(Ball &ball) {
	CircleShape hitbox = ball.getHitbox();

	bool ballIsLeft = hitbox.getPosition().x+hitbox.getRadius()*2 < m_hitbox.getPosition().x;
	bool ballIsRight = hitbox.getPosition().x > m_hitbox.getPosition().x+m_hitbox.getSize().x;
	bool ballDirIsLeft = ball.getDirection().x < 0;

	return ((ballIsLeft && ballDirIsLeft) || (ballIsRight && !ballDirIsLeft));
}


void Enemy::moveToX(int x)
{
	const int borderWidth = 20;

	Vector2f boardSize = m_hitbox.getSize();
	Vector2u winSize = m_window.getSize();

	if (x - boardSize.x/2 <= borderWidth)
		x = boardSize.x/2 + borderWidth;
	else if (x + boardSize.x/2 >= winSize.x-borderWidth)
		x = winSize.x - borderWidth - boardSize.x/2;

	m_hitbox.setPosition(x - boardSize.x/2, 20);
}

int Enemy::getScore(void)
{
	return m_score;
}

RectangleShape Enemy::getHitbox(void)
{
	return m_hitbox;
}

void Enemy::setScore(int score)
{
	m_score = score;
}

