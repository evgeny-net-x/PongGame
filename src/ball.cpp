#include "../include/ball.h"

using namespace sf;

Ball::Ball(RenderWindow &window): GameObject("ball"), m_window(window)
{
	const float radius = 20;

	this->m_velocity = this->m_defaultVelocity;
	srand(time(NULL));

	for (int i = 0; i < HISTORY_SIZE_OF_BALL_POSITIONS; i++) {
		Color color(255, 255, 255, 255 - 25*i);

		this->m_hitboxes[i] = CircleShape(radius);
		this->m_hitboxes[i].setFillColor(color);
	}

	this->setStartingPosition();
}

Vector2f Ball::getCenterPosition(void) {
	CircleShape hitbox = m_hitboxes[0];
    Vector2f pos = hitbox.getPosition();
    const float radius = hitbox.getRadius();

    return Vector2f(pos.x+radius, pos.y+radius);
}

void Ball::draw(void)
{
	for (int i = HISTORY_SIZE_OF_BALL_POSITIONS-1; i > 0; i--)
		m_window.draw(m_hitboxes[i]);
}

void Ball::update(float deltaSec)
{
    Game *game = Game::getInstance();
    Player *player = (Player *) game->findChild("player");
    Enemy *enemy = (Enemy *) game->findChild("enemy");

	// ball intersects with window
	Vector2f currentPos = m_hitboxes[0].getPosition();
	float radius = m_hitboxes[0].getRadius();
	Vector2u winSize = m_window.getSize();

	if (currentPos.x < 0) {
		m_hitboxes[0].move(-currentPos.x, 0);
		m_dir.x *= -1;
	} else if (currentPos.x+radius*2 > winSize.x) {
		m_hitboxes[0].move(-currentPos.x + winSize.x - radius*2, 0);
		m_dir.x *= -1;
	} else if (currentPos.y < 0 || currentPos.y+radius*2 > winSize.y) {
		if (currentPos.y < 0)
			player->setScore(player->getScore()+1);
		else
			enemy->setScore(enemy->getScore()+1);

		this->setStartingPosition();
	}

	// ball intersects with boards
	if ((this->collision(player->getHitbox()) && m_dir.y > 0) || (this->collision(enemy->getHitbox()) && m_dir.y < 0)) {
		m_dir.y *= -1;
		this->increaseVelocity();
	}

	this->move(deltaSec);
}

void Ball::move(float deltaSec)
{
	Vector2f nextLastPos = this->m_hitboxes[0].getPosition() + deltaSec*this->m_velocity*this->m_dir;

	for (int i = HISTORY_SIZE_OF_BALL_POSITIONS-1; i >= 1; i--)
		this->m_hitboxes[i].setPosition(this->m_hitboxes[i-1].getPosition());
	this->m_hitboxes[0].setPosition(nextLastPos);
}

void Ball::increaseVelocity(void)
{
	if (this->m_velocity < 2000)
		this->m_velocity *= 1.2;
}

void Ball::setStartingPosition(void)
{
	Vector2u winSize = m_window.getSize();
	this->m_velocity = this->m_defaultVelocity;

	for (int i = 0; i < HISTORY_SIZE_OF_BALL_POSITIONS; i++)
		this->m_hitboxes[i].setPosition(winSize.x/2-this->m_hitboxes[i].getRadius(), winSize.y/2-this->m_hitboxes[i].getRadius());

    // TODO: redo and move the angle definitions into a separate method
	int sign = rand()%2 == 0 ? 1 : -1;;
	float angle = rand()%55 + 20;
	float radian = sign*angle*M_PI/180.0;
	this->m_dir.x = cos(radian);
	this->m_dir.y = sin(radian);
}

bool Ball::collision(const RectangleShape &board)
{
	Vector2f boardPos  = board.getPosition();
	Vector2f boardSize = board.getSize();
	Vector2f ballPos = this->m_hitboxes[0].getPosition();
	float ballRadius = this->m_hitboxes[0].getRadius();

    const float boardLeftSide   = boardPos.x;
    const float boardBottomSide = boardPos.y;
    const float boardRightSide = boardLeftSide   + boardSize.x;
    const float boardUpSide    = boardBottomSide + boardSize.y;

    const float ballLeftSide   = ballPos.x;
    const float ballBottomSide = ballPos.y;
    const float ballRightSide = ballLeftSide   + ballRadius*2;
    const float ballUpSide    = ballBottomSide + ballRadius*2;

	return ballLeftSide   < boardRightSide &&
	       ballBottomSide < boardUpSide    &&
	       ballRightSide  > boardLeftSide  &&
	       ballUpSide     > boardBottomSide;
}

