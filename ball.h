#ifndef __BALL_H__
#define __BALL_H__

class Ball;

#include "player.h"
#include "enemy.h"

#include <SFML/Graphics.hpp>

#define HISTORY_SIZE_OF_BALL_POSITIONS 10

class Ball
{
private:
	sf::RenderWindow &m_window;
	const float m_defaultVelocity = 450.0;
	float m_velocity;
	sf::Vector2f m_dir;
	sf::CircleShape m_hitboxes[HISTORY_SIZE_OF_BALL_POSITIONS];

public:
	Ball(sf::RenderWindow &window);

	void draw(void);
	void update(float deltaInSec, Player &player, Enemy &enemy);

	void move(float deltaInSec);
	void increaseVelocity(void);
	void setStartingPosition(void);
	bool collision(const sf::RectangleShape &board);
    sf::Vector2f getCenterPosition(void);

	sf::Vector2f getDirection(void) { return m_dir; }
	sf::CircleShape getHitbox(void) { return m_hitboxes[0]; }
	float getVelocity(void) { return m_velocity; }
};

#endif
