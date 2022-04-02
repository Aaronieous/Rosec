#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(float xPos, float yPos);
	~Player();

	bool Move(float speed, float xDir, float yDir) override;
};

