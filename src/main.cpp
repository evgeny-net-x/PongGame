#include "../include/gameObject.h"
#include "../include/game.h"
#include "../include/ball.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/ui.h"

using namespace std;
using namespace sf;

int main(void)
{
    Game *game = Game::getInstance();

    Ball ball(game->m_window);
    Player player(game->m_window);
    Enemy enemy(game->m_window);
    UI ui(game->m_window, game->m_maxScore);

	game->addChild(static_cast<GameObject &>(ball));
	game->addChild(static_cast<GameObject &>(player));
	game->addChild(static_cast<GameObject &>(enemy));
	game->addChild(static_cast<GameObject &>(ui));

    game->start();

    return 0;
}
