#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Graphics.hpp>
#include "gameObject.h"

class Player: public GameObject
{
private:
	int m_score;
	sf::RenderWindow &m_window;
	sf::RectangleShape m_hitbox;

protected:
	void moveToX(int x);

public:
	Player(sf::RenderWindow &window);

	virtual void draw(void);
	virtual void update(float deltaSec);

	int getScore(void);
	sf::RectangleShape getHitbox(void);
	void setScore(int score);
};

#endif
