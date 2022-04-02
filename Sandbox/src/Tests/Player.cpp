#include "Player.h"


Player::Player(float xPos, float yPos)
	: Entity(xPos, yPos)
{
}

Player::~Player()
{
}

bool Player::Move(float speed, float xDir, float yDir)
{
	setX(getX() + speed * xDir);
	setY(getY() + speed * yDir);
	return true;
}
