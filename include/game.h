#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>

#include "../include/gameObject.h"

class Game: public GameObject
{
private:
	const int m_FPS = 30;

    sf::Clock m_clock;
	bool m_redraw = true;

    static Game *m_instance;

    Game(void);
public:
	const int m_maxScore = 10;
    sf::RenderWindow m_window;

    Game(Game &other) = delete;
    void operator=(const Game &) = delete;
    static Game *getInstance(void);

    void start(void);
    void draw(void);
    void update(float deltaSec);
};

#endif
