#include "../include/ui.h"

using namespace sf;
using namespace std;

UI::UI(RenderWindow &window, int maxScore): m_window(window)
{
	if (maxScore < 0)
		maxScore = 1;
	else if (maxScore > 99)
		maxScore = 99;

	m_isEnd = false;
	m_maxScore = maxScore;
	m_font.loadFromFile("/Library/Fonts/Arial Unicode.ttf");
	Vector2f windowSize(window.getSize().x, window.getSize().y);

	m_foreground = RectangleShape(windowSize);
	m_foreground.setPosition(0, 0);
	m_foreground.setFillColor(Color(30, 30, 30, 200));

	m_resultText.setFont(m_font);
	m_resultText.setFillColor(Color::White);
	m_resultText.setCharacterSize(120);

	Color backgroundColor(255, 255, 255, 200);
	m_grid = RectangleShape(Vector2f(windowSize.x, 10));
	m_grid.setFillColor(backgroundColor);

	m_playerScore.setFont(m_font);
	m_playerScore.setFillColor(backgroundColor);
	m_playerScore.setCharacterSize(200);

	m_aiScore.setFont(m_font);
	m_aiScore.setFillColor(backgroundColor);
	m_aiScore.setCharacterSize(200);
}

void UI::drawUI(void)
{
	m_window.draw(m_grid);
	m_window.draw(m_playerScore);
	m_window.draw(m_aiScore);
}

void UI::drawResult(void)
{
	m_window.draw(m_foreground);
	m_window.draw(m_resultText);
}

void UI::update(Player &player, Enemy &ai)
{
	m_grid.setSize(Vector2f(m_window.getSize().x, 10));
	m_grid.setPosition(0, m_window.getSize().y/2-5);

	stringstream score1;
	if (player.getScore() < m_maxScore)
		score1 << 0;
	score1 << player.getScore();
	m_playerScore.setString(score1.str());
	m_playerScore.setPosition(m_window.getSize().x-250, m_window.getSize().y/2);

	stringstream score2;
	if (ai.getScore() < m_maxScore)
		score2 << 0;
	score2 << ai.getScore();
	m_aiScore.setString(score2.str());
	m_aiScore.setPosition(m_window.getSize().x-250, m_window.getSize().y/2-250);

	if (player.getScore() == m_maxScore || ai.getScore() == m_maxScore) {
		m_isEnd = true;
		m_resultText.setString(player.getScore() == m_maxScore ? "YOU WIN!" : "YOU LOSE!");
		m_resultText.setPosition(m_window.getSize().x/2 - 300, m_window.getSize().y/2-80);
	}
}
