#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>

class Enemy;

#include "gameObject.h"
#include "game.h"
#include "ball.h"

class Enemy: public GameObject
{
private:
	const float m_maxVelocity = 2800;
	int m_score;
	sf::RenderWindow &m_window;
	sf::RectangleShape m_hitbox;

public:
	Enemy(sf::RenderWindow &window);

	virtual void draw(void) override;
	virtual void update(float deltaSec) override;
	void moveToX(int x);

    bool ballOutsideVerticalBounds(Ball &ball);

    sf::Vector2f getCenterPosition(void);
	int getScore(void);
	sf::RectangleShape getHitbox(void);

	void setScore(int score);
};

#endif
