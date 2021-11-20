#include "ui.h"

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

	Color backgroundColor(255, 255, 255, 200);

	m_grid = this->createRectangleShape(Vector2f(windowSize.x, 10), Vector2f(0, 0), backgroundColor);
	m_foreground = this->createRectangleShape(windowSize, Vector2f(0, 0), Color(30, 30, 30, 200));

    this->initializeText(m_resultText, Color::White, 120);
    this->initializeText(m_playerScore, backgroundColor, 200);
    this->initializeText(m_aiScore, backgroundColor, 200);
}

RectangleShape UI::createRectangleShape(const Vector2f size, const Vector2f position, const Color color) {
	RectangleShape rect = RectangleShape(size);
	rect.setPosition(position.x, position.y);
	rect.setFillColor(color);

    return rect;
}

void UI::initializeText(Text &text, const Color &color, const int fontSize)
{
	text.setFont(m_font);
	text.setFillColor(color);
	text.setCharacterSize(fontSize);
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

void UI::update(Player &player, Enemy &enemy)
{
	m_grid.setSize(Vector2f(m_window.getSize().x, 10));
	m_grid.setPosition(0, m_window.getSize().y/2-5);

    const string playerScore = this->normalizeScore(player.getScore());
	m_playerScore.setString(playerScore);
	m_playerScore.setPosition(m_window.getSize().x-250, m_window.getSize().y/2);

    const string enemyScore = this->normalizeScore(enemy.getScore());
	m_aiScore.setString(enemyScore);
	m_aiScore.setPosition(m_window.getSize().x-250, m_window.getSize().y/2-250);

	if (player.getScore() == m_maxScore || enemy.getScore() == m_maxScore) {
		m_isEnd = true;
		m_resultText.setString(player.getScore() == m_maxScore ? "YOU WIN!" : "YOU LOSE!");
		m_resultText.setPosition(m_window.getSize().x/2 - 300, m_window.getSize().y/2-80);
	}
}

string UI::normalizeScore(int score) {
    stringstream scoreStream;
    if (score < m_maxScore)
        scoreStream << 0;

    scoreStream << score;
    return scoreStream.str();
}
