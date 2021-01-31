#ifndef __UI_H__
#define __UI_H__

#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "player.h"
#include "enemy.h"

class UI
{
private:
	sf::RenderWindow &m_window;

	int m_maxScore;
	bool m_isEnd;
	sf::Font m_font;

	sf::Text m_aiScore;
	sf::Text m_playerScore;
	sf::Text m_resultText;

	sf::RectangleShape m_grid;
	sf::RectangleShape m_foreground;

public:
	UI(sf::RenderWindow &window, int maxScore);

	void drawUI(void);
	void drawResult(void);
	void update(Player &player, Enemy &ai);

	bool isEnd(void) { return m_isEnd; }
};

#endif
