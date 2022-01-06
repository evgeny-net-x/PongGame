#include "../include/game.h"

using namespace sf;
using namespace std;

Game* Game::m_instance = nullptr;;

Game::Game(void): GameObject("game"), m_window(VideoMode(1200, 900), "Pong")
{
    
}

Game *Game::getInstance(void)
{
    if (m_instance == nullptr)
        m_instance = new Game();

    return m_instance;
}

void Game::draw()
{
    if (m_redraw) {
        m_redraw = false;
        m_window.clear(Color(30, 30, 30));

        for(auto i = m_children.begin(); i != m_children.end(); ++i)
            (*i)->draw();
    }
}

void Game::update(float deltaSec)
{
    Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == Event::Closed)
            m_window.close();
        //else if (event.type == Event::MouseMoved)
            //player->update(deltaSec);
        else if (event.type == Event::Resized) { // set minimum size
            if (event.size.width < 720)
                event.size.width = 720;

            if (event.size.height < 540)
                event.size.height = 540;

            m_window.setSize(Vector2u(event.size.width, event.size.height));
            m_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }
    }

    for(auto i = m_children.begin(); i != m_children.end(); ++i)
        (*i)->update(deltaSec);
}

void Game::start(void)
{
	while (m_window.isOpen()) {
		float deltaSec = m_clock.getElapsedTime().asSeconds();
		if (deltaSec < 1.0/m_FPS)
			sleep(seconds(1.0/m_FPS - deltaSec));
		else {
			m_redraw = true;
			m_clock.restart();
		}	

        this->update(deltaSec);
        this->draw();
    }
}
