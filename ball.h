#ifndef __BALL_H__
#define __BALL_H__

class Ball;

#include "player.h"
#include "enemy.h"

#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::RenderWindow &m_window;
	const float m_defaultVelocity = 450.0;
	float m_velocity;
	sf::Vector2f m_dir;
	sf::CircleShape m_hitboxes[10];

public:
	Ball(sf::RenderWindow &window);

	void draw(void);
	void update(float deltaInSec, Player &player, Enemy &ai);

	void move(float deltaInSec);
	void increaseVelocity(void);
	void setStartingPosition(void);
	bool collision(const sf::RectangleShape &board);

	sf::Vector2f getDirection(void) { return m_dir; }
	sf::CircleShape getHitbox(void) { return m_hitboxes[0]; }
	float getVelocity(void) { return m_velocity; }
};

#endif
