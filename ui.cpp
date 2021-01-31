#include "ui.h"

using namespace sf;
using namespace std;

UI::UI(RenderWindow &window): m_window(window)
{
	Vector2f windowSize(window.getSize().x, window.getSize().y);

	font.loadFromFile("/Library/Fonts/Arial Unicode.ttf");
	m_isEnd = false;

	m_foreground = RectangleShape(windowSize);
	m_foreground.setPosition(0, 0);
	m_foreground.setFillColor(Color(30, 30, 30, 200));

	m_resultText.setFont(font);
	m_resultText.setFillColor(Color::White);
	m_resultText.setCharacterSize(120);

	Color backgroundColor(255, 255, 255, 200);
	m_grid = RectangleShape(Vector2f(windowSize.x, 10));
	m_grid.setFillColor(backgroundColor);

	m_playerScore.setFont(font);
	m_playerScore.setFillColor(backgroundColor);
	m_playerScore.setCharacterSize(200);

	m_aiScore.setFont(font);
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
	if (player.getScore() < 10)
		score1 << 0;
	score1 << player.getScore();
	m_playerScore.setString(score1.str());
	m_playerScore.setPosition(m_window.getSize().x-250, m_window.getSize().y/2);

	stringstream score2;
	if (ai.getScore() < 10)
		score2 << 0;
	score2 << ai.getScore();
	m_aiScore.setString(score2.str());
	m_aiScore.setPosition(m_window.getSize().x-250, m_window.getSize().y/2-250);

	if (player.getScore() == 10 || ai.getScore() == 10) {
		m_isEnd = true;
		m_resultText.setString(player.getScore() == 10 ? "YOU WIN!" : "YOU LOSE!");
		m_resultText.setPosition(m_window.getSize().x/2 - 300, m_window.getSize().y/2-80);
	}
}
