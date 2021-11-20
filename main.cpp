#include <SFML/Graphics.hpp>

#include "ball.h"
#include "player.h"
#include "enemy.h"
#include "ui.h"

using namespace std;
using namespace sf;

int main(void)
{
	const int FPS = 30;
	const int maxScore = 1;

	RenderWindow window(VideoMode(1200, 900), "Pong");
	Ball ball(window);
	Player player(window);
	Enemy ai(window);
	UI ui(window, maxScore);

	Clock clock;
	bool redraw = true;

	while (window.isOpen()) {
		float deltaInSec = clock.getElapsedTime().asSeconds();
		if (deltaInSec < 1.0/FPS)
			sleep(seconds(1.0/FPS - deltaInSec));
		else {
			redraw = true;
			clock.restart();
		}

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseMoved)
				player.update();
			else if (event.type == Event::Resized) { // set minimum size
				if (event.size.width < 720)
					event.size.width = 720;

				if (event.size.height < 540)
					event.size.height = 540;

				window.setSize(Vector2u(event.size.width, event.size.height));
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
		}

		ai.update(deltaInSec, ball);
		ball.update(deltaInSec, player, ai);
		ui.update(player, ai);

		if (redraw) {
			redraw = false;
			window.clear(Color(30, 30, 30));

			player.draw();
			ai.draw();
			ball.draw();

			if (ui.isEnd()) {
				ui.drawResult();
				window.display();
				sleep(seconds(2));
				break;
			}

			ui.drawUI();
			window.display();
		}
	}

	return 0;
}
