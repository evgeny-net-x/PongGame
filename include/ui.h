#ifndef __UI_H__
#define __UI_H__

#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "gameObject.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

class UI: public GameObject
{
private:
	sf::RenderWindow &m_window;

	int m_maxScore;
	bool m_isEnd;
	sf::Font m_font;

	sf::Text m_enemyScore;
	sf::Text m_playerScore;
	sf::Text m_resultText;

	sf::RectangleShape m_grid;
	sf::RectangleShape m_foreground;

    std::string normalizeScore(int score);
    void initializeText(sf::Text &text, const sf::Color &color, const int fontSize);
    sf::RectangleShape createRectangleShape(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color);
public:
	UI(sf::RenderWindow &window, int maxScore);

    virtual void draw(void) override;
	virtual void update(float deltaSec) override;

	void drawUI(void);
	void drawResult(void);

	bool isEnd(void) { return m_isEnd; }
};

#endif
