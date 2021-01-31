#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Graphics.hpp>

class Player
{
private:
	int m_score;
	sf::RenderWindow &m_window;
	sf::RectangleShape m_hitbox;

	void moveToX(int x);

public:
	Player(sf::RenderWindow &window);

	void draw(void);
	void update(void);

	int getScore(void);
	sf::RectangleShape getHitbox(void);
	void setScore(int score);
};

#endif
