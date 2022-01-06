#ifndef __BALL_H__
#define __BALL_H__

class Ball;

#include "gameObject.h"
#include "player.h"
#include "enemy.h"

#include <SFML/Graphics.hpp>

#define HISTORY_SIZE_OF_BALL_POSITIONS 10

class Ball: public GameObject
{
private:
	sf::RenderWindow &m_window;
	const float m_defaultVelocity = 450.0;
	float m_velocity;
	sf::Vector2f m_dir;
	sf::CircleShape m_hitboxes[HISTORY_SIZE_OF_BALL_POSITIONS];

public:
	Ball(sf::RenderWindow &window);

	virtual void draw(void) override;
	virtual void update(float deltaSec) override;

	void move(float deltaSec);
	void increaseVelocity(void);
	void setStartingPosition(void);
	bool collision(const sf::RectangleShape &board);

    sf::Vector2f getCenterPosition(void);
	sf::Vector2f getDirection(void) { return m_dir; }
	sf::CircleShape getHitbox(void) { return m_hitboxes[0]; }
	float getVelocity(void) { return m_velocity; }
};

#endif
