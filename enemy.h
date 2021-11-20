#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>

class Enemy;

#include "ball.h"

class Enemy
{
private:
	const float m_maxVelocity = 2800;
	int m_score;
	sf::RenderWindow &m_window;
	sf::RectangleShape m_hitbox;

    bool ballOutsideVerticalBounds(Ball &ball);
public:
	Enemy(sf::RenderWindow &window);

	void draw(void);
	void update(float deltaInSec, Ball &ball);
	void moveToX(int x);

    sf::Vector2f getCenterPosition(void);
	int getScore(void);
	sf::RectangleShape getHitbox(void);

	void setScore(int score);
};

#endif
